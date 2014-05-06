/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 * Nom:			Log.c
 * Fonction :	Gestion des Log . On envoi les lignes a ajouter au log, et log.c se charge de la gestion
 *
 *  SARL ADTEK
 **********************************************************************************************************
 * Author | Jean Arhainx  |  Date  19/03/2014   |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or
 * send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *********************************************************************************************************/

#include <p32xxxx.h>               						
#include "0_SPARKBOX.h"
#include "log.h"
#include "rtc.h"

STRUCT_LOG 		Log[NB_LIGNES_LOG]; // environ 3,6Ko (80lignes))
unsigned char	Index_Log;
unsigned char 	Index_Read; // Recopie de Index_Log pour un accés en lecture depuis l'extérieur
unsigned char	Index_Nb_Lignes;
unsigned char	Date_Log[9];	// Date du fichier de log à récupérer
unsigned int	cpt1s_log = 0;	// cpt1s de la création de la date du log du fichier de log à récupérer
unsigned char 	NomFichierLog[20]; // Nom fichier de log
unsigned char	Fichier_Present = 0;
unsigned char   message_log[80] = " ";

void Nom_Log(INT32 utclog,unsigned char* out);

void Init_Log(void)
{
	unsigned char i;
	
	for (i=0; i < NB_LIGNES_LOG; i++)
	{
		Log[i].Date  	= 0;
		Log[i].Ligne[0] = 0x00;
	}
	Index_Log 		= 0;
	Index_Read 		= Index_Log;	
	Index_Nb_Lignes = 0;
	cpt1s_log = 0;
	Date_Log[0]=0x00;
}


void Ajout_Ligne_Log_Long(long valeur)
{
	unsigned char ligne_d[20];
	unsigned char ligne_l[20];
	
	ultoa(ligne_l,valeur,10);
	strcpy(ligne_d,"DEBUG: ");
	strcat(ligne_d,ligne_l);
		
	Ajout_Ligne_Log(ligne_d);
}	
	


void Ajout_Ligne_Log(unsigned char * Ligne_Log)
{
	// horodatage 
	if (utc.utc_fr > 0)
	{
		Log[Index_Log].Date = utc.utc_fr;	
	}
	else
	{
		Log[Index_Log].Date = 1;
	}
	// Ligne de Log
	if (strlen(Ligne_Log) <= TAILLE_LIGNE_LOG)
	{
		strcpy(Log[Index_Log].Ligne, Ligne_Log);
	}
	else // La chaine déborde. On ne garde que ce que l'on peut stocker!
	{
		strncpy(Log[Index_Log].Ligne, Ligne_Log,TAILLE_LIGNE_LOG);
		Log[Index_Log].Ligne[TAILLE_LIGNE_LOG] = 0x00;
	}	
	
	// Gestion du tableau avec une rotation cyclique
	Index_Log++;
	Index_Read = Index_Log;	
	if (Index_Log == NB_LIGNES_LOG)
	{
		Index_Log = 0; // Retour au début du tampon
	} 
	Index_Nb_Lignes++;
	if (Index_Nb_Lignes > NB_LIGNES_LOG)
	{
		Index_Nb_Lignes = NB_LIGNES_LOG;
	}
	
}

	


