/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 * Nom:			HTTP_LOG.C
 * Fonction :	Gestion de la page Log
 *
 *  SARL ADTEK
 **********************************************************************************************************
 * Author | Jean Arhainx  |  Date  19/03/2014   |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or
 * send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *********************************************************************************************************/
#define __HTTP_LOG_C

#include "TCPIPConfig.h"
#include "TCPIP Stack/TCPIP.h"
#include "0_SPARKBOX.h"
#include "log.h"
#include "http.h"
#include "rtc.h"

unsigned char	val = 0;
unsigned char	val1 = 0;
unsigned char	val2 = 0;
unsigned char	val3 = 0;
struct tm		tm_data;

void HTTPPrint_log(unsigned char num) 
{
	if (ADTEK_HTTP_Return(100))return;
	
	Http_byte[0] = 0x00;
	if (num <= NB_LIGNES_LOG)
	{
		if (Index_Nb_Lignes == NB_LIGNES_LOG)
		{
			val = (NB_LIGNES_LOG - Index_Read);
			if (num  <= val)
			{
				val = (num - 1) + Index_Read;
			}
			else
			{
				val = num - (val +1);
			}
		}
		else
		{
			val = num - 1;
		}
		if (val < NB_LIGNES_LOG)
		{ 
			if (Log[val].Date != 0)
			{
				ConvertUtcSecToString(Log[val].Date,Http_byte);
				strcat(Http_byte," ");
				strcat(Http_byte,Log[val].Ligne);
			}	
		}
		else
		{
			strcpy(Http_byte,"Erreur HTTP_log.c");
		}	
		TCPPutString(sktHTTP, Http_byte);
	}
	else
	{
		TCPPutString(sktHTTP,"Log terminé");
	}		
}

/*void HTTPPrint_date_log(void)
{
	Fichier_Present = 0;
	if (ADTEK_HTTP_Return(10))return;
	// On calcule la date du log (date du jour))
	if (cpt1s_log < cpt1s)
	{
		if ((NomFichierLog[0] == 0x70) && (NomFichierLog[1] == 0x76) && (NomFichierLog[2] == 0x74) && (NomFichierLog[3] == 0x62) && (NomFichierLog[2] == 0x6F) && (NomFichierLog[3] == 0x78)) // "pvtbox"
		{
			strcpy(Date_Log,"pvtbox");
		}
		else
		{
			memcpy(&Date_Log[0],&NomFichierLog[0],6);
			Date_Log[6] = 0x00;
		}
	}
	TCPPutString(sktHTTP,Date_Log);
}*/

void HTTPPrint_date_ind(void)
{
	WORD t;

	if (ADTEK_HTTP_Return(10))return;
	if (cpt1s_Ind < cpt1s)
	{
		if (utc.annee >= 2013)
		{
			t = utc.annee;
			uitoa(t,Date_Ind);
		}
	}
	TCPPutString(sktHTTP,Date_Ind);
}

void HTTPPrint_mess_log(void)
{
	if (ADTEK_HTTP_Return(50))return;
	TCPPutString(sktHTTP,message_log);
}

/* HTTPPrint_fichier_csv(void)
 * Génération d'un fichier csv avec les valeurs de la Flash EEPROM
 *
 */
void HTTPPrint_fichier_csv(void)
{
	 unsigned int			tindex;
	 STRUCT_DATE_ADTEK		affiche_jour;

	 static unsigned short	daypos;
	 static time_t			tdonnees;

	// Première ligne. On calcule l'index au 1er janvier et on affiche ue légende!
	if(curHTTP.callbackPos == 0)
	{     // First time for this callback
		curHTTP.callbackPos = 1;
	 	daypos=0;
		tm_data.tm_sec 	= 0;
		tm_data.tm_min	= 0;
		tm_data.tm_hour = 23;  // 23 heures
		tm_data.tm_mday	= 1;
		tm_data.tm_mon  = 0; // JANVIER = 0
		tm_data.tm_year = atoi(Date_Ind) - 1900;
		tm_data.tm_wday = 0;
		tm_data.tm_yday = 0;
		tdonnees = mktime(&tm_data);
		strcpy(Http_byte,"SPARKBOX-ADTEK: Fichier des index\r\n");
		TCPPutString(sktHTTP, Http_byte);
		strcpy(Http_byte,"DATE;TELE1;TELE2\r\n\r\n");
		TCPPutString(sktHTTP, Http_byte);
	}

	// Lignes suivantes, on affiche les index
	if(TCPIsPutReady(sktHTTP) > 250)
	{
		if (daypos <= 365)
		{
			// Affichage de la date

			ExtractUTC_Temps((INT32)tdonnees,&affiche_jour,0);
			uitoa(affiche_jour.jour,Http_byte);
			strcat(Http_byte,"/");
			uitoa(affiche_jour.mois,Http_byte2);
			strcat(Http_byte,Http_byte2);
			strcat(Http_byte,"/");
			uitoa(affiche_jour.annee,Http_byte2);
			strcat(Http_byte,Http_byte2);
			strcat(Http_byte,";");

			// Lecture de l'index TELE1
			tindex =BD_Lecture_Jour_Teleinfo(0,tdonnees);
			if (tindex < 0xFFFFFFFF)
			{
				ultoa(Http_byte2,tindex,10);
				PadLeftZero(Http_byte2,9);
				strcat(Http_byte,Http_byte2);
			}
			else strcat(Http_byte,"---------");
			strcat(Http_byte,";");
			// Lecture de l'index TELE2
			tindex =BD_Lecture_Jour_Teleinfo(1,tdonnees);
			if (tindex < 0xFFFFFFFF)
			{
				ultoa(Http_byte2,tindex,10);
				PadLeftZero(Http_byte2,9);
				strcat(Http_byte,Http_byte2);
			}
			else strcat(Http_byte,"---------");
			strcat(Http_byte,";");

			strcat(Http_byte,"\n");
			TCPPutString(sktHTTP, Http_byte);

			daypos++;
			tdonnees = tdonnees + 86400;
		}
		else
		{       // No more
			curHTTP.callbackPos = 0;
		}
	}
}