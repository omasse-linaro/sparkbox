// TELEINFO.C
// Gestion des données Téléinfo du compteur électronique
// 1/12/2010	Gestion de la PTEC et envoi au process de relève PAC
#include "Teleinfo.h"
#include <plib.h>
#include "rs232.h"          // Pour le buffer de réception
#include "0_ADTEK.h"
#include "Stat_Pv.h"
#include <string.h>

// Trames de réception teleinfo
TRAME_TELE 				CurrentMessage[NB_TELEINFO];
unsigned char 			ValidMessage[NB_TELEINFO][SIZE_GROUP_TELE];

TELE_STATE 				Tele_State[NB_TELEINFO];
unsigned short 			error_crc[NB_TELEINFO];      // Pour debug
// Structure des compteurs Téléinfo
STRUCT_INFO_COMPTEUR	Compteur[NB_TELEINFO];	// Structure qui contient le résultat des 2 compteurs
unsigned short			ptec_short;

unsigned char out[40]; // Sert pour la convertion Watt -> Kwatt xxxxxxyyy (xxxxxx,yyy) + Fonctions de convertion vers string
unsigned int  cpt_tele;
unsigned int  index_lu;
unsigned int  index_sav;
unsigned int  index_ecart;

// Prototypes fonctions
void Process_Trame_Tele( unsigned char* trame, STRUCT_INFO_COMPTEUR* compteur ,unsigned char port);
void Efface_Compteur_Tele(unsigned char no_tele );
void PuissanceToStr(unsigned int p,unsigned char* out);


//*************************************************************************************************
// *
// *  TeleInit : 
// *
// *  Author              Date         	Comment
// *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// * Hervé DELAY 		    05/10/2010 		0.0.0   Première version
// * Hervé DELAY 		    23/10/2010 		0.0.1   Ajout multi port
// *
// **************************************************************************************************
void TeleInit( void )
{
    unsigned char selPort;
    
    for ( selPort = 0; selPort < NB_TELEINFO; selPort++ )
    {
	    CurrentMessage[selPort].ptr 	= 0;   
        ValidMessage[selPort][0] 		= 0;      
        error_crc[selPort] 				= 0;
    
    	Compteur[selPort].etat			= CAPTEUR_DEMARRAGE;
        Compteur[selPort].erreur		= 0;     
		Efface_Compteur_Tele(selPort);  // Effacement des infos du télérelevé  
        Compteur[selPort].fonction		= 0; 
        Compteur[selPort].id			= 0; 
        Compteur[selPort].base[0]		= 0x00;
        Compteur[selPort].ptec_sav[0]	= 0x00;
        Compteur[selPort].cpt_teleinfo 	= cpt1s; 
        // Variables calculées
        Compteur[selPort].calc_puissance_instantanee = 0;
        // On lance le calcul d'un index cumulé
        //Process_Calcul_Index(selPort);     
        cpt_tele = 0;
    }
}

//**************************************************************************************************
// *  Process_Tele : 	Traitement journalier des structures
//
void Process_Jour_Tele( void )
{
static unsigned char selPort;
    
    for ( selPort = 0; selPort < NB_TELEINFO; selPort++ )
    {
        //CurrentMessage[selPort].ptr = 0;   
        //ValidMessage[selPort][0] = 0;      
        //error_crc[selPort] = 0;
        Compteur[selPort].erreur = 0;     
    }
}


//**************************************************************************************************
// *
// *  Process_Tele : 	traitement des données reçues sur le port série
// *                     			
// *                      
// *  Author              Date         	Comment
// *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// * Hervé DELAY 		    05/10/2010 		0.0.0   Première version
// * Hervé DELAY 		    23/10/2010 		0.0.1   Ajout multi port
// *
// **************************************************************************************************


void Process_Tele( void )
  {
    unsigned char portTele;
	unsigned char i;
    unsigned char j;
    unsigned char message = 0;          // Nombre de message lus
    
    unsigned char nbReceived;
    unsigned char tempRS[RS232_BUFFER_SIZE];

    
    
    for ( portTele = 0; portTele < NB_TELEINFO ; portTele++ )
    {   
        // Réinitialisation du message définitif
        ValidMessage[portTele][0] = 0;
    
        // Lecture des données reçues sur le port série
        nbReceived = UartIsReadReady( portTele ); // Nombre de caractères prêts à lire, maximum 32 dans "rs232.h"
        if ( nbReceived > 0 )                     // On teste si on a reçu des données
        {
            UartRead ( portTele, (void *) tempRS, nbReceived );
        
            // Recopie dans une trame temporaire, analyse et transfert dans la trame finale si complet
            i = 0;
            while ( i < nbReceived )
            {
        
                switch ( Tele_State[portTele] )
                {
                    case TELE_WAIT :
                        if (  tempRS[i++] == TELE_LF )               // Recherche caractère de début de groupe
                        {
                            CurrentMessage[portTele].ptr = 0;
                            CurrentMessage[portTele].crc = 0;
                            Tele_State[portTele] = TELE_RCV;
                        }
                        break;
                    
                    case TELE_RCV :
                        if ( tempRS[i] == TELE_CR )                 // Recherche fin de groupe
                        {
                            if ( CurrentMessage[portTele].ptr > 1 )           // 2 caractères reçus est le strict minimum pour tester le CRC !!
                            {
                                // Contrôle du CRC
                                for ( j = 0; j < ( CurrentMessage[portTele].ptr - 2 ); j++ )      // Le dernier caractère de la chaîne est le crc, il ne faut pas le prendre
                                {                                                       // Etiquette 0x20 Data 0x20 crc
                                    CurrentMessage[portTele].crc += CurrentMessage[portTele].data[j];       // Le crc se calcule de l'étiquette à la data (pas le dernier 0x20 !), masque 0x3F et +0x20
                                }
                                CurrentMessage[portTele].crc &= 0x3F;
                                CurrentMessage[portTele].crc += 0x20;
                            
                                if ( CurrentMessage[portTele].data[CurrentMessage[portTele].ptr - 1] == CurrentMessage[portTele].crc )
                                {
                                    // Ajout du fin de chaîne
                                    CurrentMessage[portTele].data[CurrentMessage[portTele].ptr - 2] = 0;
                                
                                    // Recopie de la trame temporaire dans la trame définitive
                                    memcpy ( ValidMessage[portTele], CurrentMessage[portTele].data, (CurrentMessage[portTele].ptr - 1) );
                        
                                    // Si plusieurs groupes trouvés, seul le dernier est conservé
                                    message++; // Ce compteur permet de détecter un overflow
                                    Process_Trame_Tele(ValidMessage[portTele], &Compteur[portTele],portTele);
                                    Compteur[portTele].cpt_teleinfo = cpt1s; // On remet à zéro le compteur de temps
                                    Compteur[portTele].etat			= CAPTEUR_OK;
                                }
                                else
                                {
                                    error_crc[portTele]++;            // Pour debug
                                }
                            
                            }
                        
                            Tele_State[portTele] = TELE_WAIT;
                        }
                        else
                        {
                            if ( CurrentMessage[portTele].ptr < ( SIZE_GROUP_TELE - 1 ) )                  // Test débordement
                            {
                                CurrentMessage[portTele].data[CurrentMessage[portTele].ptr++] = tempRS[i];        // Recopie de la donnée en chaîne temporaire
                            }
                            else
                            {
                                CurrentMessage[portTele].ptr = 0;
                                Tele_State[portTele] = TELE_WAIT;
                            }
                        }
                    
                        i++;
                    
                        break;
                    
                    default :
                        Tele_State[portTele] = TELE_WAIT;
                        break;  
                }
            }
        }
        if ((cpt1s - Compteur[portTele].cpt_teleinfo) > 15) // Pas de Téléinfo depuis plus de 10s
        {
        	//On efface la structure
        	Efface_Compteur_Tele(portTele);
        	Compteur[portTele].etat	= CAPTEUR_ABSENT;
        	Regul.Capteur[T_PUISS].Etat == CAPTEUR_ABSENT;
        	Compteur[portTele].ptec_sav[0]	= 0x00;
        }   
    }
}

// ********************************************************************************************************
// *
// *  Process_Trame_Tele : 	traitement d'une trame téléinfo
// *
// ********************************************************************************************************
void Process_Trame_Tele(unsigned char* trame, STRUCT_INFO_COMPTEUR* compteur, unsigned char port)
{
    unsigned char longueur_trame;
    unsigned char longueur_etiquette;
    unsigned char longueur_valeur;
    unsigned char * separateur;
    
    longueur_trame = strlen(trame);    
    separateur = strstr( trame, " " );             // On cherche la fin de l'étiquette, l'espace qui est le séparateur  
    longueur_etiquette = (separateur - trame);   
    
    if ( longueur_trame > longueur_etiquette )        
    {
        longueur_valeur = longueur_trame - longueur_etiquette - 1;
         
        if ( strncmp ( (char *) trame, (ROM char *) "ADCO", 4 ) == 0 && longueur_valeur == L_ADCO )
        {
            memcpy ( compteur->adco, (separateur + 1), longueur_valeur );		// recopie de la valeur
            compteur->adco[longueur_valeur] = 0;                                 // Fin de chaîne
        }   
        else if ( strncmp ( (char *) trame, (ROM char *) "OPTARIF", 7 ) == 0 && longueur_valeur == L_OPTARIF )
        {
            memcpy ( compteur->optarif, (separateur + 1), longueur_valeur );		
            compteur->optarif[longueur_valeur] = 0;                                
        }     
        else if ( strncmp ( (char *) trame, (ROM char *) "ISOUSC", 6 ) == 0 && longueur_valeur == L_ISOUSC )
        {
            memcpy ( compteur->isousc, (separateur + 1), longueur_valeur );		
            compteur->isousc[longueur_valeur] = 0;                                
        } 
        else if ( strncmp ( (char *) trame, (ROM char *) "BASE", 4 ) == 0 && longueur_valeur == L_INDEX )
        {
            memcpy ( compteur->base, (separateur + 1), longueur_valeur );        	
            compteur->base[longueur_valeur] = 0;  
            if (port == 0) // TELE1   
            {
            	if (cpt_tele == 0)
            	{
	            	cpt_tele = cpt1s+60; // 60 1 minute
	            	index_sav = atoi(Compteur[0].base);
	            }	 
	   	        else if (cpt1s >= cpt_tele)
	            {
		            index_lu = atoi(Compteur[0].base);
		            if (index_lu > index_sav)
		            {
			            
	            		index_ecart = ((index_lu-index_sav) * (3600 / (60+(cpt1s-cpt_tele))));
	            	}
	            	else
	            	{
	            		index_ecart = 0;
	            	}	
	            	PuissanceToStr(index_ecart, Regul.Capteur[T_PUISS].Temperature_s);// valeur en string
	            	Regul.Capteur[T_PUISS].Temperature = index_ecart;
	            	// Record instantané battu !
	            	if (index_ecart > Stat_Max_Inst.valeur)	
	            	{
	            	 	Stat_Max_Inst.valeur =	index_ecart;
	            	 	Stat_Max_Inst.tdate  =  utc.utc_fr;
	            	}
	            	index_sav = index_lu;
	            	cpt_tele = cpt1s+60; // 1 minute sup
	            	Regul.Capteur[T_PUISS].Etat = CAPTEUR_OK;
	            }
            }                                                   
        }      
        else if( strncmp ( (char *) trame, (ROM char *) "HCHP", 4 ) == 0 && longueur_valeur == L_INDEX )
        {
            memcpy ( compteur->hc_hp, (separateur + 1), longueur_valeur );        	
            compteur->hc_hp[longueur_valeur] = 0;                                
        } 
        else if ( strncmp ( (char *) trame, (ROM char *) "HCHC", 4 ) == 0 && longueur_valeur == L_INDEX )
        {
            memcpy ( compteur->hc_hc, (separateur + 1), longueur_valeur );        	
            compteur->hc_hc[longueur_valeur] = 0;
        }   
        else if ( strncmp ( (char *) trame, (ROM char *) "EJPHN", 5 ) == 0 && longueur_valeur == L_INDEX )
        {
            memcpy ( compteur->ejp_hn, (separateur + 1), longueur_valeur );        	
            compteur->ejp_hn[longueur_valeur] = 0;
        }
        else if ( strncmp ( (char *) trame, (ROM char *) "EJPHPM", 6 ) == 0 && longueur_valeur == L_INDEX )
        {
            memcpy ( compteur->ejp_hpm, (separateur + 1), longueur_valeur );        	
            compteur->ejp_hpm[longueur_valeur] = 0;
        }   
        else if ( strncmp ( (char *) trame, (ROM char *) "BBRHPJB", 7 ) == 0 && longueur_valeur == L_INDEX )
        {
            memcpy ( compteur->bbr_hp_jb, (separateur + 1), longueur_valeur );        	
            compteur->bbr_hp_jb[longueur_valeur] = 0;
        }     
        else if ( strncmp ( (char *) trame, (ROM char *) "BBRHCJB", 7 ) == 0 && longueur_valeur == L_INDEX )
        {
            memcpy ( compteur->bbr_hc_jb, (separateur + 1), longueur_valeur );        	
            compteur->bbr_hc_jb[longueur_valeur] = 0;
        }      
        else if ( strncmp ( (char *) trame, (ROM char *) "BBRHPJW", 7 ) == 0 && longueur_valeur == L_INDEX )
        {
            memcpy ( compteur->bbr_hp_jw, (separateur + 1), longueur_valeur );        	
            compteur->bbr_hp_jw[longueur_valeur] = 0;
        }        
        else if ( strncmp ( (char *) trame, (ROM char *) "BBRHCJW", 7 ) == 0 && longueur_valeur == L_INDEX )
        {
            memcpy ( compteur->bbr_hc_jw, (separateur + 1), longueur_valeur );        	
            compteur->bbr_hc_jw[longueur_valeur] = 0;
        }     
        else if ( strncmp ( (char *) trame, (ROM char *) "BBRHPJR", 7 ) == 0 && longueur_valeur == L_INDEX )
        {
            memcpy ( compteur->bbr_hp_jr, (separateur + 1), longueur_valeur );        	
            compteur->bbr_hp_jr[longueur_valeur] = 0;
        }       
        else if ( strncmp ( (char *) trame, (ROM char *) "BBRHCJR", 7 ) == 0 && longueur_valeur == L_INDEX )
        {
            memcpy ( compteur->bbr_hc_jr, (separateur + 1), longueur_valeur );        	
            compteur->bbr_hc_jr[longueur_valeur] = 0;
        }
        else if ( strncmp ( (char *) trame, (ROM char *) "PEJP", 4 ) == 0 && longueur_valeur == L_PEJP )
        {
            memcpy ( compteur->pejp, (separateur + 1), longueur_valeur );        	
            compteur->pejp[longueur_valeur] = 0;
        }
        else if ( strncmp ( (char *) trame, (ROM char *) "PTEC", 4 ) == 0 && longueur_valeur == L_PTEC )
	    {
            memcpy ( compteur->ptec, (separateur + 1), longueur_valeur );        	
            compteur->ptec[longueur_valeur] = 0;
            // PTEC est utilisé par la Relève. pour TELE1 on fait suivre les info si necessaire.
            if (port == 0) 
            {	// TELE 1
	        	if ((compteur->ptec[0] != compteur->ptec_sav[0]) || (compteur->ptec[1] != compteur->ptec_sav[1]) || 
	        		(compteur->ptec[2] != compteur->ptec_sav[2]) || (compteur->ptec[3] != compteur->ptec_sav[3])) 
	            {
	            	// La période tarifaire en cours a changé
	            	memcpy(compteur->ptec_sav,compteur->ptec,4);
	            	compteur->ptec_sav[4] = 0x00;
	            	ptec_short = PTEC_NONE;
	            	// On traduit en masque short
	            	if (memcmp(compteur->ptec,TH,2) == 0) 	{ ptec_short = PTEC_TH; }
	            	if (memcmp(compteur->ptec,HP,2) == 0) 	{ ptec_short = PTEC_HP; }
	            	if (memcmp(compteur->ptec,HC,2) == 0) 	{ ptec_short = PTEC_HC; }
	            	if (memcmp(compteur->ptec,HN,2) == 0) 	{ ptec_short = PTEC_HN; }
	            	if (memcmp(compteur->ptec,PM,2) == 0) 	{ ptec_short = PTEC_PM; }
	            	if (memcmp(compteur->ptec,HCJB,4) == 0) { ptec_short = PTEC_HCJB; }
	            	if (memcmp(compteur->ptec,HPJB,4) == 0) { ptec_short = PTEC_HPJB; }
	            	if (memcmp(compteur->ptec,HCJW,4) == 0) { ptec_short = PTEC_HCJW; }
	            	if (memcmp(compteur->ptec,HPJW,4) == 0) { ptec_short = PTEC_HPJW; }
	           		if (memcmp(compteur->ptec,HCJR,4) == 0) { ptec_short = PTEC_HCJR; }
	            	if (memcmp(compteur->ptec,HPJR,4) == 0) { ptec_short = PTEC_HPJR; }	            	
	            }
            }
        }        
        else if ( strncmp ( (char *) trame, (ROM char *) "DEMAIN", 6 ) == 0 && longueur_valeur == L_DEMAIN )
        {
            memcpy ( compteur->demain, (separateur + 1), longueur_valeur );        	
            compteur->demain[longueur_valeur] = 0;
        } 
        else if ( strncmp ( (char *) trame, (ROM char *) "IINST", 5 ) == 0 && longueur_valeur == L_IINST )
        {
            memcpy ( compteur->iinst1, (separateur + 1), longueur_valeur );        	
            compteur->iinst1[longueur_valeur] = 0;
        }
        else if ( strncmp ( (char *) trame, (ROM char *) "IINST1", 6 ) == 0 && longueur_valeur == L_IINST )
        {
            memcpy ( compteur->iinst1, (separateur + 1), longueur_valeur );        	
            compteur->iinst1[longueur_valeur] = 0;
        }
        else if ( strncmp ( (char *) trame, (ROM char *) "IINST2", 6 ) == 0 && longueur_valeur == L_IINST )
        {
            memcpy ( compteur->iinst2, (separateur + 1), longueur_valeur );        	
            compteur->iinst2[longueur_valeur] = 0;
        }
        else if ( strncmp ( (char *) trame, (ROM char *) "IINST3", 6 ) == 0 && longueur_valeur == L_IINST )
        {
            memcpy ( compteur->iinst3, (separateur + 1), longueur_valeur );        	
            compteur->iinst3[longueur_valeur] = 0;
        }
        else if ( strncmp ( (char *) trame, (ROM char *) "ADPS", 4 ) == 0 && longueur_valeur == L_ADPS )
        {
            memcpy ( compteur->adps, (separateur + 1), longueur_valeur );        	
            compteur->adps[longueur_valeur] = 0;
        }               
        else if ( strncmp ( (char *) trame, (ROM char *) "IMAX", 4 ) == 0 && longueur_valeur == L_IMAX )
        {
            memcpy ( compteur->imax1, (separateur + 1), longueur_valeur );        	
            compteur->imax1[longueur_valeur] = 0;
        }
        else if ( strncmp ( (char *) trame, (ROM char *) "IMAX1", 5 ) == 0 && longueur_valeur == L_IMAX )
        {
            memcpy ( compteur->imax1, (separateur + 1), longueur_valeur );        	
            compteur->imax1[longueur_valeur] = 0;
        }
        else if ( strncmp ( (char *) trame, (ROM char *) "IMAX2", 5 ) == 0 && longueur_valeur == L_IMAX )
        {
            memcpy ( compteur->imax2, (separateur + 1), longueur_valeur );        	
            compteur->imax2[longueur_valeur] = 0;
        }
        else if ( strncmp ( (char *) trame, (ROM char *) "IMAX3", 5 ) == 0 && longueur_valeur == L_IMAX )
        {
            memcpy ( compteur->imax2, (separateur + 1), longueur_valeur );        	
            compteur->imax3[longueur_valeur] = 0;
        }
        else if ( strncmp ( (char *) trame, (ROM char *) "PMAX", 4 ) == 0 && longueur_valeur == L_PMAX )
        {
            memcpy ( compteur->pmax, (separateur + 1), longueur_valeur );        	
            compteur->pmax[longueur_valeur] = 0;
        }
        else if ( strncmp ( (char *) trame, (ROM char *) "PAPP", 4 ) == 0 && longueur_valeur == L_PAPP )
        {
            memcpy ( compteur->papp, (separateur + 1), longueur_valeur );        	
            compteur->papp[longueur_valeur] = 0;
        }
        else if ( strncmp ( (char *) trame, (ROM char *) "HHPHC", 5 ) == 0 && longueur_valeur == L_HHPHC )
        {
            memcpy ( compteur->hhphc, (separateur + 1), longueur_valeur );        	
            compteur->hhphc[longueur_valeur] = 0;
        }       
        else if ( strncmp ( (char *) trame, (ROM char *) "MOTDETAT", 8 ) == 0 && longueur_valeur == L_MOTDETAT )
        {
            memcpy ( compteur->motdetat, (separateur + 1), longueur_valeur );        	
            compteur->motdetat[longueur_valeur] = 0;
        }
        else if ( strncmp ( (char *) trame, (ROM char *) "PPOT", 4 ) == 0 && longueur_valeur == L_PPOT )
        {
            memcpy ( compteur->ppot, (separateur + 1), longueur_valeur );        	
            compteur->ppot[longueur_valeur] = 0;
        }      
        else
        {
        	compteur->erreur++;
        }  
    }
}

//*******************************************************
//
// Remise à zéro de la structure Téléinfo !
//
//*******************************************************
void Efface_Compteur_Tele(unsigned char no_tele )
{
    unsigned char selPort;
    
    if ( no_tele < NB_TELEINFO )
    {
        Compteur[no_tele].adco[0] = 0;                                	
        Compteur[no_tele].optarif[0] = 0;                                
        Compteur[no_tele].isousc[0] = 0;                                        	
        Compteur[no_tele].base[0] = 0;                                     	
        Compteur[no_tele].hc_hp[0] = 0;                                         	
        Compteur[no_tele].hc_hc[0] = 0;          	
        Compteur[no_tele].ejp_hn[0] = 0;           	
        Compteur[no_tele].ejp_hpm[0] = 0;      	
        Compteur[no_tele].bbr_hp_jb[0] = 0;           	
        Compteur[no_tele].bbr_hc_jb[0] = 0;          	
        Compteur[no_tele].bbr_hp_jw[0] = 0;              	
        Compteur[no_tele].bbr_hc_jw[0] = 0;        	
        Compteur[no_tele].bbr_hp_jr[0] = 0;         	
        Compteur[no_tele].bbr_hc_jr[0] = 0;             	
        Compteur[no_tele].pejp[0] = 0;        	
        Compteur[no_tele].ptec[0] = 0;       	
        Compteur[no_tele].demain[0] = 0;       	
        Compteur[no_tele].iinst1[0] = 0;
        Compteur[no_tele].iinst2[0] = 0;
        Compteur[no_tele].iinst3[0] = 0;
        Compteur[no_tele].adps[0] = 0;      	
        Compteur[no_tele].imax1[0] = 0; 
        Compteur[no_tele].imax2[0] = 0;
        Compteur[no_tele].imax3[0] = 0;          	
        Compteur[no_tele].papp[0] = 0;              	
        Compteur[no_tele].hhphc[0] = 0;            	
        Compteur[no_tele].motdetat[0] = 0;       	
        Compteur[no_tele].ppot[0] = 0;  
        Compteur[no_tele].pmax[0] = 0;  
    }
}


//*******************************************************
//
// WattToKwat
// Convertion de l'index Téléinfo en Watt vers des Kwatt en gardant la virgule
//
//*******************************************************
unsigned char *WattToKwatt(BYTE* str)
{
	out[0]=0x00;
	
	// On ne copie que si on a une chaine de bonne longueur	
	// Penser a redimensionner out si on change la formule d'affichage
	if (strlen(str) == 9)
	{
		// On recopie la valeur en Watt
		strcpy(out,str);	// xxxxxxyyy
		out[9]	= 0x20;		// Espace
		out[10] = 0x28;		//(
		out[11] = str[0];
		out[12] = str[1];
		out[13] = str[2];
		out[14] = str[3];
		out[15] = str[4];
		out[16] = str[5];
		out[17] = 0x2C; 	// Insertion virgule
		out[18] = str[6];
		out[19] = str[7];
		out[20] = str[8];
		out[21]	= 0x29;		//)	
		out[22] = 0x20; 	// L'espace en fin est obligatoire ... mais je ne sais pas pourquoi
		out[23] = 0x00;
	}	
	return(out);
}

//*******************************************************
//
// PtecToString
// Convertion de la chaine PTEC en String
//
//*******************************************************
unsigned char *PtecToString(unsigned char no_tele) 			   
{
	strcpy(out,"");
	if(strcmp(Compteur[no_tele].ptec,"TH..") == 0)
	{
		strcat(out,"Toutes les Heures");
	}
	else if(strcmp(Compteur[no_tele].ptec,"HC..") == 0)
	{
		strcat(out,"Heures creuses");
	}
	else if(strcmp(Compteur[no_tele].ptec,"HP..") == 0)
	{
		strcat(out,"Heures pleines");
	}
	else if(strcmp(Compteur[no_tele].ptec,"HN..") == 0)
	{
		strcat(out,"Heures normales");
	}
	else if(strcmp(Compteur[no_tele].ptec,"PM..") == 0)
	{
		strcat(out,"Heures de pointe mobile");
	}
	else if(strcmp(Compteur[no_tele].ptec,"HCJB") == 0)
	{
		strcat(out,"Heures creuses Jours Bleus");
	}
	else if(strcmp(Compteur[no_tele].ptec,"HPJB") == 0)
	{
		strcat(out,"Heures pleines Jours Bleus");
	}
	else if(strcmp(Compteur[no_tele].ptec,"HCJW") == 0)
	{
		strcat(out,"Heures creuses Jours Blancs");
	}
	else if(strcmp(Compteur[no_tele].ptec,"HPJW") == 0)
	{
		strcat(out,"Heures pleines Jours Blancs");
	}
	else if(strcmp(Compteur[no_tele].ptec,"HCJR") == 0)
	{
		strcat(out,"Heures creuses Jours Rouges");
	}
	else if(strcmp(Compteur[no_tele].ptec,"HPJR") == 0)
	{
		strcat(out,"Heures pleines Jours Rouges");
	}	
	return(out);
} 

//*******************************************************
//
// OptarifToString
// Convertion de la chaine Optarif en String
//
////*******************************************************
unsigned char *OptarifToString(unsigned char no_tele) 
{
	strcpy(out,"");
	if(strcmp(Compteur[no_tele].optarif,"BASE") == 0)
	{
		strcat(out,"Option Base");
	}
	else if(strcmp(Compteur[no_tele].optarif,"HC..") == 0)
	{
		strcat(out,"Option Heures Creuses");
	}
	else if(strcmp(Compteur[no_tele].optarif,"EJP.") == 0)
	{
		strcat(out,"Option EJP");
	}			
	else if(memcmp(Compteur[no_tele].optarif,"BBR",3) == 0)
	{
		strcat(out,"Option Tempo (");
		strcat(out,Compteur[no_tele].optarif);
		strcat(out,")");
	}
	return(out);
}

//*******************************************************
//
//  PuissanceToStr
//
//*******************************************************
void PuissanceToStr(unsigned int p,unsigned char* out)
{
	static unsigned int 	int_trav;
	static unsigned char	i_out;
	static unsigned int		k;
	static unsigned int 	r;	
	static unsigned int 	flag;
	int_trav = p;
	i_out = 0;
	flag = 0;
	
	if (int_trav == 0) 
	{
        out[i_out++] = '0';
   	} 
   	else 
	{
		k = 100000;
        while (k > 0) 
	    {
        	r = int_trav / k;
			if (flag || r > 0) 
			{
				out[i_out++] = '0' + r;
				flag = 1;
			}
	        int_trav -= r * k;
	        k = k / 10;
	    }
	}    
	out[i_out] = 0x00;
	return;
}
	


//PuissanceToStr(index_ecart[port], Regul.Capteur[T_PUISS].Temperature_s);// valeur en string
//Regul.Capteur[T_PUISS].Temperature = index_ecart[port];	
//Regul.Capteur[T_PUISS].Etat = CAPTEUR_OK;
