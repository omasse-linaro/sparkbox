/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 * Nom:			HTTP_DONNEES.C
 * Fonction :	Gestion de la page Donnees
 *
 *  SARL ADTEK
 **********************************************************************************************************
 * Author | Jean Arhainx  |  Date  19/03/2014   |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or
 * send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *********************************************************************************************************/
#define __HTTP_CAPTEURS_C

#include "TCPIPConfig.h"
#include "TCPIP Stack/TCPIP.h"
#include "0_SPARKBOX.h"
#include "teleinfo.h"
#include "http.h"
#include "log.h"
#include "divers.h"
#include "temperature.h"


unsigned char 	donnees_mois 	= 1;
unsigned short 	donnees_an 		= 0;

struct tm 		tm_donnees;
time_t			tdonnees_soir;
time_t			tdonnees_matin;
unsigned int	tindex_soir;
unsigned int	tindex_matin;
unsigned int    tindex_calc; 

//************************************************************************************************************************************************
// CAPTEURS
//************************************************************************************************************************************************
HTTP_IO_RESULT HTTPPostDonnees(void)
{
		 

	if( curHTTP.byteCount > TCPIsGetReady(sktHTTP) + TCPGetRxFIFOFree(sktHTTP) )
	{
		lastFailure = TRUE;
		goto ConfigFailure;
	}
		
	if( TCPIsGetReady(sktHTTP) < curHTTP.byteCount ) // Ensure that all data is waiting to be parsed.  If not, keep waiting for all of it to arrive.
	{
		lastFailure = TRUE;
		return HTTP_IO_NEED_DATA;
	}
	
	// Lecture des données reçues par le POST
	while(curHTTP.byteCount)
	{
		// Read a form field name
		if( HTTPReadPostName(curHTTP.data, 6) != HTTP_READ_OK )
		{
			lastFailure = TRUE;
			goto ConfigFailure;
		}	
		// Read a form field value
		if( HTTPReadPostValue(curHTTP.data + 6, sizeof(curHTTP.data)-6-2) != HTTP_READ_OK )
		{
			lastFailure = TRUE;
			goto ConfigFailure;
		}
        // On veux lire le mois et l'année désirée
        if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"mois"))
		{
        	memset( Temp_c, 0x00, 3 );	
			memcpy( Temp_c, (char*)curHTTP.data+6, sizeof(curHTTP.data)-6);
			Temp_i = atoi( Temp_c );
			if ( Temp_i >= 0 && Temp_i <= 12 )
			{
                donnees_mois = (unsigned char) Temp_i;
			}
			else
			{
				goto ConfigFailure;
			}	
		}
		if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"an"))
		{
        	memset( Temp_c, 0x00, 3 );	
			memcpy( Temp_c, (char*)curHTTP.data+6, sizeof(curHTTP.data)-6);
			Temp_i = atoi( Temp_c );
			if ( Temp_i >= 2011 && Temp_i <= 2041 )
			{
                donnees_an = Temp_i;
			}
			else
			{
				goto ConfigFailure;
			}	
		}
			
 	}   
 
    ConfigFailure:

	strcpypgm2ram((char*)curHTTP.data, (ROM char*)"donnees.htm");
	curHTTP.httpStatus = HTTP_REDIRECT;		
	return HTTP_IO_DONE;
}


void HTTPPrint_bdtitre(void)
{
	strcpy(Http_byte,"PRODUCTION ");
	
	if (donnees_mois == 1) 		 strcat(Http_byte,"JANVIER");
	else if (donnees_mois == 2)  strcat(Http_byte,"FEVRIER");
	else if (donnees_mois == 3)  strcat(Http_byte,"MARS");
	else if (donnees_mois == 4)  strcat(Http_byte,"AVRIL");
	else if (donnees_mois == 5)  strcat(Http_byte,"MAI");
	else if (donnees_mois == 6)  strcat(Http_byte,"JUIN");
	else if (donnees_mois == 7)  strcat(Http_byte,"JUILLET");
	else if (donnees_mois == 8)  strcat(Http_byte,"AOUT");
	else if (donnees_mois == 9)  strcat(Http_byte,"SEPTEMBRE");
	else if (donnees_mois == 10) strcat(Http_byte,"OCTOBRE");
	else if (donnees_mois == 11) strcat(Http_byte,"NOVEMBRE");
	else if (donnees_mois == 12) strcat(Http_byte,"DECEMBRE");
		
	TCPPutString(sktHTTP, Http_byte);
}

// Donnée affichée de la BD pour le jour (num)

 void HTTPPrint_bd(WORD num)
{

}

void HTTPPrint_mois(unsigned char num)
{
	if ((donnees_an == 0) || (utc.annee == 0))
	{
		donnees_mois = utc.mois;
 		donnees_an = utc.annee;
	}
	if ( num == donnees_mois )
	{
		TCPPutString(sktHTTP, "selected");
	}
}

void HTTPPrint_donnees_an(void)
{
	uitoa(donnees_an, Http_byte);
	TCPPutString(sktHTTP, Http_byte);
}





