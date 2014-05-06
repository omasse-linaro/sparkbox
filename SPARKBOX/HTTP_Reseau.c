/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 * Nom:			HTTP_RESEAU.C
 * Fonction :	Gestion de la page Reseau
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
#include <stdio.h>

//************************************************************************************************************************************************
// RESEAU
//************************************************************************************************************************************************
HTTP_IO_RESULT HTTPPostReseau(void)
{
	BYTE 		i;
	BOOL 		modif;
	APP_CONFIG  newAppConfig;	


	if(curHTTP.byteCount > TCPIsGetReady(sktHTTP) + TCPGetRxFIFOFree(sktHTTP))
	{
		goto ConfigFailure;
	}
	
	if(TCPIsGetReady(sktHTTP) < curHTTP.byteCount) // Ensure that all data is waiting to be parsed.  If not, keep waiting for all of it to arrive.
	{
		return HTTP_IO_NEED_DATA;
	}
	
	newAppConfig = AppConfig;
	newAppConfig.Flags.bIsDHCPEnabled = 0; // Sinon on ne pourra plus quitter le DHCP
	
	modif = FALSE;
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
			
		// Parse the value that was read
		if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"ip"))
		{// Read new static IP Address
			if(!StringToIPAddress(curHTTP.data+6, &newAppConfig.MyIPAddr))
			{
				goto ConfigFailure;
			}	
			newAppConfig.DefaultIPAddr.Val = newAppConfig.MyIPAddr.Val;
			modif = TRUE;
		}
		else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"gw"))
		{// Read new gateway address
		  	if(!StringToIPAddress(curHTTP.data+6, &newAppConfig.MyGateway))
		  	{
				goto ConfigFailure;
			}		
			modif = TRUE;
		}
		else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"sub"))
		{// Read new static subnet
			if(!StringToIPAddress(curHTTP.data+6, &newAppConfig.MyMask))
			{
				goto ConfigFailure;
			}	
            modif = TRUE;
	    }
	    else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"dns1"))
		{// Read new primary DNS server
			if(!StringToIPAddress(curHTTP.data+6, &newAppConfig.PrimaryDNSServer))
			{
				goto ConfigFailure;
			}	
		}
		else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"dns2"))
		{// Read new secondary DNS server
			if(!StringToIPAddress(curHTTP.data+6, &newAppConfig.SecondaryDNSServer))
			{
				goto ConfigFailure;
			}	
		}
		else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"dhcp"))
		{// Read new DHCP Enabled flag
			if(curHTTP.data[6] == '1')
			{
				newAppConfig.Flags.bIsDHCPEnabled = 1;
			}	
		}
	}
	
	// Sauvegarde des parametres réseau.
	// On ne sauvegarde pas en version de démonstration
	if (FONCTION != FONCTION_DEMO)
	{
		Eeprom_Ecriture_IP(newAppConfig);

		// Set the board to reboot and display reconnecting information
		strcpypgm2ram((char*)curHTTP.data, (ROM char*)"/reboot.htm?");
		memcpy((void*)(curHTTP.data+20), (void*)newAppConfig.NetBIOSName, 16);
		curHTTP.data[20+16] = 0x00;	// Force null termination
		for(i = 20; i < 20u+16u; i++)
		{
			if(curHTTP.data[i] == ' ')
				curHTTP.data[i] = 0x00;
		}		
		curHTTP.httpStatus = HTTP_REDIRECT;
		// AppConfig = newAppConfig; On ne change pas encore d'adresse IP dynamiquement tant qu'on ne sait pas le gérer coté navigateur
	}	
	else // DEMONSTRATION
	{
		strcpypgm2ram((char*)curHTTP.data, (ROM char*)"index.htm");
		curHTTP.httpStatus = HTTP_REDIRECT;		
	}
//	curHTTP.httpStatus = HTTP_REDIRECT;	
//	strcpypgm2ram((char*)curHTTP.data, (ROM char*)"/index.htm");
	return HTTP_IO_DONE;


ConfigFailure:
	lastFailure = TRUE;
	strcpypgm2ram((char*)curHTTP.data, (ROM char*)"/reseau.htm");
	curHTTP.httpStatus = HTTP_REDIRECT;		

	return HTTP_IO_DONE;
}




void HTTPPrint_config_ip(void)
{
	HTTPPrintIP(AppConfig.MyIPAddr);
	return;
}

void HTTPPrint_config_gw(void)
{
	HTTPPrintIP(AppConfig.MyGateway);
	return;
}

void HTTPPrint_config_subnet(void)
{
	HTTPPrintIP(AppConfig.MyMask);
	return;
}

void HTTPPrint_config_dhcpchecked(void)
{
	if(AppConfig.Flags.bIsDHCPEnabled)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"checked");
	return;
}

void HTTPPrint_config_dns1(void)
{
	HTTPPrintIP(AppConfig.PrimaryDNSServer);
	return;
}

void HTTPPrint_config_dns2(void)
{
	HTTPPrintIP(AppConfig.SecondaryDNSServer);
	return;
}







