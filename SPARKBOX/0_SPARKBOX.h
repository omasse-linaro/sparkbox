/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 *  SARL ADTEK
 **********************************************************************************************************
 * Author | Jean Arhainx  |  Date  19/03/2014   |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or
 * send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *********************************************************************************************************/
#ifndef _SPARKBOX_H
	#define _SPARKBOX_H
	
	#include "GenericTypeDefs.h"
	#include "TCPIP Stack/TCPIP.h"
	#include <time.h>
	

	//#define ADTEK_TEST1		// Remplace les capteurs par un jeu de test
	//#define LOG_UDP		// Indique si on gère des LOG via UDP
	
	//#define BAUD_RATE       (19200)		// bps
	
	#define ADTEK_USE_MAIL
	// LIMITES ----------------------------------
	#define NB_MAX_CAPTEURS    			16
	#define T_HECTO_MIN					-9999		// -99,99°
	#define T_HECTO_MAX					9999 		// 99,99°
	#define TEMPS_MIN					1300000000	// Temps minimum, si il est inférieur, c'est cpt1s sinon c'est le timestamp


	// Definition capteurs
	#define AUCUN   	        0
	#define ANALOGIQUE		    1
    //#define reserve           2
	#define DS1820			    3
	#define TELEINFO			4
	#define RESERVE5			5
	#define RESERVE10			10
	#define RESERVE11			11
	
	// Index paramètres EVSE
	#define MAX_AMP				0		// Ampèrage maximal de la SparkBox
	#define	AMP					1		// Ampèrage actuel de la SparkBox	
	#define GFCI				2		// Test 30mA  (1 = OUI, 0 = NON)
	#define DIODE				3		// Test Diode (1 = OUI, 0 = NON)
	#define RELAIS_STUCK		4		// Test de collage de relais
	#define AMP_REDUIT1			5		// Ampérage réduit 1
	#define AMP_REDUIT2			6		// Ampérage réduit 2
	#define LCD					7		// Modèle de LCD  0x01 = internet, 0x02 = I2C
	#define VENTILATION			8		// Numéro de relais utilisé pour la ventilation (0= pas de relais, donc arret de charge si ventilation demandée)
	#define COEF_GFCI			9		// Coefficient bobine détyection Courant de fuite (GFCI)
	
	#define CAPTEUR_AUCUN			0x99
	#define CAPTEUR_DEMARRAGE		0x98
	#define CAPTEUR_ABSENT			0x00
	#define CAPTEUR_OK				0x01
	#define CAPTEUR_ERREUR			0x02
	#define INTERVALE_ALERTE		3600		// une alerte OW max par capteur toutes les heures
/*/

	#define RELEVE_AUCUN			0x00		// Pas de relève
	#define RELEVE_APPOINT   		0x01		// Relève en complément de la PAC (par exemple appoint électrique)
	#define RELEVE_REMPLACEMENT		0x02 		// La mise en route du complément arrête la PAC	

	#define DELESTAGE_AUCUN			0x00
*/
	// MONITORING
	#define MONITORING_AUCUN		0x00
	#define MONITORING_ADTEK1		0x01	// 00000001 ADTEK 
	#define MONITORING_ADTEK2		0x02	// 00000010 ADTEK RESERVE
	#define MONITORING_MYNETMEMO	0x04	// 00000100 Mynetmemo
	#define MONITORING_XPL			0x08	// 00001000 XPL
	#define MONITORING_ITOW			0x10	// 00010000 ITow
	#define MONITORING_BDPV			0x20	// 00100000 BDPV

	// XPL
	#define XPL						0x00	// Pas d'options spécifiques. Donc au moins mode client. Le pilotage XPL (ON/OFF) est dans Monitoring
	#define XPL_ATTENTE				0x01 	// Inactif !
	#define XPL_SERVEUR				0x02	// Serveur XPL Actif	

	// DEGUG 
	#define DEBUG_NONE			0
	#define DEBUG_LOG_ETENDU	1
	#define DEBUG_MAX			128
	#define DEBUG_ADTEK			129
	
	#define OUI					1
	#define NON					0
	
	#define ON					1
	#define OFF					0
	
	#define START				1
	#define STOP				0
	
	#define ARRET				0
	#define MARCHE				1
	
	
	// RELAIS
	#define NB_RELAIS_MAX		4
	#define RELAIS_ON		    1
	#define RELAIS_OFF	        0
	#define RELAIS_NONE			0
	#define RELAIS_NEUTRE		1
	#define RELAIS_PHASE		2

		
	//LED
	#define LED_OFF	        	0
	#define LED_ON 	        	1

	//OPTO
	#define OPTO_OFF	        1
	#define OPTO_ON 	       	0
	
	//MENU
	#define MENU_BASE1			0
	#define MENU_MINI			1
	#define MENU_NORMAL			2
	#define MENU_ETENDU			4

	
	//EMAIL_RECAP
	#define EMAIL_RECAP_NONE	0
	#define EMAIL_RECAP_JOUR	1
	#define EMAIL_RECAP_HEBDO	2
	#define EMAIL_RECAP_MOIS	4
	
	// Fonction
	#define FONCTION_SPARKBOX	1
	#define FONCTION_DEMO		2
	#define FONCTION_DEBUG		3


	// STRUCTURE CAPTEUR GENERIQUE POUR TOUT MODELE DE CAPTEUR	
   typedef struct
   {
        unsigned char   Type;					// One Wire, PT1000, .....    
        unsigned char	Id[8];				    // Identifiant capteur OW = ID, TELEINFO = Rang de l'info qui sert de resultat au capteur 
        unsigned char   No;					    // One Wire = position capteur dans le tableau - PT1000 = 1 ou 2, TELEINFO = 1 ou 2 
        short			Temperature; 		    // Température *100	
        unsigned char	Temperature_s[8];	    // Chaîne ascii contenant la température
        unsigned char	Nom[26];				// Nom Capteur sur 25 caractères
        unsigned char	Etat;					// Indique l'état du capteur (présent,défectueux,...)
		unsigned char	align;
   } STRUCT_CAPTEUR; // 48 octets *16 = 768 Octets


   	#define NB_ECH_CAL		100
	
	typedef struct _ANALOG_TAB
	{
		int				diff_somme;
		float			diff_rms;
		float			diff_rms_g;
		float			diff_coeff;
		
		int				amp_somme;
		float			amp_rms;
		float			amp_rms_g;
		
		short 			temp;
		unsigned char 	index;
	} ANALOG_TAB;
	
   
	// *******************************************************************************************************************************************
	// STRUCTURE ********EVSE  *********
	// *********************************
	// Attention garder alignement 32bits !
	typedef struct
    {
        unsigned char	Max_Amp;		// Ampérage maximal
        unsigned char	Amp;			// Ampérage disponible
        unsigned char	Gfci;			// Courant de fuite
        unsigned char	Diode;			// Test présence diode
		
		unsigned char	Collage_Relais;	// Test collage relais
		unsigned char	Amp_Reduit1;	// Puissance réduite niveau 1
		unsigned char	Amp_Reduit2;	// Puissance réduite niveau 2
		char			Ecart_Gmt;		// Gère l'écart d'heure avec la GMT

		unsigned char	Lcd;
		unsigned char	Ventilation;
		unsigned char	Arret_Sur_Baisse;				// Arrête la charge dés la baisse de l'ampérage
		unsigned char	align1;
		unsigned short	Coef_Gfci;						// Pour calibration GFCI (disparités bobines)	*100 (450 = 4.5)
		unsigned char	Delestage_Teleinfo;				// Délestage intelligent via téléinfo TELE1
		unsigned char	Reserve_Teleinfo;				// Ampérage de réserve pour Délestage intelligent via téléinfo TELE1
		unsigned int	Reserve1[31];
		// MENU
		unsigned char	Type_Menu;						// type de menu
        unsigned char	Type_Email;						// type d'envoi d'email
        // XPL
	    unsigned char   Xpl_Intervalle;					// Intervalle d'envoi de trames xpl en minutes (1 à 60)
        unsigned char 	Xpl_Fonction;					// Indique ce que l'on peux faire en Xpl
        unsigned char   Xpl_Name[24];					// Nom XPL

		// Monitoring
        unsigned char	Type_Monitoring;				// Type de Monitoring 1 bit par service donc 8 ma
		unsigned char	Debug;							// Gestion des modes de debug
		unsigned char	align3;
		unsigned char	align4;
		unsigned int	Reserve2[16];

        STRUCT_CAPTEUR  Capteur[NB_MAX_CAPTEURS];	    // Capteurs 768 octets

		unsigned int	Reserve3[32];
     
    } STRUCT_SPARKBOX; // 1243 octets (1278 Octet max dans la structure I2C)
    
    
    // *******************************************************************************************************************************************
    // STRUCTURE UTILISATEUR     
    typedef struct
    {  // Utilisateur web
        unsigned char   Login[21];      // 20 caractères + 0x00
        unsigned char   Password[21];   // 20 caractères + 0x00
    } STRUCT_USER; //42


	// Structure de DATE --------------------------------------------------------------------------------
    typedef struct
    { 
	    time_t			utc;	// Temps universel coordonné
	    time_t			utc_fr;	// Temps corrigé par le Timezone en France
		unsigned short	annee;        
		unsigned char   mois;  	
		unsigned char	jour;   
		unsigned char	heure;
		unsigned char	minute;
		unsigned char	seconde;   
    } STRUCT_DATE_ADTEK;


	// BD Client CURL
   typedef struct
   { 
	    unsigned char 	 	Mesure[13];
		unsigned char 		DataUploadState;
		TCP_SOCKET 			DataUploadSocket;
		DWORD				DataUploadTimer;
		unsigned int		Envois_Demandes;
		unsigned int		Envois_Effectues;
		unsigned int		Erreurs;
		unsigned char		Last_Erreur;
		time_t				Last_Send_Ok;
		
   } STRUCT_SOCKET_BD_CURL;

    // STRUCTURE RELAIS MANUEL    
    typedef struct
    {  
	    unsigned char	Pilotable;	// Indique si on peux piloter le relais manuellement (1) ou non (0)	
        unsigned char   Relais;     // Etat Relais
        time_t  		Time;   	// Horodatage du retour )à l'état off, ou 0 si état permanent
    } STRUCT_RELAIS_MAN;


	// Variables globales
	#if !defined(MAIN_SPARKBOX)
		extern 	APP_CONFIG 			AppConfig;
		extern 	ROM BYTE 			SerializedMACAddress[6];
		extern 	STRUCT_SPARKBOX		Sparkbox;
		extern 	APP_CONFIG 			AppConfig;
		extern 	APP_CONFIG 			NewAppConfig;
		extern 	STRUCT_USER 		User;
		extern  STRUCT_RELAIS_MAN	Relais_Man[NB_RELAIS_MAX];
		extern	unsigned int 		cpt1s;         	// compteur secondes	
		extern	unsigned int 		cpt1m;         	// compteur minutes	
		extern  unsigned int 		cpt1ms;  		// Compteur en milli-secondes, débordement 49 jours // TODO tester débordement
		extern  unsigned int 		nb_heures;	
		extern  unsigned int		debug_ui1;
		extern  unsigned int		debug_ui2;
		extern  unsigned int		debug_ui3;
		extern  unsigned int		debug_ui4;	
		extern  unsigned int		debug_ui5;
		extern  short				debug_s1;
		extern  unsigned short  	loop_count_mem;	
		extern  STRUCT_DATE_ADTEK 	utc;
		extern  unsigned char		CARTE;
		extern  unsigned char		VERSION_HARD;
		extern  unsigned char		NB_RELAIS;
		extern  unsigned char		FONCTION;
		extern  unsigned char		Mode_Admin;
		extern  unsigned int		Mode_Admin_cpt1s;
		extern  ANALOG_TAB			analogCalc;
		extern unsigned char		OPTO1_FILTRE;
		extern unsigned char		OPTO2_FILTRE;
		extern unsigned char		BP_FILTRE;
		extern unsigned char		NomFichierIndex[20]; // Nom fichier d'index
		extern unsigned char		Date_Ind[5];		// Date du fichier d'index à récupérer
		extern unsigned int			cpt1s_Ind;		// cpt1s pour fichier d'index a récupérer
	#else
		APP_CONFIG 		    AppConfig;
		ROM BYTE 			SerializedMACAddress[6] = {MY_DEFAULT_MAC_BYTE1, MY_DEFAULT_MAC_BYTE2, MY_DEFAULT_MAC_BYTE3, MY_DEFAULT_MAC_BYTE4, MY_DEFAULT_MAC_BYTE5, MY_DEFAULT_MAC_BYTE6};
		STRUCT_SPARKBOX		Sparkbox;
		APP_CONFIG 		    AppConfig;
		STRUCT_USER 		User;
		STRUCT_RELAIS_MAN	Relais_Man[NB_RELAIS_MAX];
		unsigned int        cpt1s = 0;         // compteur secondes, débordement 136 années 
		unsigned int 		cpt1m;       	   // compteur minutes remis à zéro tous les jours
		unsigned int 		cpt1ms = 0;			// Compteur en milli-secondes, débordement 49 jours // TODO tester débordement
		unsigned int 		nb_heures = 0;	
		unsigned int		debug_ui1 = 0;
		unsigned int		debug_ui2 = 0;
		unsigned int		debug_ui3 = 0;
		unsigned int		debug_ui4 = 0;	
		unsigned int		debug_ui5 = 0;
		short				debug_s1 = 0;
		unsigned char		CARTE = 0;
		unsigned char		VERSION_HARD = 0;
		unsigned char		NB_RELAIS = 0;
		unsigned char		FONCTION = 0;
		unsigned char		Mode_Admin = 0;
		unsigned int		Mode_Admin_cpt1s = 0;
		ANALOG_TAB			analogCalc;
		unsigned char		OPTO1_FILTRE = 1;
		unsigned char		OPTO2_FILTRE = 1;
		unsigned char		BP_FILTRE = 1;
		unsigned char		NomFichierIndex[20]; // Nom fichier d'index
		unsigned char		Date_Ind[5];		// Date du fichier d'index à récupérer
		unsigned int		cpt1s_Ind = 0;		// cpt1s pour fichier d'index a récupérer
	#endif
	
	// fonctions
	void 			Process_SNTP(void);
    void     		Raz_Usine(void);

#endif 

