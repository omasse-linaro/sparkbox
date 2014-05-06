#include "Analogique.h"
#include "0_ADTEK.h"
#include <time.h>
#include <math.h>   // Uniquement pour la racine
#include "divers.h"
#include "evse.h"

STRUCT_ANALOG 	Analog[NB_ANALOGIQUE];
int 			readAdc[16] = {0,0,0,0,0}; // 16 car il faut lire tout le buffer

// Définition du filtre Analogique
// Attention, il ne faut saisir qu'un moyen de filtrage
//#define FILTRE_NONE	// Pas de filtrage
//#define FILTRE_LOW 	// Passe bas
//#define FILTRE_MOY	// Moyenne

 /*************************************************************************************************
 *
 *      Init
 *
 **************************************************************************************************/
void analogiqueInit(void)
{
	unsigned char i;
	unsigned char temp;

	// Valeurs qui seront lues dans l'ordre de 0 a 4
	TRISBbits.TRISB2 = 1;			// Courant 1, courant charge
	TRISBbits.TRISB3 = 1;			// Courant 2, differentiel
	TRISBbits.TRISB6 = 1;			// Temperature
	TRISBbits.TRISB7 = 1;			// Reference point milieu pour courant
	TRISBbits.TRISB10 = 1;			// V_test, lie au creneau genere de -12V a +12V


	//AD1CON1bits.SIDL = 1;                 // Stop in idle
        AD1CON1bits.FORM = 0;			// Format de sortie 16 bits
	AD1CON1bits.SSRC = 7;			// Trigger source : compteur interne
	AD1CON1bits.CLRASAM = 1;		// Stop conversion bit : a la premiere interruption
	AD1CON1bits.ASAM = 1;			// ADC sample auto start bit


        AD1CON2bits.VCFG = 3;			// Reference externe vref+ vref-
	AD1CON2bits.CSCNA = 1;			// Scan des entrees selectionnees
	AD1CON2bits.SMPI = 4;			// Interruption a la 5e conversion


        AD1CON3bits.SAMC = 31;			// Auto sample time (5 bis) n * Tad (en dessous) 0 interdit, temps pour le sample, 31 * 7us soit 214us par voie
	AD1CON3bits.ADCS = 255;			// Conversion clock select bits : Tad = Tpb * 2 * [(bits7-0) + 1] = 7us, mini 83.33ns

	//AD1CON3 = 0x000F;                     // Horloge la plus lente, environ 156kHz		Tad = Tpb * 2 * [(bits7-0) + 1]		6,4us

	AD1CHS = 0x0000;                        // Configuration des canaux


	AD1PCFG = 0xFB33;                       // Configuration des entrées analogiques	// 1111 1011 0011 0011			0 pour entree analogique
	AD1CSSL = 0x04CC;                       // Canaux a scanner       			// 0000 0100 1100 1100

	IPC6bits.AD1IP = 5; 			// set interrupt priority
        IPC6bits.AD1IS = 3;

	IEC1SET = 2;                            // Autorise les interruptions

	AD1CON1SET = 0x8000;                    // Mise ON de l'ADC
        //AD1CON1bits.ON = 1;			// Mise ON de l'ADC
	AD1CON1bits.SAMP = 1;                   // Demarre l'echantillonnage

   for ( i = 0; i < NB_ANALOGIQUE; i++ )
   {
       Analog[i+1].Etat	= CAPTEUR_DEMARRAGE;
   }

   // Initialisation pour calcul
   analogCalc.index = 0;

}

void analogiqueStart(void)
{
	Delay10us(2); // Pour ne pas faire l'acquisition trop près du front

	AD1CON1SET = 0x0004; 	// Démarre l'échantillonnage
}

//==================================================================
// ADC Interrupt
// On analyse un lot de 50 résultats, donc en théorie pour le 1kHz
//	25 ech au niveau bas et 25 ech au niveau haut
// On garde le min -1 et max -1
//==================================================================
void __ISR( _ADC_VECTOR, ipl5 ) ADCHandler( void )
{
	static unsigned char echantillons = 0;
	static int min 		= 1024;
	static int lastmin 	= 1024;
	static int max 		= 0;
	static int lastmax 	= 0;
        static int cpt1s_temp  = 0;   // Indique quand acquérir la température (1 fois par seconde)
	unsigned char count = 0;

	// Pour calculs intermediaires
	int calc;
	float calc_float;

	// Lecture des 16 buffers (impératif, sinon on ne peut pas acquitter l'interruption)
        for ( count = 0; count < 16; count++ )
	{
	    readAdc[count] = ReadADC10(count);
	}

	// Traitement de la mesure du creneau pour connaitre l'etat de la voiture
	if (echantillons < 50) // On limite à 50 échantillons car il faut pouvoir répondre en moins de 100ms à une demande de déconnexion !
	{
		if (readAdc[4] > max)
		{
		 	max = readAdc[4];
		 	lastmax = max;
		}
		if (readAdc[4] < min)
		{
		 	min = readAdc[4];
		 	lastmin = min;
		}
		echantillons++;
	}
	else
	{
		// On "exporte" le résultat
		if (lastmin ==1024) lastmin = min; // Au cas ou la première acquisition ait été le min
		if (lastmax ==0 ) lastmax = max; // Au cas ou la première acquisition ait été le max
		Evse.Min = lastmin;
		Evse.Max = lastmax;
		min = 1024; lastmin = 1024;
		max = 0; lastmax = 0;
		echantillons = 0;
	}

	Evse.Vref2 = readAdc[3];

        if (cpt1s_temp <= cpt1s)
        {
            // temperature : MCP9701 19.5mV/°C et offset de
            // Vout = 19.5mV * temperature + 400mV
            // temp = (Vout - 400mV)/19.5mV
            // Ce calcul pourra etre fait 1 fois par seconde par exemple
            calc = ((int)  readAdc[2]) * 3300;
            calc /= 1024;
            calc -= 400;
            calc *= 100;		// Pour diviser ensuite par 195 au lieu de 19.5 et avoir le resultat en dixieme de °C
            calc /= 195;		// Temperature en 1/10 de °C
            analogCalc.temp = (short) calc;
            Evse.Temp = (int) calc;
            cpt1s_temp = cpt1s+1;
        }

	//clear the interrupt flag
    IFS1CLR = 0x0002;

	// Pour etre toujours a 1kHz avec une phase stable
	if ( PILOT == 1 )
	{
		//LCD_CMD_AFF ^= 1;
		if ( analogCalc.index >= NB_ECH_CAL )
			analogCalc.index = 0;

		calc = (int) ( readAdc[1] - Evse.Vref2);	// Passage en signe
		calc *= calc;					// Passage au carre
		//analogCalc.diff[analogCalc.index] = calc;
		analogCalc.diff_somme += calc;			// Calcul partiel de l'integrale

		calc = (int) ( readAdc[0] - Evse.Vref2);	// Passage en signe
		calc *= calc;					// Passage au carre
		//analogCalc.amp[analogCalc.index] = calc;
		analogCalc.amp_somme += calc;			// Calcul partiel de l'integrale

		// calcul trms quand la table est complete
		analogCalc.index++;
		if ( analogCalc.index == NB_ECH_CAL )
		{
			calc_float = (float) analogCalc.diff_somme;
			analogCalc.diff_somme = 0;
			calc_float /= NB_ECH_CAL;		// Valeur de l'integrale des carres
			analogCalc.diff_rms = sqrtf(calc_float);
			analogCalc.diff_rms_g = analogCalc.diff_rms / 4.5;  // le transformateur n'est pas lineaire, il faudrait une conversion par tranche
                        Evse.Courant = analogCalc.diff_rms_g;

			calc_float = (float) analogCalc.amp_somme;
			analogCalc.amp_somme = 0;
			calc_float /= NB_ECH_CAL;		// Valeur de l'integrale des carres
			analogCalc.amp_rms = sqrtf(calc_float);
			analogCalc.amp_rms_g = analogCalc.amp_rms / 11.5;
                        Evse.Courant_Diff = analogCalc.amp_rms_g ;

			analogCalc.index = 0;
		}
	}
}



