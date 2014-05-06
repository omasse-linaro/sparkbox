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
#ifndef _LOG_H
	#define _LOG_H          
    #include "0_SPARKBOX.h"
   
   	#define TAILLE_LIGNE_LOG 	60	// Commentaire Log 
   	#define NB_LIGNES_LOG		80	// Nombres de lignes sauvegardées par rotation cyclique (doit rentrer dans un char)
   
   	// Gestion des statistiques de fonctionnement.
   	typedef struct
   	{
		unsigned int  Date; // Contient cpt1s ou la date et heure en Timestamp
		unsigned char Ligne[TAILLE_LIGNE_LOG+1];
	} STRUCT_LOG; 
   
   	extern STRUCT_LOG 		Log[];
   	extern unsigned char 	Index_Read;
   	extern unsigned char	Index_Nb_Lignes;
   	
	extern unsigned char	Date_Log[9];
	extern unsigned int		cpt1s_log;
	extern unsigned char 	NomFichierLog[20];
	extern unsigned char	Fichier_Present;
	extern unsigned char   	message_log[80];

	// Prototypes fonctions
	void 			Init_Log(void);
	void 			Ajout_Ligne_Log(unsigned char * Ligne_Log);	
	unsigned char  	Log_Acccess_Fichier(void);
	void 			Ajout_Ligne_Log_Long(long valeur);
	
#endif