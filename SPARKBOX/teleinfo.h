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
#ifndef TELEINFO_H
	#define TELEINFO_H

	#include "TCPIP Stack/TCPIP.h"
	#include "rs232.h"
    
    #define NB_TELEINFO     2              	// Nombre de ports téléinfo câblés
    #define TELEINFO_PAC	0				// Compteur dédié PAC
    
    // Adresse
    #define ADCO            "ADCO"
    
    // Tarif et réponses associées
    #define OPTARIF         "OPTARIF"
    #define BASE            "BASE"
    #define HC              "HC.."
    #define EJP             "EJP."
    #define TEMPO           "BBRx"          // Attention, le dernier caractère est variable selon la programmation du compteur !
    
    // Index
    #define HCHC            "HCHC"          // Heures creuses
    #define HCHP            "HCHP"          // Heures pleines
    #define EJPHN           "EJPHN"         // EJP heures normales
    #define EJPHPM          "EJPHPM"        // EJP heurese de pointe
    #define BBRHCJB         "BBRHCJB"       // Heures creuses jours bleus
    #define BBRHPJB         "BBRHPJB"       // Heures pleines jours bleus
    #define BBRHCJW         "BBRHCJW"       // Heures creuses jours blancs
    #define BBRHPJW         "BBRHPJW"       // Heures pleines jours blancs
    #define BBRHCJR         "BBRHCJR"       // Heures creuses jours rouges
    #define BBRHPJR         "BBRHPJR"       // Heures pleines jours rouges
    
    #define PEJP            "PEJP"          // Préavis EJP
    
    #define DEMAIN          "DEMAIN"        // Couleur du lendemain
    #define BLEU            "BLEU"
    #define BLANC           "BLAN"
    #define ROUGE           "ROUG"
    
    #define IISNT           "IINST"         // Intensité instantanée
    #define IISNT1          "IINST1"        // Intensité instantanée
    #define IISNT2          "IINST2"        // Intensité instantanée
    #define IISNT3          "IINST3"        // Intensité instantanée
    #define ADIR1           "ADIR1"         // Avertissement dépassement
    #define ADIR2           "ADIR2"         // Avertissement dépassement
    #define ADIR3           "ADIR3"         // Avertissement dépassement
    #define ADPS            "ADPS"          // Avertissement dépassement
    #define IMAX            "IMAX"          // Intensité maximale
    #define IMAX1           "IMAX3"         // Intensité maximale
    #define IMAX2           "IMAX2"         // Intensité maximale
    #define IMAX3           "IMAX3"         // Intensité maximale
    #define HHPHC           "HHPHC"         // Horaire heure pleine heure creuse
    #define PAPP            "PAPP"          // Puissance apparente
    #define PMAX            "PMAX"          // Puissance maximale
    #define PPOPT           "PPOT"          // Présence des potentiels
    
    // Période tarifaire en cours
    #define PTEC            "PTEC"
    #define TH              "TH.."          // Toutes les heures
    //#define HC              "HC.."        // Déjà défini
    #define HP              "HP.."
    #define HN              "HN.."          // Heures normales
    #define PM              "PM.."          // Pointe mobile
    #define HCJB            "HCJB"          // Heures creuses jours bleus
    #define HPJB            "HPJB"          // Heures pleines jours bleus
    #define HCJW            "HCJW"          // Heures creuses jours blancs
    #define HPJW            "HPJW"          // Heures pleines jours blancs
    #define HCJR            "HCJR"          // Heures creuses jours rouges
    #define HPJR            "HPJR"          // Heures pleines jours rouges
    
    #define PTEC_NONE       0				// Pas de PTEC Connue
    #define PTEC_TH         1		        // Toutes les heures
    #define PTEC_HC         2        		// HC
    #define PTEC_HP         4				// HC	
    #define PTEC_HN         8          		// EJP Heures normales
    #define PTEC_PM         16         		// EJP Pointe mobile
    #define PTEC_HCJB       32          	// Heures creuses jours bleus
    #define PTEC_HPJB       64          	// Heures pleines jours bleus
    #define PTEC_HCJW       128          	// Heures creuses jours blancs
    #define PTEC_HPJW       256         	// Heures pleines jours blancs
    #define PTEC_HCJR       512          	// Heures creuses jours rouges
    #define PTEC_HPJR       1024          	// Heures pleines jours rouges   
    #define PTEC_ALL		65535			// Annule l'action de la ptec dans la gestion de la relève
  
    
    // Mot d'état
    #define MOTDETAT        "MOTDETAT"
        
    #define ISOUSC          "ISOUSC"
     
    // Longeur des réponses associées
    #define L_ADCO          12
    #define L_OPTARIF       4
    #define L_INDEX         9
    #define L_PTEC          4
    #define L_MOTDETAT      6
    
    #define L_ISOUSC        2
    #define L_PEJP          2
    #define L_DEMAIN        4
    #define L_IINST         3
    #define L_ADPS          3
    #define L_IMAX          3
    #define L_PMAX			5
    #define L_HHPHC			1
    #define L_PAPP          5 
    #define L_PPOT			2   
    
    // Début et fin de trame
	#define TELE_STX				0x02                // Début de trame
	#define TELE_ETX				0x03                // Fin de trame
    #define TELE_EOT                0x04                // Interruption de trame, reprise avec STX
    
    #define TELE_SP                 0x20                // Séparateur de champ
    #define TELE_LF                 0x0A                // Début de groupe
    #define TELE_CR                 0x0D                // Fin de groupe
    
	// Def 
    #define SIZE_GROUP_TELE         32    
    #define TARIF_BASE              "BASE"    
    
    typedef struct _TRAME_TELE
    {
        unsigned char   ptr;
        unsigned char   data[SIZE_GROUP_TELE];
        unsigned char   crc;
    } TRAME_TELE;
          
	// Def machine d'état liaison série
	typedef enum _TELE_STATE
	{
		TELE_WAIT, TELE_RCV
	} TELE_STATE;
   
    typedef struct 
    {
	    unsigned char   etat;			//  1 	Etat de la connection au téléinfo!	
	    unsigned char	adco[13];		//  2 	N° identification Compteur
		unsigned char	optarif[5];		//  3 	Option tarifaire 
        unsigned char	isousc[3];		//  4 	Intensité souscrite 
        unsigned char	base[10];		//  5 	Index (base)
        unsigned char	hc_hc[10];		//  6 	Index Heures Creuses (heures creuses)
        unsigned char	hc_hp[10];		//  7 	Index Heures Pleines (heures creuses)
        unsigned char	ejp_hn[10];		//  8 	Index Heures Normales (EJP)
        unsigned char	ejp_hpm[10];	//  9 	Index Heures de Pointes Mobiles (EJP)      
        unsigned char	bbr_hc_jb[10];	// 10 	Index Heures Creuses Jours Bleus  (Tempo)
        unsigned char	bbr_hp_jb[10];	// 11 	Index Heures Pleines Jours Bleus  (Tempo)
        unsigned char	bbr_hc_jw[10];	// 12 	Index Heures Creuses Jours Blancs (Tempo)
        unsigned char	bbr_hp_jw[10];	// 13 	Index Heures Pleines Jours Blancs (Tempo)        
        unsigned char	bbr_hc_jr[10];	// 14 	Index Heures Creuses Jours Rouges (Tempo)
        unsigned char	bbr_hp_jr[10];	// 15 	Index Heures Pleines Jours Rouges (Tempo)
        unsigned char	pejp[3];		// 16 	Préavis EJP
        unsigned char	ptec[5];		// 17 	Période Tarifaire en Cours
        unsigned char	demain[5];		// 18	Couleur du lendemaine (Tempo)
        unsigned char	iinst1[4];		// 191 	Intensité instantanée
        unsigned char	iinst2[4];		// 192 	Intensité instantanée
        unsigned char	iinst3[4];		// 193 	Intensité instantanée
        unsigned char	adps[4];		// 20 	Avertissement de dépassement de la puissance souscrite (ampérage)
        unsigned char	imax1[4];		// 211	Intensité maximale
        unsigned char	imax2[4];		// 212	Intensité maximale
        unsigned char	imax3[4];		// 213	Intensité maximale
        unsigned char	pmax[6];		// 214	Puissance maximale appelée (Triphasé)
        unsigned char	papp[6];		// 22	Puissance apparente (Volt/Ampères)
        unsigned char	hhphc[2];		// 23	Groupe horaire (si Heures Creuse ou Tempo)(A,C,D,E,Y))
        unsigned char	motdetat[7];	// 24	Mot D'état
        unsigned char	ppot[3];		// 25 	Présence des potentiels   
        unsigned char   monitoring;		// 26	Indique quel champ est "monitoré"
        unsigned int 	erreur;  		// 28	Compteur d'erreurs
        unsigned char	fonction;		// Numéro si Capteur
        unsigned char 	id;				// Si associé a un capteur l'ID définit le champ utilisé (IINST,ADCO,....)
        unsigned char	ptec_sav[5];	// Sauvegarde du précédent PTEC
        unsigned short	ptec_short;		// ptec converti
        unsigned int	last_cpt1s;		// Horodatage de la dernière trame
        unsigned int	nISousc;		// Intensité souscrite sur un uint
        // 40 = puissance instantanée sur une minute
        // 41 = index (cumul)
  		// Variables calculées et non fournie par le compteur Téléinfo !
        unsigned int 	calc_puis; 		// Puissance instantanée
        unsigned int 	calc_cpt1s;		// Copie de cpt1s à chaque réception de trame pour détecter une rupture de com
        unsigned int    calc_index;		// Somme des index !
        unsigned int    calc_iinst;		// Somme des iinst!
        unsigned int 	calc_max_papp;	// Max de papp sur la journée 
        unsigned int 	calc_papp;		// papp version int!		
        unsigned int 	calc_max_puis;	// Max de Imax sur la journée
        unsigned char	calc_index_char[12];	
        // Les valeurs en string
        unsigned char	calc_puis_s[6];
        //unsigned char	calc_iinst_s[6];
        //unsigned char	calc_papp_s[6];
    } STRUCT_INFO_COMPTEUR;	
    
    extern STRUCT_INFO_COMPTEUR Compteur[NB_TELEINFO];
        
	// Prototypes de fonction
    void 			TeleInit( void );
    void 			Process_Tele( void );
    void 			Process_Jour_Tele( void );
    unsigned char 	*WattToKwatt(BYTE* str);
    unsigned char 	*PtecToString(unsigned char no_tele);
    unsigned char 	*OptarifToString(unsigned char no_tele);
    void 			Process_Calcul_Teleinfo(unsigned char port);
    void 			Process_Calcul_Index(unsigned char port);
    void 			Process_Calcul_iinst(unsigned char port);
#endif

