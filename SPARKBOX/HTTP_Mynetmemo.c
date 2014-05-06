/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 * Nom:			HTTP_MYNETMEMO.C
 * Fonction :	Gestion de la page Mynetmemo
 *
 *  SARL ADTEK
 **********************************************************************************************************
 * Author | Jean Arhainx  |  Date  19/03/2014   |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or
 * send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *********************************************************************************************************/
#define __HTTP_MYNETMEMO_C

#include "TCPIPConfig.h"
#include "TCPIP Stack/TCPIP.h"
#include "0_SPARKBOX.h"
#include "mynetmemo.h"
#include "http.h"
#include "log.h"
#include "temperature.h"
#include "evse.h"


STRUCT_MYNETMEMO newMynetmemo;

HTTP_IO_RESULT HTTPPostMynetmemo(void)
{
	static unsigned char modif;
	static unsigned char monit;

    // Sauvegarde des données
	newMynetmemo 	= Mynetmemo;
	modif 			= FALSE;  
	monit 			= FALSE;	  
	
	if( curHTTP.byteCount > TCPIsGetReady(sktHTTP) + TCPGetRxFIFOFree(sktHTTP) )
	{
		goto ConfigFailure;
	}
		
	if( TCPIsGetReady(sktHTTP) < curHTTP.byteCount ) // Ensure that all data is waiting to be parsed.  If not, keep waiting for all of it to arrive.
	{
		return HTTP_IO_NEED_DATA;
	}
	
	// Lecture des données reçues par le POST
	while(curHTTP.byteCount)
	{
		// Read a form field name
		if( HTTPReadPostName(curHTTP.data, 6) != HTTP_READ_OK )
		{
			goto ConfigFailure;
		}	
		// Read a form field value
		if( HTTPReadPostValue(curHTTP.data + 6, sizeof(curHTTP.data)-6-2) != HTTP_READ_OK )
		{
			goto ConfigFailure;
		}
        
        if(!strncmp((char*)curHTTP.data, (ROM char*)"m_",2))
		{
			strcpy ( Temp_c, (char*) curHTTP.data + 2 ); // curHTTP.data contient la chaîne "m_xx" envoyée par la page capteurs.htm, on récupère directement le numéro après "c_"
	        num = (unsigned char) atoi( Temp_c );
			memset( Temp_c, 0x00, 3 );	
			memcpy( Temp_c, (char*)curHTTP.data+6, sizeof(curHTTP.data)-6);
			newMynetmemo.ID_Mynetmemo[num] = (unsigned short) atoi(Temp_c);	
			modif = TRUE;
		}
       	else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"log"))
		{
			memcpy( Temp_c, (char*)curHTTP.data+6, sizeof(curHTTP.data)-6);
			strncpy(newMynetmemo.Login, Temp_c,20);	
			newMynetmemo.Login[20] = 0x00;
			modif = TRUE;
		} 
        else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"pas"))
		{
			memcpy( Temp_c, (char*)curHTTP.data+6, sizeof(curHTTP.data)-6);
			strncpy(newMynetmemo.Password, Temp_c,20);
			newMynetmemo.Password[20] = 0x00;	
			modif = TRUE;
		} 
		else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"ser"))
		{
			memcpy( Temp_c, (char*)curHTTP.data+6, sizeof(curHTTP.data)-6);
			strncpy(newMynetmemo.ServerName, Temp_c,40);
			newMynetmemo.ServerName[40] = 0x00;
			modif = TRUE;
		} 
		else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"por"))
		{
			memcpy( Temp_c, (char*)curHTTP.data+6, sizeof(curHTTP.data)-6);
			newMynetmemo.ServerPort = (unsigned short) atoi(Temp_c);
			modif = TRUE;
		} 
		else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"e1"))
		{
			if((curHTTP.data[6] == 0x6F) &&(curHTTP.data[7] == 0x6E)) //on
			{
				monit = TRUE;
			}	
		}     
    }
       
    // Sauvegarde des parametres 
    if (modif == TRUE)
    {
	    // On ne sauvegarde pas en version de démonstration
	    if (FONCTION != FONCTION_DEMO)
	    {
			Mynetmemo	= newMynetmemo;
   			Eeprom_Ecriture_Mynetmemo(Mynetmemo);
   		}	
   		Ajout_Ligne_Log("HTTP: Mise à jour Mynetmemo");
   	}	
   	if (monit != (Sparkbox.Type_Monitoring & MONITORING_MYNETMEMO))
   	{
	   	if (monit == TRUE)
	   	{
   			Sparkbox.Type_Monitoring = Sparkbox.Type_Monitoring | MONITORING_MYNETMEMO;
   		}
   		else
   		{
   			Sparkbox.Type_Monitoring = Sparkbox.Type_Monitoring & ~MONITORING_MYNETMEMO;
   		}
   		Eeprom_Ecriture_Regul(Sparkbox);
   	}
  	  	
    return HTTP_IO_DONE;
	
	// CONFIG FAILURE
    ConfigFailure:
	lastFailure = TRUE;
	strcpypgm2ram((char*)curHTTP.data, (ROM char*)"mynetmemo.htm");
	curHTTP.httpStatus = HTTP_REDIRECT;		
	return HTTP_IO_DONE;

}

//--------------------------------------------------------------------------------------------

void HTTPPrint_mynet_envoi(void)
{
    if (Sparkbox.Type_Monitoring & MONITORING_MYNETMEMO)
	{
		TCPPutROMString(sktHTTP, (ROM BYTE*) " checked=\"checked\"");
	}
}

void HTTPPrint_mynet_log(void)
{
	TCPPutString( sktHTTP, Mynetmemo.Login);
}

void HTTPPrint_mynet_pwd(void)
{
	TCPPutString( sktHTTP, Mynetmemo.Password);
}

void HTTPPrint_monit_fct(unsigned char num)
{
	TCPPutString( sktHTTP, Sparkbox.Capteur[num].Nom);
}


void HTTPPrint_monit_val(unsigned char num)
{
	 switch ( num )
     {
		case 0 :
			// TELE1: IINST
			TCPPutString( sktHTTP,Compteur[0].iinst1);
        break;

		case 1 :
			// Température
			ultoa(Http_byte,Evse.Temp,10);
			TCPPutString( sktHTTP,Http_byte);
        break;

        case 2 :
			// Pilot (State)
			Http_byte[0] = 0x30 + Evse.state;
			Http_byte[1] = 0x00;
			TCPPutString( sktHTTP,Http_byte);
        break;

		case 3 :
			// Courant 1
			ultoa(Http_byte,(unsigned long)Evse.Courant,10);
			TCPPutString( sktHTTP,Http_byte);
        break;

		case 4 :
			// Courant 2
			ultoa(Http_byte,(unsigned long)Evse.Courant_Diff,10);
			TCPPutString( sktHTTP,Http_byte);
        break;

		case 5 :
			// TELE1 Puissance calculée
			TCPPutString( sktHTTP,Compteur[0].calc_puis_s);
        break;

		case 6 :
			// TELE1 INDEX
			TCPPutString( sktHTTP,Compteur[0].calc_index_char);
        break;

		case 7 :
			// TELE2: IINST
			TCPPutString( sktHTTP,Compteur[1].iinst1);
        break;

		case 8 :
			// TELE2 Puissance calculée
			TCPPutString( sktHTTP,Compteur[1].calc_puis_s);
        break;

		case 9 :
			// TELE2 INDEX
			TCPPutString( sktHTTP,Compteur[1].calc_index_char);
        break;
	 }	
}

void HTTPPrint_mynet_ser(void)
{
	TCPPutString( sktHTTP, Mynetmemo.ServerName);
}

void HTTPPrint_mynet_por(void)
{
	BYTE digits[6];
	uitoa( Mynetmemo.ServerPort, digits);
	TCPPutString(sktHTTP, digits);
}


void HTTPPrint_id_monitor(unsigned char num)
{
	BYTE digits[6];
	uitoa( Mynetmemo.ID_Mynetmemo[num], digits);
	TCPPutString(sktHTTP, digits);
}




