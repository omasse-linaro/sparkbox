/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 * Nom:			HTTP_INDEXS.C
 * Fonction :	Gestion de la page Index
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
#include "teleinfo.h"
#include "0_SPARKBOX.h"
#include "temperature.h"
#include "divers.h"
#include "http.h"
#include "evse.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>



void HTTPPrint_index_message1(void)
{
	TCPPutString( sktHTTP, "");
}


void HTTPPrint_index_erreur1(void)
{
	TCPPutString( sktHTTP, "");
}



void HTTPPrint_prod_mois(void)
{
	
}


void HTTPPrint_prod_jour(void)
{
	
}


void HTTPPrint_prod_heure(void)
{
	
}

void HTTPPrint_ls(void)
{
	ultoa(Http_byte,(unsigned int)loop_count_mem,10);
	strcat(Http_byte,"/s");
	TCPPutString( sktHTTP, Http_byte);
}



void HTTPPrint_capteur_temp(unsigned char num)
{	
	if (Sparkbox.Capteur[num].Etat == CAPTEUR_OK)
	{
		strcpy(Http_byte,(unsigned char *) Temptostr(num));
		strcat(Http_byte, "�");
	}
	else if (Sparkbox.Capteur[num].Etat == CAPTEUR_ERREUR)
	{
		strcpy(Http_byte, "Erreur Capteur");
	}
	else if (Sparkbox.Capteur[num].Etat == CAPTEUR_DEMARRAGE)
	{
		strcpy(Http_byte, "D�marrage");
	}
	else if (Sparkbox.Capteur[num].Etat == CAPTEUR_ABSENT)
	{
		strcpy(Http_byte, "Capteur Absent");
	}
	else if (Sparkbox.Capteur[num].Etat == CAPTEUR_AUCUN)
	{
		strcpy(Http_byte, "--");
	}
	else
	{
		strcpy(Http_byte,"Erreur");
	}
	
	TCPPutString( sktHTTP, Http_byte);
}




void HTTPPrint_affiche_teleinfo(void)
{
	unsigned char httpi;
	unsigned char existe = 0;
	
	if (ADTEK_HTTP_Return(100))return;
	
	for (httpi = 0;httpi < NB_TELEINFO ; httpi++)
	{
		if (strcmp(Compteur[httpi].adco,"") != 0) existe++;
	}
	if (existe)
	{
		TCPPutString( sktHTTP, "T�l�info");
		for (httpi = 0;httpi < NB_TELEINFO ; httpi++)
		{		
			if (strcmp(Compteur[httpi].adco,"") != 0)
			{
				TCPPutString(sktHTTP,"   Compteur TELE");
				Http_byte[0] =  httpi+0x31;
				Http_byte[1] =  0x00;
				TCPPutString( sktHTTP, Http_byte);
				TCPPutString(sktHTTP,"= ");
				TCPPutString(sktHTTP,Compteur[httpi].adco);
			}
		}
	}
	else
	{
		TCPPutString( sktHTTP, " ");
	}
}

void HTTPPrint_debug1(void)
{	
	TCPPutString( sktHTTP, " ");
}

void HTTPPrint_Amp_Programmes(unsigned char num)
{
	if (ADTEK_HTTP_Return(10))return;

	ultoa(Http_byte,Sparkbox.Amp,10);
	if (num == 1) strcat(Http_byte," A");
	TCPPutString( sktHTTP, Http_byte);
}

void HTTPPrint_Courant_Fuite(unsigned char num)
{
	if (ADTEK_HTTP_Return(10))return;

	if (Sparkbox.Gfci != 0)
	{
		ultoa(Http_byte,Sparkbox.Gfci,10);
		if (num == 1) strcat(Http_byte," mA");
	}
	else
	{
		if (num == 1) strcpy(Http_byte,"D�sactiv�");
		else		strcpy(Http_byte,"0");
	}
		TCPPutString( sktHTTP, Http_byte);
}

void HTTPPrint_Test_Relais(void)
{
	if (ADTEK_HTTP_Return(10))return;

	if (Sparkbox.Collage_Relais == 1)
	{
		if ((Evse.Default & DEFAUT_RELAIS) == DEFAUT_RELAIS)
		{
			TCPPutString( sktHTTP, "DEFAUT!");
		}
		else
		{
			TCPPutString( sktHTTP, "Activ�");
		}
	}
	else
	{
		TCPPutString( sktHTTP, "D�sactiv�");
	}
}

void HTTPPrint_Test_Diode(void)
{
	if (ADTEK_HTTP_Return(10))return;

	if (Sparkbox.Diode == 1)
	{
		if ((Evse.Default & DEFAUT_DIODE) == DEFAUT_DIODE)
		{
			TCPPutString( sktHTTP, "DEFAUT!");
		}
		else
		{
			TCPPutString( sktHTTP, "Activ�");
		}
	}
	else
	{
		TCPPutString( sktHTTP, "D�sactiv�");
	}
}

void HTTPPrint_erreur_xml(void)
{
	unsigned char restart;

	if (Evse.Default != NONE)
	{
		strcpy(Http_byte,"ALERTE: ");
		restart = 0;

		if ((Evse.Default & DEFAUT_DIODE) == DEFAUT_DIODE)
		{
			strcat(Http_byte,"Defaut Diode , ");
		}
		if ((Evse.Default & DEFAUT_GROUND) == DEFAUT_GROUND)
		{
			strcat(Http_byte,"Defaut Terre , ");
			restart = 1;
		}
		if ((Evse.Default & DEFAUT_GFCI) == DEFAUT_GFCI)
		{
			strcat(Http_byte,"Defaut fuite courant (GFCI), ");
			restart = 1;
		}
		if ((Evse.Default & DEFAUT_RELAIS) == DEFAUT_RELAIS)
		{
			strcat(Http_byte,"Defaut Relais, ");
			restart = 1;
		}
		if (restart == 1)
		{
			strcat(Http_byte,"Red�marrage Sparkbox imp�ratif!");

		}
		TCPPutString( sktHTTP, Http_byte);
	}
	else
	{
		TCPPutString( sktHTTP, " ");
	}
	
}


void HTTPPrint_temps_charge(void)
{
	unsigned int tps;
	unsigned int h;
	unsigned int m;
	if (Evse.Heure_Debut != 0)
	{
		tps = (cpt1ms - Evse.Heure_Debut) / 60000; // ms -> minutes
		h = tps /60;
		m = tps - (h * 60);
		if (h != 0)
		{
			ultoa(Http_byte,h,10);
			strcat(Http_byte," h ");
		}
		else
		{
			strcpy(Http_byte," ");
		}
		ultoa(Http_byte2,m,10);
		strcat(Http_byte,Http_byte2);
		strcat(Http_byte," m");
		TCPPutString( sktHTTP, Http_byte);
	}
	else
	{		
		TCPPutString( sktHTTP, "0");
	}	
}

void HTTPPrint_amp(void)
{
	TCPPutString( sktHTTP, " ");
}

void HTTPPrint_state(void)
{
	if (Evse.state == STATE_A)
	{
		strcpy(Http_byte, "Non connect�");
	}
	else if (Evse.state == STATE_B)
	{
		strcpy(Http_byte, "Connect�");
	}
	else if (Evse.state == STATE_C)
	{
		strcpy(Http_byte, "En charge");
	}
	else if (Evse.state == STATE_D)
	{
		strcpy(Http_byte, "Ventilation requise");
	}
	else if (Evse.state == STATE_E)
	{
		strcpy(Http_byte, "STATE E");
	}
	else if (Evse.state == STATE_F)
	{
		strcpy(Http_byte, "STATE F");
	}
	else
	{
		strcpy(Http_byte,"Erreur");
	}

	TCPPutString( sktHTTP, Http_byte);
}




void HTTPPrint_Pilot_Value(void)
{
	ultoa(Http_byte2,Evse.Max,10);
	TCPPutString( sktHTTP, Http_byte2);
}

void HTTPPrint_Ac1(void)
{
	if (AC1) TCPPutString( sktHTTP, "?");
	else TCPPutString( sktHTTP, "220v");
}

void HTTPPrint_Ac2(void)
{
	if (AC2) TCPPutString( sktHTTP, "?");
	else TCPPutString( sktHTTP, "220v");
}

void HTTPPrint_Temp(void)
{
	ultoa(Http_byte2,Evse.Temp,10);
	TCPPutString( sktHTTP, Http_byte2);
}

//  Courant mesur� (A * 100)
void HTTPPrint_Cour1(unsigned char num)
{
	HectoTempToStr((short)Evse.Courant ,Http_byte2);
    //ultoa(Http_byte2,(unsigned long)Evse.Courant,10);
	if (num == 1) strcat (Http_byte2," A");
    TCPPutString( sktHTTP, Http_byte2);
}
void HTTPPrint_Cour2(unsigned char num)
{
	ultoa(Http_byte2,(unsigned long)Evse.Courant_Diff,10);
    if (num == 1) strcat (Http_byte2," mA");
	TCPPutString( sktHTTP, Http_byte2);
}
void HTTPPrint_Vref2(void)
{
	ultoa(Http_byte2,Evse.Vref2,10);
	TCPPutString( sktHTTP, Http_byte2);
}