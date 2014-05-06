/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 * Nom:			HTTP_PASSWORD.C
 * Fonction :	Gestion de la page Password
 *
 *  SARL ADTEK
 **********************************************************************************************************
 * Author | Jean Arhainx  |  Date  19/03/2014   |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or
 * send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *********************************************************************************************************/
#define __HTTP_STATUS_C

#include "TCPIPConfig.h"
#include "TCPIP Stack/TCPIP.h"
#include "0_SPARKBOX.h"
#include "http.h"
#include "log.h"
#include <stdio.h>

/*****************************************************************************
 					-- CONFIGURATION --					
  ***************************************************************************/
HTTP_IO_RESULT HTTPPostPassword(void)
{
	BYTE 			*ptr;
	BYTE 			i;
	int 			val;
	unsigned char	modif;	
	
	if(curHTTP.byteCount > TCPIsGetReady(sktHTTP) + TCPGetRxFIFOFree(sktHTTP))
	{
		goto ConfigFailure;
	}
	if(TCPIsGetReady(sktHTTP) < curHTTP.byteCount) 
	{
		return HTTP_IO_NEED_DATA;
	}

	modif = 0;
	// Lecture des données reçues par le POST
	while(curHTTP.byteCount)
	{
		// Read a form field name
		if(HTTPReadPostName(curHTTP.data, 6) != HTTP_READ_OK)
		{
			goto ConfigFailure;
		}	
		// Read a form field value
		if(HTTPReadPostValue(curHTTP.data + 6, sizeof(curHTTP.data)-6-2) != HTTP_READ_OK)
		{
			goto ConfigFailure;
		}				

		// Mot de passe
		if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"pwd")) 
		{
			memset(Http_byte,0x00,21);	
			memcpy(Http_byte,(char*)curHTTP.data+6,sizeof(curHTTP.data)-6);
			// Si on a une chaine vide on remet le pws par défaut
			if (Http_byte[0] != 0x00)
			{
				strcpy(&User.Login[0],"admin");
				strcpy(&User.Password[0],Http_byte);
			}
			else
			{
				strcpy(&User.Login[0],"admin");
				strcpy(&User.Password[0],"admin");
			}	
			modif = 1;
		}			
	}
	// On ne sauvegarde pas en version de démonstration
	if ((FONCTION != FONCTION_DEMO) && (modif == 1))
	{
		Eeprom_Ecriture_User(User);
	}	
	Ajout_Ligne_Log("HTTP: Changement password");	

	strcpypgm2ram((char*)curHTTP.data, (ROM char*)"password.htm");
	curHTTP.httpStatus = HTTP_REDIRECT;	
	return HTTP_IO_DONE;

ConfigFailure:
	lastFailure = TRUE;
	strcpypgm2ram((char*)curHTTP.data, (ROM char*)"password.htm");
	curHTTP.httpStatus = HTTP_REDIRECT;		
	return HTTP_IO_DONE;
}


void HTTPPrint_pwd(void)
{
	TCPPutString(sktHTTP, User.Password);
}
