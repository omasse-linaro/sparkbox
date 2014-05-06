/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 * Nom:			HTTP_CMD.C
 * Fonction :	Gestion des commandes directes http
 *
 *  SARL ADTEK
 **********************************************************************************************************
 * Author | Jean Arhainx  |  Date  19/03/2014   |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or
 * send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *********************************************************************************************************/
#define __HTTP_CMD_C

#include "TCPIPConfig.h"
#include "TCPIP Stack/TCPIP.h"
#include "0_SPARKBOX.h"
#include "temperature.h"
#include "http.h"

void HTTPPrint_cmd(void)
{
	//if (Http_byte[0]!= 0x4F) // 'O' le O de Ok
	if (Http_byte[0]== 0x00) // 'O' le O de Ok
	{
		strcpy(Http_byte,"ERREUR. Aucune commande n'est reconnue !<br /><br />");
		strcat(Http_byte,"Usage: http://adresse_ip/cmd.htm?commandes<br /><br />");
		strcat(Http_byte,"Comandes usuelles:<br />");
		strcat(Http_byte,"cmd.htm?relaisx=on(ou off)&time=nb_secondes<br />");
		strcat(Http_byte,"cmd.htm?relaisx=on(ou off)<br />");
		strcat(Http_byte,"cmd.htm?relais   pour lire l'état des relais<br />");
		strcat(Http_byte,"cmd.htm?temp=yy (yy = numéro de capteur, ou all pour tous)<br />");		
	}	
	TCPPutString( sktHTTP, Http_byte );
	Http_byte[0] = 0x00;
}

void Affiche_Etat_Relais(void)
{
	unsigned char cpt;
	
	strcpy(Http_byte,"OK<br />Etat RELAIS: ");
	for (cpt = 0 ; cpt < NB_RELAIS; cpt++)
	{
		strcat(Http_byte,"R");
		uitoa((cpt+1),Http_byte2);
		strcat(Http_byte,Http_byte2);
		strcat(Http_byte,"=");
		if (Etat_Relais(cpt+1) == RELAIS_ON)
		{
			strcat(Http_byte,"on");
		}
		else
		{
			strcat(Http_byte,"off");
		}
		if ((Relais_Man[cpt].Pilotable == OUI) && (Relais_Man[cpt].Time != 0))
		{
			strcat(Http_byte,"(");
			uitoa((Relais_Man[cpt].Time - utc.utc_fr),Http_byte2);
			strcat(Http_byte,Http_byte2);
			strcat(Http_byte,"s)");
		}
		strcat(Http_byte,", ");
	}
}

void Affiche_Temp(unsigned char num)
{
	unsigned char cpt;
	if (num < NB_MAX_CAPTEURS)
	{
		strcpy(Http_byte,"OK<br /> Temperature: ");
		strcat(Http_byte,(unsigned char *) Temptostr(num));
	}
	else
	{
		strcpy(Http_byte,"OK. Erreur: Numéro de capteur inconnu.");
	}	
}

void Affiche_Temp_All(void)
{
	unsigned char cpt;
	
	strcpy(Http_byte,"OK<br /> Températures: ");
	for (cpt = 0 ; cpt < NB_MAX_CAPTEURS; cpt++)
	{
		strcat(Http_byte,"T");
		uitoa((cpt+1),Http_byte2);
		strcat(Http_byte,Http_byte2);
		strcat(Http_byte,"=");
		if ((Sparkbox.Capteur[cpt].Type == DS1820) || (Sparkbox.Capteur[cpt].Type == ANALOGIQUE))
		{
			strcat(Http_byte,(unsigned char *) Temptostr(cpt));
		}
		else
		{
			strcat(Http_byte,"--");
		}	
		strcat(Http_byte,"; ");

	}
}
