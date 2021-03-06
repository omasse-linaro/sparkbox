/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 * Nom:			0_SparkBox.c
 * Fonction :	Fichier principal
 *
 *  SARL ADTEK
 **********************************************************************************************************
 * Author | Jean Arhainx  |  Date  19/03/2014   |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or
 * send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *********************************************************************************************************/

#define MAIN_SPARKBOX

#include "HardwareProfile.h"
#include "0_SPARKBOX.h"
#include <time.h>
#include <stdio.h>
#include "TCPIP Stack/SNTP.h"
#include "0_SparkBox_Version.h"
#include "rs232.h"
#include "i2c.h"
#include "Eeprom_i2c.h"
#include "mynetmemo.h"
#include "teleinfo.h"
#include "http.h"
#include "temperature.h"
#include "log.h"
#include "rtc.h"
#include "mcp7941.h"
#include "divers.h"
#include "SST25VF016.h"
#include "evse.h"

// declared static in case exception condition would prevent
 // auto variable being created
 static enum {
    EXCEP_IRQ = 0,                      // interrupt
    EXCEP_AdEL = 4,                     // address error exception (load or ifetch)
    EXCEP_AdES,                         // address error exception (store)
    EXCEP_IBE,                          // bus error (ifetch)
    EXCEP_DBE,                          // bus error (load/store)
    EXCEP_Sys,                          // syscall
    EXCEP_Bp,                           // breakpoint
    EXCEP_RI,                           // reserved instruction
    EXCEP_CpU,                          // coprocessor unusable
    EXCEP_Overflow,                     // arithmetic overflow
    EXCEP_Trap,                         // trap (possible divide by zero)
    EXCEP_IS1 = 16,                     // implementation specfic 1
    EXCEP_CEU,                          // CorExtend Unuseable
    EXCEP_C2E                           // coprocessor 2
 } _excep_code;
  
 static unsigned int _epc_code;
 static unsigned int _excep_addr;

// Configuration Bit PIC 32 ************************************************************************
// SYSCLK =  MHz (4MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV) = 80,0 Mhz
// PBCLK =  80,00 MHz (80/1)
#define SYSCLK 80000000 
#pragma config ICESEL   = ICS_PGx1  // ICE/ICD comm channel shared w/ PGC2, PGD2
#pragma config FPLLMUL  = MUL_20 // 4Mhz * 20 = 80Mhz
#pragma config FPLLIDIV = DIV_1 // 4Mhz / 1 = 4Mhz          avec oscillateur 4MHz
#pragma config FPLLODIV = DIV_1 
#pragma config FWDTEN = OFF

#pragma config POSCMOD = EC // External Resonator < 10Mhz (compatible V1 et V0)

#pragma config FNOSC = PRIPLL
#pragma config FPBDIV = DIV_1 // 80Mhz sur bus
#pragma config CP=OFF
#pragma config BWP=OFF
#pragma config FSOSCEN=OFF


// Variables globales
unsigned short  loop_count 		= 0;
unsigned short  loop_count_mem 	= 0;
unsigned char   affichage_debug = 0;
ldiv_t 			t_jour;
ldiv_t 			t_minute;

ldiv_t 			l_utc;
div_t 			i_utc;
WORD 			utc_sec;
WORD 			utc_min;
WORD 			utc_heure;
time_t			UTC_ProchainSNTP = 0; // Indique le timestamp a partir du quel on pourra refaire une acquisition SNTP

STRUCT_DATE_ADTEK 	utc;

// Declaration Fonctions
static void     Initialisation_Carte(void);
void 			Initialisation_Peripheriques(void);
void 			Process_Affichage(void);
void 			Process_Affichage_Debug1(void);
void 			Process_Affichage_Debug2(void);
void 			Process_Monitoring(void);
void 			Process_Capteurs_all(void);
void 			Process_Capteurs(void);
void 			Process_Capteurs_OW(void);
void 			Process_Maintenance_OW(void);
void 			Process_Gestion_Carte_SD(void);

// Gestionnaire exception ***************************************************************************
void _general_exception_handler(void) //(unsigned cause, unsigned status)
 {
   	asm volatile("mfc0 %0,$13" : "=r" (_excep_code));
    asm volatile("mfc0 %0,$14" : "=r" (_excep_addr));

     _excep_code = (_excep_code & 0x0000007C) >> 2;   

	Nop();
	while(1)
	{
		if(LED1 ==  1)
		{
			LED1=0;
			LED2=1;
		}
		else 
		{
			LED1=1;
			LED2=0;
		}	
		DelayMs(50);
	}	
	// Si on veut continuer , il faut ex�cuter ce code 
	Nop(); // trap here for debug
	asm("mfc0 $v0, $14"); // $v0 = EPC (=> $14 means EPC)
	asm("addiu $v0, $v0, 4"); // $v0 += 4
	asm("mtc0 $v0, $14"); // EPC = $v0
	return;       
 }

int main(void) // **************************** MAIN *********************************************
 {    
    DWORD 			t 						= 0;	// Lecture des ticks // pour info en test TICKS_PER_SECOND = 312500
    DWORD 			t_sav_seconde 			= 0;	// Boucle 1 seconde
    DWORD			t_sav_quinze_seconde 	= 0;	// Boucle 15 seconde
    DWORD 			t_sav_heure				= 0;	// Boucle 1 heure
    unsigned char 	changement_jour			= 0;	// Indique le changement de jour
    unsigned char 	changement_heure		= 0;	// Indique le changement d'heure
    unsigned char 	changement_minute       = 0;	// Indique le changement de minute
    DWORD 			dwLastIP 				= 0;
    unsigned char	bufl[20];
    unsigned char	change 					= 0;

    Initialisation_Carte();
    cpt1s = 0;
    cpt1m = 0;
    Initialisation_Peripheriques();		// initialisation des p�riph�riques, I2C, TCPIP, OW, LCD , ....
	
    // Lecture version
    strcpy(Http_byte2,"STRT: D�marrage - Version ");
    strcat(Http_byte2,VERSION_SOFT);
    strcat(Http_byte2," du ");
    strcat(Http_byte2,(ROM void*)__DATE__" "__TIME__);
    Ajout_Ligne_Log(Http_byte2);

    strcpy(Http_byte2,"STRT: Carte ADT0");ctoa(CARTE,Http_byte);strcat(Http_byte2,Http_byte);strcat(Http_byte2,", V");ctoa(VERSION_HARD,Http_byte);
    strcat(Http_byte2,Http_byte);strcat(Http_byte2,", ");ctoa(NB_RELAIS,Http_byte);strcat(Http_byte2,Http_byte);strcat(Http_byte2," relais, ");
    strcat(Http_byte2,"S/N: ");strcat(Http_byte2,No_Serie());
    Ajout_Ligne_Log(Http_byte2);


    while(1)  //***************************** BOUCLE PRINCIPALE  ***************************************
    {
        loop_count++;
        t = TickGet();
        //************ BOUCLE 1 SECONDE **********************************************************************************
        if (((t - t_sav_seconde) >= TICK_SECOND ) || (t < t_sav_seconde))
        {
			t_sav_seconde = t;
			loop_count_mem = loop_count;
			loop_count = 0;
			LED1 ^= 1;
			cpt1s++;

			//On incr�mente le temps manuellement
			utc.utc_fr++;
			utc.utc++;
			utc.seconde++;
			if (utc.seconde == 60)
			{
				utc.seconde = 0;
				utc.minute++;
				changement_minute = 1;
				if (utc.minute == 60)
				{
					utc.minute = 0;
					utc.heure++;
					changement_heure = 1;
					if (utc.heure == 24)
					{
						utc.heure = 0;
						changement_jour = 1;
						ExtractUTCAnneeMoisJour(utc.utc_fr,&utc.annee,&utc.mois,&utc.jour);
					}
				}
			}


			ConvertUtcSecToString(utc.utc_fr, Http_byte);
			memcpy(&bufl[0], &Http_byte[11],8);
			lcd_goto(0x08);
			lcd_puts(bufl);


			/*
			strcpy(bufl,"                ");
			ctoa(Sparkbox.Amp, bufl);
			strcat(bufl,"A");
			strcat(bufl,"              ");
			ConvertUtcSecToString(utc.utc_fr, Http_byte);
			memcpy(&bufl[8], &Http_byte[11],8);

			lcd_puts_line(0, bufl);*/
        }

        //************ BOUCLE 15 SECONDES *******************************************************************
        t = TickGet();
        if (( t - t_sav_quinze_seconde >= TICK_SECOND*15 ) || (t < t_sav_quinze_seconde))
        {
			t_sav_quinze_seconde = t;

        }

        //************ BOUCLE 1 MINUTE *************************************************************************
        if (changement_minute)
        {
			Process_Monitoring();

			changement_minute = 0;
        }

        //************ BOUCLE 1 HEURE *******************************************************************
        if (( t - t_sav_heure >= TICK_HOUR ) || (t < t_sav_heure))
        {
			t_sav_heure = t;
        }

        //************ BOUCLE CHANGEMENT HEURE *******************************************************************
        if ( changement_heure )
        {
			nb_heures++; // Permet de ne pas afficher certaines infos de suite .

			changement_heure = 0;
        }

        //************ BOUCLE 1 JOUR  *******************************************************************
        // Boucle de "maintenance" journali�re. Permet le nettoyage des structures (comptage erreur,....)
        // Elle est pilot�e par l'horloge.
        if ( changement_jour )
        {

			Process_Jour_Tele();

			Process_Jour_Mynetmemo();

			BD_Enregistre_Jour_Index();

			changement_jour = 0;
        }

        // ************* PROCESS *******************

        // Lecture Compteurs Electroniques TeleInfo
        Process_Tele();

        // Processus Monitoring
        if ((FONCTION != FONCTION_DEMO) && ((Sparkbox.Type_Monitoring & MONITORING_MYNETMEMO)))
        {
           Process_Mynetmemo();
        }


        // Pile TCPIP
        StackTask();

        StackApplications();


        // Gestion du pilotage manuel des relais (1cycle/100)
        Process_Relais_Manuel();

        // Si l'adresse IP change (et que le service est activ�), on l'annonce
        if(dwLastIP != AppConfig.MyIPAddr.Val)
        {
            dwLastIP = AppConfig.MyIPAddr.Val;
            #if defined(STACK_USE_ANNOUNCE)
                AnnounceIP();
            #endif
        }

        // Process de gestion de charge
        Process_EVSE();

        // Gestion RTC ADTEK
        Process_ADTEK_Get_Timestamp();

        // Watchdog
        ClrWdt();

		// Gestion du bouton ext�rieur
        Process_BP();

		// Gestion OPTO1 et OPTO2
		Process_Opto();

        if ((change == 1 ) && (BP_FILTRE == 0))
        {
    //
    //	        ctoa(Evse.Amp, bufl1);
    //        	strcat(bufl1,"A  ");
    //			lcd_goto(11);
    //			lcd_puts(bufl1);
    //			change = 0;
        }
        if (BP_FILTRE == 1)
        {
                change = 1;
        }
    }
}



//*****************************************************************************************************



// ***************************************************************************************************
//  PROCESS_MONITORING 
// Ce process se charge de demander l'envoi des donn�es � "monitorer" sur les serveurs d�clar�s.
//
void Process_Monitoring(void)
{
   // Envoi de donn�es vers Mynetmemo si le monitoring est actif
    if (Sparkbox.Type_Monitoring & MONITORING_MYNETMEMO)
    {
        // Envoi de chaque capteur. La proc�dure Envoi_Donnees_Mynetmemo v�rifie aussi si elle doit envoyer les donn�es.

        // TELE1: IINST
        Envoi_Donnees_Mynetmemo(0,Compteur[0].iinst1);

        // Temp�rature
        ultoa(Http_byte,Evse.Temp,10);
        Envoi_Donnees_Mynetmemo(1,Http_byte);

        // Pilot (State)
        Http_byte[0] = 0x30 + Evse.state;
        Http_byte[1] = 0x00;
        Envoi_Donnees_Mynetmemo(2,Http_byte);

        //Courant1
        ultoa(Http_byte,(unsigned long)Evse.Courant,10);
        Envoi_Donnees_Mynetmemo(3,Http_byte);

        //Courant2
        ultoa(Http_byte,(unsigned long)Evse.Courant_Diff,10);
        Envoi_Donnees_Mynetmemo(4,Http_byte);

        // TELE1 Puissance calcul�e
        Envoi_Donnees_Mynetmemo(5,Compteur[0].calc_puis_s);

		// TELE1 INDEX
		Envoi_Donnees_Mynetmemo(6,Compteur[0].calc_index_char);

		// TELE2: IINST
        Envoi_Donnees_Mynetmemo(7,Compteur[1].iinst1);

		// TELE2 Puissance calcul�e
        Envoi_Donnees_Mynetmemo(8,Compteur[1].calc_puis_s);

		// TELE2 INDEX
		Envoi_Donnees_Mynetmemo(9,Compteur[1].calc_index_char);

    }
}



//******************************************************************************************
// INITIALISATION CARTE
//
static void Initialisation_Carte(void)
{
    // D�marrage du watchdog
    //	WDTCONbits.ON = 1;

    // LEDs
    LED1_TRIS 	 = 0;
    LED2_TRIS 	 = 0;
    
    DEBUG_TRIS	= 0;
    DEBUG = 0;
    DEBUG2_TRIS	= 0;
    DEBUG2 = 0;
    
	// LCD
	LCD_CMD_AFF_TRIS = 0;
    
    // On active toutes les LED au d�marrage
    LED1 		= LED_ON;
    LED2		= 0;
    LCD_CMD_AFF = LED_ON;
    
    OPTO1_TRIS = 1;
    OPTO2_TRIS = 1;
    BOUTON_TRIS = 1;
    BP_EXT_TRIS = 1;
    
    AC1_TRIS	= 1;
    AC2_TRIS	= 1;	
   
    // IO d'enable de l'eeprom en sortie
    SST25_CS_TRIS 	= 0;
    SST25_CS_LAT 	= 1;
   
    RELAIS1_TRIS = 0;
    RELAIS2_TRIS = 0;
    RELAIS3_TRIS = 0;
    RELAIS4_TRIS = 0;

    RELAIS1 = RELAIS_OFF;
    RELAIS2 = RELAIS_OFF;
    RELAIS3 = RELAIS_OFF;
    RELAIS4 = RELAIS_OFF;

    PILOT_TRIS = 0;
    PILOT_IN_TRIS = 1;
    PILOT = 1; 			// 0 = -12v 1 = +12V
    
        // LCD
    lcd_init();
    
    lcd_puts_line(0, "SparkBox - ADTEK");
    lcd_puts_line(1, "Demarrage ......");
    
    // PIC32MX ---------------
    CheKseg0CacheOn();
    INTEnableSystemMultiVectoredInt(); 		
    SYSTEMConfigPerformance(GetSystemClock()); 	
    mOSCSetPBDIV (OSC_PB_DIV_1);  			
    DelayMs(50);
   // D�sactivation du JTAG
    DDPCONbits.JTAGEN = 0;
	
}



 //******************************************************************************************
// INITIALISATION DES PERIPHERIQUES
//
void Initialisation_Peripheriques(void)
{
	unsigned char etat_rtc = 0;
	
	TickInit();
	
	// D�marrage gestion des logs!	
	Init_Log();	
	
	// Gestion de l'heure et de la RTC si ADT18
	utc.annee = 0;
	utc.mois = 0;
	utc.jour = 0;
	utc.heure = 0;
	utc.minute = 0;
	utc.seconde = 0;
	
	Init_eeprom();  // D�marrage I2C pour EEProm

	MPFSInit();
    
    // Retour a la configuration usine ?
    if (BOUTON == 0)
	{
		lcd_puts_line(1, "Raz Usine ....");
		Raz_Usine();
		Ajout_Ligne_Log("STRT: RAZ Usine demand� par appui bouton!");
	} 

	// Lecture de la config mat�rielle Hardware
	// Num�ro de carte
	CARTE =  Eeprom_Lecture_Config(0x1900);
	if (CARTE == 0xFF)
	{
		Ajout_Ligne_Log("STRT: Num�ro de carte vierge");
	}
	// Version Hardware
	VERSION_HARD =  Eeprom_Lecture_Config(0x1901);
	if (VERSION_HARD == 0xFF)
	{
		Ajout_Ligne_Log("STRT: Version Hardware inconnue");
	}
	// Nombre de relais
	NB_RELAIS =  Eeprom_Lecture_Config(0x1902);
	if (NB_RELAIS == 0xFF)
	{
		NB_RELAIS = 4;
		Eeprom_Ecriture_Config(0x1902,4); // 4 relais
		Ajout_Ligne_Log("STRT: Initialisation des relais. 4 par d�faut!");
	}	
	// Fonction
	FONCTION =  Eeprom_Lecture_Config(0x1903);
	if ((FONCTION == 0xFF)||(FONCTION == 0x00))
	{
			Eeprom_Ecriture_Config(0x1903,FONCTION_SPARKBOX);
			FONCTION = FONCTION_SPARKBOX;
	}
	
    // Lecture EEPROM
    if (!Eeprom_Lecture_IP(&AppConfig)) 
    {
	    Eeprom_RAZ_IP(&AppConfig);
    	Ajout_Ligne_Log("STRT: Probl�me lecture Config IP. Raz effectu�e.");
    }
    
    // Initialize core stack layers (MAC, ARP, TCP, UDP) and application modules (HTTP, SNMP, etc.)
    StackInit(); 
     
	// LECTURE REGUL    
    if (!Eeprom_Lecture_Regul(&Sparkbox))
    {
	    Eeprom_Raz_Regul(&Sparkbox);
    	Ajout_Ligne_Log("STRT: Probl�me lecture Config Regul. Raz effectu�e.");
    }
    Controle_Coherence_Regul();

    if (!Eeprom_Lecture_User(&User))
    {
	    Eeprom_Raz_User(&User);
    	Ajout_Ligne_Log("STRT: Probl�me lecture Config User. Raz effectu�e.");
    }
	if (!Eeprom_Lecture_Mynetmemo(&Mynetmemo))
	{
		Eeprom_Raz_Mynetmemo(&Mynetmemo);
    	Ajout_Ligne_Log("STRT: Probl�me lecture Config Mynetmemo. Raz effectu�e.");
    }

    // T�l�info
    Initialisation_Rs232();
    TeleInit();

	// BD SST
	BD_Init();

    //** MONITORING **//
    // 1)Mynetmemo
    // 2) BDPV
    Sparkbox.Type_Monitoring = MONITORING_MYNETMEMO;
    Sparkbox.Type_Menu = MENU_ETENDU;
    Initialise_Mynetmemo();
    
    
    // Gestion des relais manuel (pilotage par http)
    Init_Relais_Manuel();
    	
    // Initialisation Convertisseurs Analogique/Num�rique
    analogiqueInit();
  
	MCP7941_Init_I2c();
	etat_rtc = MCP7941_Init();
	MCP7941_Lis_UTC(&utc);
	
    Init_Timer_1kHz();
    
    Init_EVSE();

	strcpy(Http_byte,"                ");
	lcd_puts_line(0, Http_byte);
    
}

//******************************************************************************************
void Raz_Usine(void)
{
	unsigned int i;

	i= 0;
	LED1 = LED_OFF;
	while (i<100)
	{
        ClrWdt();           
		DelayMs(50);
		LED2 = LED_ON;
		LED1 = LED_OFF;         		
		DelayMs(50);
   		LED2 = LED_OFF;     		
   		LED1 = LED_ON;
        i++;
        if (BOUTON == 1) // Le  rel�chement du bouton acc�l�re le processus
        {
	        i = 100;
        }	
    }	
    Eeprom_RAZ_IP(&AppConfig);
	Eeprom_Raz_Mynetmemo(&Mynetmemo);
	Eeprom_Raz_User(&User);
	Eeprom_Raz_Regul(&Sparkbox);
}






