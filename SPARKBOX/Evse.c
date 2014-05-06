/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 * Nom:			Evse.c
 * Fonction :	Gestion de la précédure de charge J1772
 *
 *  SARL ADTEK
 **********************************************************************************************************
 * Author | Jean Arhainx  |  Date  19/03/2014   |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or
 * send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *********************************************************************************************************/


#include <plib.h>
#include <string.h>
#include "0_SPARKBOX.h"
#include "log.h"
#include "rtc.h"
#include "divers.h"
#include "teleinfo.h"
#include "evse.h"

#define SYSCLK 80000000 

#define INIT_PR3     ( SYSCLK / ( 2 * 1000 ) - 1 )        // 1kHz

#define PULSE_INIT		0
#define PULSE_STARTED	1

STRUCT_EVSE			Evse;

unsigned char	bp_ext_sav = 1;
unsigned char	Pilot_1kHz 		= OFF;
unsigned char	Pilot_1kHz_Pulse	= PULSE_INIT;
unsigned int	rstuck_cpt1ms = 0;				// Gestion temporisation pour test collage relais

unsigned int	Pwm; // variable to store calculated PWM value
unsigned char	Mode = 0; // variable to determine ramp up or ramp down

void Init_1kHz_DutyCycle();
int	Charge(unsigned status);
unsigned char Amperage(void);

#define DELAY_GROUND_CHECK	1000
#define DELAY_STUCK_CHECK	1000
#define DELAY_DIODE_CHECK	10


// Procédure d'initialisation de l'EVSE

int Init_EVSE(void)
{
	Evse.state = STATE_A;
	//Evse.Amp   = Sparkbox.Amp;
	Evse.DutyCycle = 0;
	Pilot(Sparkbox.Amp);
	Evse.Min = 900;
	Evse.Max = 900;
	Evse.Heure_Debut = 0;
	Evse.Default = NONE;

	return (0);
}


// Process de gestion de l'EVSE

int Process_EVSE(void)
{
	static unsigned char state_sav = 0;	// Sauvegarde de l'état courant
	static unsigned char state_new = 0;	// Nouvel état
	static unsigned char state_new2 = 0;	// Nouvel état
	static unsigned int  state_cpt1ms = 0;
	static unsigned char state_buf[2];
	static unsigned char default_sav = NONE;	// Sauvegarde de l'état précédent de défaut
	static unsigned char buf_l2[17];
	static unsigned int  diode_cpt1ms = 0;
	static unsigned int  gfci_cpt1ms = 0;
	static unsigned int  clign_cpt1ms = 0;		// Sert à la gestion du clignotement de la LED du bouton

	// Lecture du signal  Pilot ---------------------------------------------
	if (Evse.Max >= 800) {
		state_new = STATE_A;    // DC                   // Not Connected
	}
	else if (Evse.Max >= 700) {
		state_new = STATE_B;    // +9v	-12v    1kHz	// EV Connected (Ready)
	}
	else if (Evse.Max >= 600) {
		state_new = STATE_C;    // +6v	-12v	1kHz	// EV Charge
	}
	else if (Evse.Max >= 500)       // +3v	-12v	1kHz		// EV Charge Venti. Required
	{
		state_new = STATE_D;
	}

	// Anti-rebond sur le signal Pilot ------------------------------
	if (state_new != state_sav) {
		if (state_cpt1ms == 0) {
			state_cpt1ms = cpt1ms;
			state_new2 = state_new;
		}
		else if (state_new == state_new2) // Pas de changement pendant la phase d'anti-rebond
		{
			if (state_new == STATE_A) {
				if ((cpt1ms - state_cpt1ms) > 25) {
					Evse.state = state_new;
				}
			}
			else {
				if ((cpt1ms - state_cpt1ms) > 250) {
					Evse.state = state_new;
				}
			}
		}
		else // retour au début 
		{
			state_cpt1ms = 0;
		}
	}


	// Test de présence de la diode sur le VE ---------------------------
	if ((Sparkbox.Diode == OUI) && ((Pilot_1kHz == ON) && (Evse.Min >= 200))) {
		// On gère un anti-rebonds de 100ms pour le GFCI
		if (gfci_cpt1ms == 0) {
			gfci_cpt1ms = cpt1ms;
		}
		else if ((cpt1ms - gfci_cpt1ms) > 100) {
			Evse.Default |= DEFAUT_DIODE;
		}
	}
	else {
		gfci_cpt1ms = 0 ;
		Evse.Default &= DEFAUT_DIODE__; // Pour effacer le défaut
	}

	// Test de non dépassement du courant de fuite  ---------------------------
	if ((Sparkbox.Gfci > 0) && ((Pilot_1kHz == ON) && (Evse.Courant_Diff >= Sparkbox.Gfci  ))) {

		if (diode_cpt1ms == 0) {
			diode_cpt1ms = cpt1ms;
		}
		else if ((cpt1ms - diode_cpt1ms) > 100) {
			Evse.Default |= DEFAUT_GFCI;
		}
	}
	else {
		diode_cpt1ms = 0 ;
		// On n'autorise pas la supression des défauts. Il faut redémarrer !
		// Evse.Default &= DEFAUT_DIODE__; // Pour effacer le défaut
	}


	// Test de présence de la phase et de la terre  ---------------------------
	if ((Evse.Etat_Relais == ON) && ((cpt1ms - Evse.Heure_Debut) > DELAY_GROUND_CHECK) && (AC1 == 1) && (AC2 == 1)) {
		Evse.Default |= DEFAUT_GROUND;
		Ajout_Ligne_Log("EVSE: AC1 == 1");
	}
	else {
		// On n'autorise pas la supression des défauts. Il faut redémarrer !
		//Evse.Default &= DEFAUT_GROUND__; // Pour effacer le défaut
	}


	// Test de non collage des relais.
	// L'arrêt de charge programme rstuck_cpt1ms = cpt1ms + DELAY_STUCK_CHECK.
	// V0 = test
	if ((Sparkbox.Collage_Relais == OUI) && ((rstuck_cpt1ms > cpt1ms) && (AC1 == 0) && (AC2 == 0))) // || (VERSION_HARD == 0)
	{
		Evse.Default |= DEFAUT_RELAIS;
	}
	else {
		//On n'autorise pas la supression des défauts. Il faut redémarrer !
		//Evse.Default &= DEFAUT_RELAIS__; // Pour effacer le défaut
	}


	// Gestion signal Pilot et LED Bouton ----------------------------------------
	if (Evse.state == STATE_A) {
		Pilot(0);  // +12v continu
		LED2 = 0;
	}
	else
	{
		// Gestion du fil "pilot". On spécifie à la voiture l'ampérage disponible
		Pilot(Amperage());

		// LED BOUTON
		// On gère les défauts
		if (Evse.Default != NONE)
		{
			if (cpt1ms > clign_cpt1ms)
			{
				LED2 ^= 1;
				clign_cpt1ms = cpt1ms + 50;
			}
		}
		else // Pas de défauts
		{
			if (Evse.state == STATE_B ) // VE Connecté
			{
				LED2 = 1;
			}
			else // En charge
			{
				if (cpt1ms > clign_cpt1ms)
				{
					LED2 ^= 1;
					clign_cpt1ms = cpt1ms + 500;
				}
			}
		}

	}

	// Traitement et affichage des défauts -------------------------------------
	if (Evse.Default != default_sav) {
		if (Evse.Default & DEFAUT_DIODE) {
			Ajout_Ligne_Log("EVSE: Défaut présence Diode");
			Charge(ARRET);
			strcpy(state_buf, "D");
			strcpy(buf_l2, "Defaut Diode");
			lcd_puts_line(1, buf_l2);
		}
		if (Evse.Default & DEFAUT_GROUND) {
			Ajout_Ligne_Log("EVSE: Défaut Terre");
			Ajout_Ligne_Log("EVSE: Il faut redémarrer la SparkBox");
			Charge(ARRET);
			strcpy(state_buf, "G");
			strcpy(buf_l2, "Defaut Terre");
			lcd_puts_line(1, buf_l2);
		}
		if (Evse.Default & DEFAUT_RELAIS) {
			Ajout_Ligne_Log("EVSE: Défaut Collage Relais");
			Ajout_Ligne_Log("EVSE: Vérifier installation!");
			Charge(ARRET);
			strcpy(state_buf, "R");
			strcpy(buf_l2, "Defaut relais");
			lcd_puts_line(1, buf_l2);
		}
		if (Evse.Default & DEFAUT_GFCI) {
			Ajout_Ligne_Log("EVSE: Défaut Courant de fuite");
			Ajout_Ligne_Log("EVSE: Vérifier installation!");
			Charge(ARRET);
			strcpy(state_buf, "F");
			strcpy(buf_l2, "Defaut GFCI");
			lcd_puts_line(1, buf_l2);
		}
		if (Evse.Default == NONE) {
			state_sav = 99;
		}
		// Sauvegarde des états
		default_sav	= Evse.Default;
	}
	if ((Evse.state != state_sav) && (Evse.Default == NONE)) {

		if (Evse.state == STATE_A) {
			strcpy(state_buf, "A");
			strcpy(buf_l2, "Non connecte");
			Charge(ARRET);
			Ajout_Ligne_Log("EVSE: Pas de  véhicule");
		}
		if (Evse.state == STATE_B) {
			strcpy(state_buf, "B");
			strcpy(buf_l2, "Connecte");
			Charge(ARRET);
			Ajout_Ligne_Log("EVSE: Véhicule connecté");
		}
		if (Evse.state == STATE_C) {
			strcpy(state_buf, "C");
			strcpy(buf_l2, "charge");
			Ajout_Ligne_Log("EVSE: Véhicule demande charge");
			if (Evse.Default == NONE) {
				Charge(MARCHE);
			}
			else {
				Charge(ARRET);
			}
		}
		if (Evse.state == STATE_D) {
			strcpy(state_buf, "D");
			strcpy(buf_l2, "Dmd Ventil");
			if (Sparkbox.Ventilation == 0) // pas de ventilation
			{
				Charge(ARRET);
				Ajout_Ligne_Log("EVSE: Ventilation requise");
			}
			else {
				Relais(Sparkbox.Ventilation , RELAIS_ON);
				Ajout_Ligne_Log("EVSE: Ventilation en cours");

			}
		}
		if (Evse.state != STATE_D) {
			if (Sparkbox.Ventilation != 0) {
				Relais(Sparkbox.Ventilation , RELAIS_OFF);
			}
		}
		lcd_goto(0x4F);
		lcd_puts(state_buf);
		// Ligne 2
		lcd_puts_line(1, buf_l2);

		// Sauvegarde des états
		state_sav = Evse.state;
	}
	return (0);
}

//Pilot(unsigned char ampere);-- Gestion de la sortie Pilot	
// ampere = 0 -> +12v continu
// ampere = x -> Sortie 1Khz avec le rapport cyclique calculé pour x Ampères

int Pilot(unsigned char ampere)
{
	static unsigned char 	ampere_sav = 101;
	unsigned int 			ampere10;
	unsigned int 			calc;
	unsigned char			error;

	// Gestion des incohérences
	error = 0;
	if ((ampere > 0 ) && (ampere < 6) || (ampere > 80)) {
		ampere = 0;
		error = 1;
	}
	if (ampere_sav != ampere) {
		if (ampere == 0) {
			DEBUG2 = 1;
			Pilot_1kHz = OFF;
			PILOT = 1; 			// 0 = -12v 1 = +12V
			DEBUG2 = 0;
		}
		else {
			// Calcul du rapport cyclique
			if ((ampere >= 6) && (ampere <= 51)) {	// duty cycle  = Amps / 0,6
				ampere++; // Bizarre mais nécéssaire sur la Leaf
				ampere10 = (ampere * 10);
				calc = ampere10 / 6;
			}
			else if ((ampere > 51) && (ampere <= 80)) {	// duty cycle  = (Amps / 2,5) + 64
				ampere++; // Bizarre mais nécéssaire sur la Leaf
				ampere10 = (ampere * 10);
				calc = ampere10 / 25;
				calc = calc + 64;
			}
			ampere--;
			Evse.DutyCycle = calc;
			Pilot_1kHz = ON;
		}
		ampere_sav = ampere;
		if (error == 1) {
			return (-1);
		}
		return (0);
	}
}

// Gestion des relais de charge
// La fonction peut etre appelée en continu

int	Charge(unsigned status)
{
	if (status == ARRET) {
		if (Etat_Relais(RELAIS_PHASE) == RELAIS_ON) {
			Relais(RELAIS_PHASE, RELAIS_OFF);
			Ajout_Ligne_Log("EVSE: Relais EVSE OFF");
		}
		if (Etat_Relais(RELAIS_NEUTRE) == RELAIS_ON) {
			Relais(RELAIS_NEUTRE, RELAIS_OFF);
		}
		Evse.Etat_Relais = OFF;
		Evse.Heure_Debut = 0;
		if (rstuck_cpt1ms == 0) rstuck_cpt1ms = cpt1ms + DELAY_STUCK_CHECK; // On programme le test de collage relais
	}
	else if (status == MARCHE) {
		if (Etat_Relais(RELAIS_PHASE) == RELAIS_OFF) {
			Relais(RELAIS_PHASE, RELAIS_ON);
			Ajout_Ligne_Log("EVSE: Relais EVSE ON");
		}
		if (Etat_Relais(RELAIS_NEUTRE) == RELAIS_OFF) {
			Relais(RELAIS_NEUTRE, RELAIS_ON);
		}
		Evse.Etat_Relais = ON;
		if (Evse.Heure_Debut == 0) Evse.Heure_Debut = cpt1ms;
		rstuck_cpt1ms = 0;
	}
	else {
		return (-1);
	}

	return (0);
}

// Gestion du bouton extérieur
// Le process soit être appelé dans le main et le résultat lu par BP_FILTRE
void Process_BP(void)
{
	static unsigned char change = 0;
	static unsigned int  DebounceTime = 0;


	if ((change == 0 ) && (BP_EXT != BP_FILTRE))
	{
		DebounceTime = cpt1ms;
		change = 1;
	}
	if ((change == 1) && ((cpt1ms - DebounceTime) > 50))
	{
		if (BP_EXT != BP_FILTRE)
		{
			BP_FILTRE = BP_EXT;
		}
		change = 0;
	}
}

// Gestion des 2 opto
// Le process soit être appelé dans le main et le résultat lu par OPTO1_FILTRE ou OPTO2_FILTRE
void Process_Opto(void)
{
	static unsigned char change1 = 0;
	static unsigned char change2 = 0;
	static unsigned int  DebounceTime1 = 0;
	static unsigned int  DebounceTime2 = 0;

	// Opto 1
	if ((change1 == 0 ) && (OPTO1 != OPTO1_FILTRE))
	{
		DebounceTime1 = cpt1ms;
		change1 = 1;
	}
	if ((change1 == 1) && ((cpt1ms - DebounceTime1) > 50))
	{
		if (OPTO1 != OPTO1_FILTRE)
		{
			OPTO1_FILTRE = OPTO1;
		}
		change1 = 0;
	}

	// Opto 2
	if ((change2 == 0 ) && (OPTO2 != OPTO2_FILTRE))
	{
		DebounceTime2 = cpt1ms;
		change2 = 1;
	}
	if ((change2 == 1) && ((cpt1ms - DebounceTime2) > 50))
	{
		if (OPTO2 != OPTO2_FILTRE)
		{
			OPTO2_FILTRE = OPTO2;
		}
		change2 = 0;
	}


}

// ************************************************ GESTION SIGNAL 1 Khz ******************************************************************************
//  Préambule : Lancer  "Init_Timer_1kHz" au démlarrage de l'application
//  Gestion Pulse 1kHz:
//  	Pour démarrer un pulse, l'IT 1kHz appelle la fonction Init_1kHz_DutyCycle (Lance une convertion ana)
// 		Init_1kHz_DutyCycle passe Pilot à +12v, lance le timer 2 qui est chargé de gérer la durée (variable) 
//		A l'expiration du délai l'IT du timer 2 passe Pilot à -12v et lance une convertion analogique

//*****************************************************************************
//  Fonction: 		Init_Timer_1kHz
//  Description:	Initialise le Timer 1kHz !! TIMER 3
//  Gére :
// 		- cpt1ms
// 		- Lecture des opto (Compteurs)
// 		- Début de pulse signal Pilot 1kHz
// 		- Lance les convertions analogiques si +12v continu
//  ***************************************************************************

int Init_Timer_1kHz(void)
{
	// Timer 3
	T3CONbits.TCKPS = 1;        // 1:2 prescale sur sysclk
	PR3 = INIT_PR3;
	TMR3 = 0;                   // Clear counter
	IPC3bits.T3IP = 4;	        // Interrupt priority 2
	IFS0CLR = _IFS0_T3IF_MASK;
	IEC0SET = _IEC0_T3IE_MASK;
	T3CONbits.TON = 1;          // Start timer
	return (0);
}

//*****************************************************************************
//  Fonction: 		Init_1kHz_DutyCycle
//  Description:	Lance un pulse, et une acquisition Analogique 
//  ***************************************************************************

void Init_1kHz_DutyCycle(void)
{
	// Timer 2
	T2CONbits.TCKPS = 1; // 1:2 prescale
	PR2 = (INIT_PR3 * Evse.DutyCycle) / 100 ; // DutyCycle donne le rapport cyclique
	TMR2 = 0; // Clear counter
	IPC2bits.T2IP = 3;	// Interrupt priority 3
	IFS0CLR = _IFS0_T2IF_MASK;
	IEC0SET = _IEC0_T2IE_MASK;
	T2CONbits.TON = 1; // Start timer
	PILOT = 1;
}

/*****************************************************************************
  Fonction: 	interruption Timer 3 (Timer de base 1kHz)
  Description:	Gestion du 1kHz pour Compteur, cpt1ms; EVSE,....
 ***************************************************************************/
void __attribute((interrupt(ipl4), vector(_TIMER_3_VECTOR), nomips16)) _T3Interrupt(void)
{
	// Incrémentation compteur 1ms
	cpt1ms++;


	// Gestion EVSE	
	if (Pilot_1kHz == ON) // 1kHz
	{
		if (Pilot_1kHz_Pulse == PULSE_INIT) {
			Pilot_1kHz_Pulse = PULSE_STARTED;
			// On vas lancer un pulse
			Init_1kHz_DutyCycle();
		}
	}
	// Si on est en +12v continu, il faut lancer quand même les acquisitions analogiques
	analogiqueStart();

	IFS0CLR = _IFS0_T3IF_MASK;
}

/*****************************************************************************
  Fonction: 	interruption Timer 2
  Description: Met le signal PILOT à -12v
 ***************************************************************************/
void __attribute((interrupt(ipl3), vector(_TIMER_2_VECTOR), nomips16)) _T2Interrupt(void)
{
	// Si on a demandé d'arrêter le 1kHz entre temps, l'interruption ne doit pas mettre PILOT à 0 car à l'arrêt il est à 1
	if (Pilot_1kHz == ON) {
		PILOT = 0;
	}

	// On autorise la prochaine pulse
	Pilot_1kHz_Pulse = PULSE_INIT;

	// On valide l'interruption
	IFS0CLR = _IFS0_T2IF_MASK;

	// On arrête le timer 2
	T2CONbits.TON = 0;

	// Lancement convertion analogique
	analogiqueStart();
}

/*****************************************************************************
 * Fonction: 	Amperage
 * Description: Retourne l'ampérage à programmer (via le signal pilot)
 * Gére le délestage - Affiche le courant programmé - Temporise les changement d'au moin une seconde
 * - Via OPTO
 *
 ***************************************************************************/
unsigned char Amperage(void)
{
	unsigned char			amp = 0;
	static unsigned char	sav_amp = 0;
	unsigned char			buf[17];
	static unsigned int		amp_cpt1ms = 0;

	amp = Sparkbox.Amp;
	if (OPTO1_FILTRE == OPTO_ON)
	{
		amp = Sparkbox.Amp_Reduit1;
	}
	if (OPTO2_FILTRE == OPTO_ON)
	{
		amp = Sparkbox.Amp_Reduit2;
	}
	if ((amp != sav_amp) && ((cpt1ms-amp_cpt1ms) > 1000))
	{
		sav_amp = amp;
		// On en profite pour mettre à jour l'affichage
		ctoa(amp,buf);
		strcat(buf, " A");
		if (strlen(buf) == 3) strcat(buf, " ");
		lcd_goto(0x00);
		lcd_puts(buf);
		amp_cpt1ms = cpt1ms;
	}
	return(sav_amp);
}