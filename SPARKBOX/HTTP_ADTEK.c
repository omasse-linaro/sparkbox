/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 * Nom:			HTTP_ADTEK.C
 * Fonction :	
 *
 *  SARL ADTEK
 **********************************************************************************************************
 * Author | Jean Arhainx  |  Date  19/03/2014   |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or
 * send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *********************************************************************************************************/

/*********************************************************************
 * 
 * Author               Date    	Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Hervé DELAY     	    02/10/10	Premier tests
 ********************************************************************/
#define __HTTP_ADTEK_C

#include "TCPIPConfig.h"
#include "TCPIP Stack/TCPIP.h"
#include "0_SparkBox_Version.h"
#include "http.h"
#include "Eeprom_i2c.h"
#include "teleinfo.h"
#include "rtc.h"
#include "0_SPARKBOX.h"
#include "log.h"
#include "divers.h"
#include "Evse.h"
#include <time.h>
#include <string.h>

// todo : voir si encore des fonctions de l'adt01 à virer...

/****************************************************************************
  Section:
	Function Prototypes and Memory Globalizers
  ***************************************************************************/

BOOL lastSuccess = FALSE;
BOOL lastFailure = FALSE;

char 			Temp_c[250]; // Pour être sûr d'accepter le buffer retourné par la page WEB
int  			Temp_i;
unsigned char 	num;
short 			Http_Temp[NB_MAX_CAPTEURS]; // ZONE DE STOCKAGE
BYTE 			Http_byte2[500];
BYTE			Http_byte[500];
time_t			TGetRelais = 0;
BYTE 			*ptr_get;
time_t   		message_test_alarme_mail = 0; // Indique si il faut afficher un message signalant le bon envoi d'un email de test
time_t   		message_test_alarme_sms = 0; // Indique si il faut afficher un message signalant le bon envoi d'un SMS de test

// Prototypes de fonctions
void HTTPGetRelais(unsigned char num);
void HTTPGetTemp(void);
void HTTPGetRaz_Usine(void);
void HTTPGetI2c(void);



//*****************************************************************************
// BYTE HTTPNeedsAuth(BYTE* cFile) : Gestion authentification
//*****************************************************************************
BYTE HTTPNeedsAuth(BYTE* cFile)
{	
	// return 0x00 = Authentification obligatoire !
	// return 0x80 = Pas d'authentification
	
	// Si on a dépassé le temps octroyé en mode Installateur (1h) On bascule en mode User)
	if ((Mode_Admin == 0x81) && (cpt1s > Mode_Admin_cpt1s))	Mode_Admin = 0;

	if(memcmppgm2ram(cFile, (ROM void*)"reboot", 6) == 0)
	{
		if (Mode_Admin != 0x81) return 0x00;		
	}
	else if(memcmppgm2ram(cFile, (ROM void*)"reseau", 6) == 0)
	{
		if (Mode_Admin != 0x81) return 0x00;		
	}
	else if(memcmppgm2ram(cFile, (ROM void*)"fait_reboot", 11) == 0)
	{
	if (Mode_Admin != 0x81) 	return 0x00;		
	}
	else if(memcmppgm2ram(cFile, (ROM void*)"mynetmemo", 9) == 0)
	{
		if (Mode_Admin != 0x81) return 0x00;		
	}
	else if(memcmppgm2ram(cFile, (ROM void*)"parametres", 10) == 0)
	{
		if (Mode_Admin != 0x81) return 0x00;		
	}
	else if(memcmppgm2ram(cFile, (ROM void*)"donnees", 7) == 0)
	{
		if (Mode_Admin != 0x81) return 0x00;		
	}
	else if(memcmppgm2ram(cFile, (ROM void*)"password", 8) == 0)
	{
		if (Mode_Admin != 0x81) return 0x00;		
	}
	else if(memcmppgm2ram(cFile, (ROM void*)"maintenance", 11) == 0)
	{
		if (Mode_Admin != 0x81) return 0x00;		
	}
	return 0x80;			
}

//*****************************************************************************
//	BYTE HTTPCheckAuth(BYTE* cUser, BYTE* cPass)
//  ***************************************************************************
#if defined(HTTP_USE_AUTHENTICATION)
BYTE HTTPCheckAuth(BYTE* cUser, BYTE* cPass)
{		
	BYTE filename[20];
	
	if(strcmppgm2ram((char *)cUser,(ROM char *)User.Login) == 0 && strcmppgm2ram((char *)cPass, (char *)User.Password) == 0)
	{
		Mode_Admin = 0x80;
		MPFSGetFilename(curHTTP.file, filename, 20);
		return 0x80;		
	}	
	else if((strcmppgm2ram((char *)cUser,(ROM char *)"admin") == 0 && strcmppgm2ram((char *)cPass, (char *)"adtek") == 0))
	{
		// En mode Admin, toutes les pages sont accessibles
		Mode_Admin = 0x81;
		Mode_Admin_cpt1s = cpt1s + 3600;
		return 0x81;	
	}
	else if (FONCTION == FONCTION_DEMO)
	{
		if(strcmppgm2ram((char *)cUser,(ROM char *)"admin") == 0 && strcmppgm2ram((char *)cPass, (char *)"demo") == 0)
		{
			return 0x80;	
		}
	}
	return 0x00; // ERREUR LOGIN/PASSWORD
}
#endif
  
//*****************************************************************************
//	HTTP_IO_RESULT HTTPExecuteGet(void)
// Le résultat doit toujours commencer par OK
//*****************************************************************************
HTTP_IO_RESULT HTTPExecuteGet(void)
{
	
	BYTE 			filename[20];
	unsigned char 	num;
	unsigned char	rel;
	unsigned char 	count;
	unsigned char 	fini;
	unsigned char 	car;

	// Si on a dépassé le temps octroyé en mode Installateur (1h) On bascule en mode User)
	if ((Mode_Admin == 0x81) && (cpt1s > Mode_Admin_cpt1s))	Mode_Admin = 0;
	
	MPFSGetFilename(curHTTP.file, filename, 20);
	
	// ============================================== CMD.HTM ===============================================================
	if(strcmp(filename,"cmd.htm") == 0)
	{		
		num = 0;
		// ******************** RELAIS ****************************
		ptr_get = HTTPGetArg(curHTTP.data, (BYTE *)"relais1");
		if (ptr_get != NULL) { num = 1; }
		if (num == 0)
		{
			ptr_get = HTTPGetArg(curHTTP.data, (BYTE *)"relais2");
			if (ptr_get != NULL) { num = 2; }
		}	
		if (num == 0)
		{
			ptr_get = HTTPGetArg(curHTTP.data, (BYTE *)"relais3");
			if (ptr_get != NULL) { num = 3; }
		}		
		if (num == 0)
		{
			ptr_get = HTTPGetArg(curHTTP.data, (BYTE *)"relais4");
			if (ptr_get != NULL) { num = 4; }
		}
		if (num == 0)
		{
			ptr_get = HTTPGetArg(curHTTP.data, (BYTE *)"relais");
			if (ptr_get != NULL) { num = 99; }
		}			
		if (num != 0)
		{
			// On vérifie que l'on ait dépassé un certains temps avant de reformuler un GET	(1 par 5 secondes)
			if (TGetRelais < utc.utc_fr)
			{
				HTTPGetRelais(num);
			}
			else
			{
				strcpy(Http_byte,"ERREUR. Requête trop rapprochée.<br />Prévoir 5 secondes entre chaque requêtes !<br />");
			}			
		}		
		// ************************ TEMPERATURE ************************
		if (!num)
		{
			ptr_get = HTTPGetArg(curHTTP.data,"temp");
			if (ptr_get != NULL) {	HTTPGetTemp();	num = 1;	}
		}
		
		// ***************** RAZ USINE  *************************
		if (!num)
		{
			ptr_get = HTTPGetArg(curHTTP.data,"raz_usine");
			if (ptr_get != NULL) {	HTTPGetRaz_Usine(); num = 1;}
		}
		// ***************** ECTRITURE CONFIG HARDWARE DANS L'I2C *************************
		if (!num)
		{
			ptr_get = HTTPGetArg(curHTTP.data,"i2c");
			if (ptr_get != NULL) {	HTTPGetI2c();	num = 1;}
		}
		// On renvoi vers la page cmd.htm, en ajoutant un paramètre	
		strcpypgm2ram((char*)curHTTP.data, (ROM char*)"/cmd.htm");
		curHTTP.httpStatus = HTTP_REDIRECT;	
		return HTTP_IO_DONE;		
	}
		// ============================================== LOG.HTM ===============================================================
	if(strcmp(filename,"log.htm") == 0)
	{
		num = 0;

		ptr_get = HTTPGetArg(curHTTP.data, (BYTE *)"dind");
		if (ptr_get != NULL)
		{
			fini  = 0;
			count = 0;
			while (!fini)
			{
				car = *ptr_get;
				ptr_get++;
				if (car == 0x00) fini = 1;
				else
				{
					Date_Ind[count] = car;
					count++;
					if (count > 5) fini = 1; // Erreur !
				}
			}
			Date_Ind[count] = 0x00;
			cpt1s_Ind = cpt1s + 60; // On garde le nom de fichier 60s

		}


		ptr_get = HTTPGetArg(curHTTP.data, (BYTE *)"deli");
		if (ptr_get != NULL)
		{
			strcpypgm2ram((char*)curHTTP.data, (ROM char*)"/sparkbox.csv");
			curHTTP.httpStatus = HTTP_REDIRECT;
			return HTTP_IO_DONE;

		}
		strcpy(message_log,"File not found!");
		strcpypgm2ram((char*)curHTTP.data, (ROM char*)"/log.htm");
		curHTTP.httpStatus = HTTP_REDIRECT;
		return HTTP_IO_DONE;
	}
	// ============================================== DEBUG.HTM ===============================================================
	if((strcmp(filename,"debugadtek.htm") == 0) ||(strcmp(filename,"maintenance.htm") == 0))
	{
		rel = 0;
	
		
		// Test Relais
		ptr_get = HTTPGetArg(curHTTP.data, (BYTE *)"de1");
		if (ptr_get != NULL) { rel = 1; }
		ptr_get = HTTPGetArg(curHTTP.data, (BYTE *)"de2");
		if (ptr_get != NULL) { rel = 2; }
		ptr_get = HTTPGetArg(curHTTP.data, (BYTE *)"de3");
		if (ptr_get != NULL) { rel = 3; }
		ptr_get = HTTPGetArg(curHTTP.data, (BYTE *)"de4");
		if (ptr_get != NULL) { rel = 4; }		
									
		if (rel > 0)
		{
			num = Etat_Relais(rel);
			if (num == 0)
			{
				Relais(rel,RELAIS_ON);
			}
			else
			{
				Relais(rel,RELAIS_OFF);
			}
			
		}
		// On reste sur la page
		strcpypgm2ram((char*)curHTTP.data, filename);	
		curHTTP.httpStatus = HTTP_REDIRECT;	
		return HTTP_IO_DONE;
	}
}

//*****************************************************************************
//			GESTION ORIENTATION RESULTAT D'UN POST
//	HTTP_IO_RESULT HTTPExecutePost(void)	
//*****************************************************************************
HTTP_IO_RESULT HTTPExecutePost(void)
{
	BYTE filename[20];
	MPFSGetFilename(curHTTP.file, filename, sizeof(filename));

	// Si on a dépassé le temps octroyé en mode Installateur (1h) On bascule en mode User)
	if ((Mode_Admin == 0x81) && (cpt1s > Mode_Admin_cpt1s))	Mode_Admin = 0;
	
	if(strcmp(filename,"reseau.htm")==0)
	{
		return HTTPPostReseau();
	}
	else if(strcmp(filename,"mynetmemo.htm")==0)
	{
		return HTTPPostMynetmemo();
	}
	else if(strcmp(filename,"parametres.htm")==0)
	{
		return HTTPPostParametres();
	}
	else if(strcmp(filename,"teleinfo.htm")==0)
	{
		return HTTPPostTeleinfo();
	}
	else if(strcmp(filename,"password.htm")==0)
	{
		return HTTPPostPassword();
	}
	else if(strcmp(filename,"donnees.htm")==0)
	{
		return HTTPPostDonnees();
	}
	else if(strcmp(filename,"installateur.htm")==0)
	{
		return HTTPPostInstallateur();
	}
	else if(strcmp(filename,"reboot.htm")==0)
	{
		// newAppConfig.MyIPAddr.Val = AppConfig.MyIPAddr.Val; // TODO utile ?
	}	
	return HTTP_IO_DONE;
}


/****************************************************************************
  Section:
	Dynamic Variable Callback Functions
  ***************************************************************************/

/*****************************************************************************
  Function:
	void HTTPPrint_varname(void)
	
  Internal:
  	See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/

void HTTPPrint_builddate(void)
{
	curHTTP.callbackPos = 0x01;
	if(TCPIsPutReady(sktHTTP) < strlenpgm((ROM char*)__DATE__" "__TIME__))
	{
		return;
	}
	curHTTP.callbackPos = 0x00;
	TCPPutROMString(sktHTTP, (ROM void*)__DATE__" "__TIME__);
}


ROM BYTE HTML_UP_ARROW[] = "up";
ROM BYTE HTML_DOWN_ARROW[] = "dn";


unsigned char ADTEK_HTTP_Return(WORD size)
{
	if(TCPIsPutReady(sktHTTP) < size)
	{
		curHTTP.callbackPos = 0x01;
		return (1);
	}
	curHTTP.callbackPos = 0x00;
	return (0);
}
	
void HTTPPrint_Relais(WORD num)
{
	// Sélectionne le relais
	switch(num)
	{
            
        case 1 : num = RELAIS1; break;           
        case 2 : num = RELAIS2; break;            
        case 3 : num = RELAIS3; break;           
        case 4 : num = RELAIS4; break;		 				

		default:
			num = 1;
	}

	// Affiche le résultat
	TCPPut(sktHTTP, (num?'1':'0'));
	return;
}


void HTTPPrintIP(IP_ADDR ip)
{
	BYTE digits[4];
	BYTE i;
	
	for(i = 0; i < 4u; i++)
	{
		if(i)
			TCPPut(sktHTTP, '.');
		uitoa(ip.v[i], digits);
		TCPPutString(sktHTTP, digits);
	}
}


void HTTPPrint_reboot(void)
{
	Reset();
}

void HTTPPrint_rebootaddr(void)
{// Affichage de l'adresse de reboot
	BYTE digits[4];
	BYTE i;
	
	for(i = 0; i < 4u; i++)
	{
		if(i)TCPPut(sktHTTP, '.');
		uitoa(AppConfig.MyIPAddr.v[i], digits); 
		TCPPutString(sktHTTP, digits);
	}	
}

void HTTPPrint_versiontcpip(void)
{
	TCPPutROMString(sktHTTP, (ROM void*)TCPIP_STACK_VERSION);
}

// Version Logicielle
void HTTPPrint_versionsoftadt(void)
{ 
	TCPPutROMString(sktHTTP, VERSION_SOFT);	
}

// Version matérielle
void HTTPPrint_versionhardadt(void)
{ 		
	strcpy(Http_byte2,"");
	strcat(Http_byte2,"ADT0");
	ctoa(CARTE,Http_byte);
	strcat(Http_byte2,Http_byte);
	strcat(Http_byte2,", V");
	ctoa(VERSION_HARD,Http_byte);
	strcat(Http_byte2,Http_byte);
	strcat(Http_byte2,", ");
	ctoa(NB_RELAIS,Http_byte);
	strcat(Http_byte2,Http_byte);
	strcat(Http_byte2," relais");
	TCPPutString(sktHTTP, Http_byte2);
}


void HTTPPrint_serialadt(void)
{	// Le numéro de série de la carte correspond à son adresse MAC unique !
	BYTE i;	
	for(i = 0; i < 6u; i++)
	{	
		TCPPut(sktHTTP, btohexa_high(AppConfig.MyMACAddr.v[i]));
		TCPPut(sktHTTP, btohexa_low(AppConfig.MyMACAddr.v[i]));
		if (i < 5) TCPPut(sktHTTP, 0x3A); //:
	}
	curHTTP.callbackPos = 0x00;
	return;
}


void HTTPPrint_u(char num)
{
	strcpy(Http_byte,"");
	
	if (num == 1) ultoa(Http_byte, debug_ui1, 10 );
    else if (num == 2) ultoa( Http_byte, debug_ui2, 10 );   
    else if (num == 3) ultoa( Http_byte, debug_ui3, 10 ); 		
	else if (num == 4) ultoa( Http_byte, debug_ui4, 10 );
	else if (num == 5) ultoa( Http_byte, debug_ui5, 10 ); 
	TCPPutString(sktHTTP,Http_byte);
}

void HTTPPrint_day(void)
{
	ConvertUtcSecToString(utc.utc_fr, Temp_c);
	memcpy(&Http_byte,Temp_c,10);
	Http_byte[10]=0;
	TCPPutString(sktHTTP,Http_byte);
}

void HTTPPrint_hour(void)
{
	ConvertUtcSecToString(utc.utc_fr, Temp_c);
	memcpy(Http_byte, &Temp_c[11],8);
	Http_byte[8]=0;
	TCPPutString(sktHTTP,Http_byte);
}

void HTTPPrint_status_ok(void)
{
	if(lastSuccess)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"block");
	else
		TCPPutROMString(sktHTTP, (ROM BYTE*)"none");
	lastSuccess = FALSE;
}

void HTTPPrint_status_fail(void)
{
	if(lastFailure)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"block");
	else
		TCPPutROMString(sktHTTP, (ROM BYTE*)"none");
	lastFailure = FALSE;
}

// HTTPGetRaz:
// Gestion de l'effacement de l'eeprom i2C pour un retour "usine"  via un GET sur la page cmd.htm
// usage cmd.htm?raz_usine=xxxx
// xxxx =  mot de passe de validation de la commande
void HTTPGetRaz_Usine(void)
{
	// On Protège par un mot de passe (9999)
	if((strcmp((char*)ptr_get,"9999") == 0) || (strcmp((char*)ptr_get,"9999") == 0))
	{
		Raz_Usine();
		Reset();
		strcpy(Http_byte,"OK. Les paramètres de la carte ont été réinitialisés !<br />");
	}
	// C'est all, on affiche toutes les températures
	else
	{
		strcpy(Http_byte,"OK. ERREUR. Mot de passe incorrect.<br />");
	}	
	TGetRelais = utc.utc_fr + 5; // On autorisera une nouvelle requête que dans 5 secondes !		
}




// HTTPGetI2c:
// Ecriture dans l'EEPROM I2C via un GET sur la page cmd.htm
// usage cmd.htm?i2c=xxxx&valeur=yyy v(xxxx = adresse en décimal et yyy = valeur en décimal (char))
// Attention, on ne peux pas programmer FF en valeur !
// exemple : http://192.168.0.207/cmd.htm?i2c=6400&valeur=7
void HTTPGetI2c(void)
{
	unsigned short num     = 0;
	unsigned short adresse = 0xFFFF;
	unsigned char  valeur  = 0xFF;
	unsigned char car;
	unsigned char count;
	unsigned char fini;
	
	// Lecture de l'adresse
	fini  = 0;
	count = 0;
	while (!fini)
	{
		car = *ptr_get;
		ptr_get++;
		if (car == 0x00) fini = 1;
		else
		{
			Http_byte[count] = car;
			count++;
			if (count > 20) fini = 1; // Erreur !
		}
	}
	Http_byte[count] = 0x00;
	if (count > 0)
	{
		adresse = (unsigned short) atoi( Http_byte );
	}
	// Lecture de la valeur
	ptr_get = HTTPGetArg(curHTTP.data,"valeur");
	if (ptr_get != NULL)
	{
		fini  = 0;
		count = 0;
		while (!fini)
		{
			car = *ptr_get;
			ptr_get++;
			if (car == 0x00) fini = 1;
			else
			{
				Http_byte[count] = car;
				count++;
				if (count > 20) fini = 1; // Erreur !
			}
		}
		Http_byte[count] = 0x00;
		if (count > 0)
		{
			valeur = (unsigned char) atoi( Http_byte );	
		}
		
		// Tout est ok, on programme l'eeprom
		if ((adresse != 0xFFFF) && (valeur != 0xFF))
		{
			Eeprom_Ecriture_Config(adresse,valeur);
			strcpy(Http_byte,"OK <br />EEPROM programmée!");
		}		
		else
		{
			strcpy(Http_byte,"OK <br />EEPROM ERREUR DE PARAMETRES!");
		}
	}
	else
	{
		strcpy(Http_byte,"OK <br />EEPROM ERREUR DE PARAMETRE!");
	}
}

// HTTPGetTemp:
// Gestion de la température via un GET sur la page cmd.htm
// usage cmd.htm?temp=yy
// yy =  numéro de capteur (1 à 16) ou "all" pour tous les capteurs 
void HTTPGetTemp(void)
{
	unsigned char num;
	
	// On affiche un capteur car "all" n'est pas trouvé
	if(strcmp((char*)ptr_get,"all") != 0)
	{
		num = (*ptr_get - 0x31);
		Affiche_Temp(num);
	}
	// C'est all, on affiche toutes les températures
	else
	{
		Affiche_Temp_All();
	}	
	TGetRelais = utc.utc_fr + 1; // On autorisera une nouvelle requête que dans 1 secondes !		
}


// HTTPGetRelais:
// Gestion des relais via un GET sur la page cmd.htm
// usage cmd.htm?relaisx=yy&time=zz
// ou    cmd.htm?relaisx=yy
// ou	 cmd.htm?relais pour connaitre l'état des relais
// x = numéro de relais
// yy = on ou off
// zz = temps d'activation du relais si "on"
void HTTPGetRelais(unsigned char num)
{
	unsigned char 	etat;	
	unsigned short 	duree = 0;
	
	if(strcmp((char*)ptr_get,"on") == 0) etat = RELAIS_ON;
	else if(strcmp((char*)ptr_get,"off") == 0) etat = RELAIS_OFF;
	else if (num != 99) return;
	
	ptr_get = HTTPGetArg(curHTTP.data,"time");
	if (ptr_get != NULL)
	{
		duree = atoi(ptr_get);
	}	
	if (num <= 4) 
	{
		strcpy(Http_byte,"OK <br />ERREUR. Relais numéro 1 à 4 non accessibles via http car réservé à la PVTBox!");
	}	
	else if (num <=8) 
	{
		Relais_Man[num-1].Relais = etat;
		if (duree != 0)
		{
			Relais_Man[num-1].Time	= utc.utc_fr + duree;
		}
		else
		{
			Relais_Man[num-1].Time	= 0;
		}
		Affiche_Etat_Relais();	
	}
	// On veut juste l'état des relais
	else if (num == 99)
	{
		Affiche_Etat_Relais();
	}		 
	TGetRelais = utc.utc_fr + 5; // On autorisera une nouvelle requête que dans 5 secondes !			
}


void HTTPPrint_debug_bt(void)
{
	if (BOUTON == 0) 
	{
		TCPPutString(sktHTTP, "Appuyé");
	} 
	else
	{
		TCPPutString(sktHTTP, "-");
	} 
}


void HTTPPrint_opto1(void)
{
	if (OPTO1_FILTRE == 0)
	{
		TCPPutString(sktHTTP, "1");
	}
	else
	{
		TCPPutString(sktHTTP, "0");
	}

}
void HTTPPrint_opto2(void)
{
	if (OPTO2_FILTRE == 0)
	{
		TCPPutString(sktHTTP, "1");
	}
	else
	{
		TCPPutString(sktHTTP, "0");
	}
}

void HTTPPrint_header(void)
{
	if (ADTEK_HTTP_Return(600))return;
	
	TCPPutString(sktHTTP, "<div id=\"title\"><div class=\"right\">");
			
	TCPPutString(sktHTTP, "</div></div>");
	TCPPutString(sktHTTP, "<div id=\"menu\">");
	TCPPutString(sktHTTP, "<a href=\"index.htm\">ACCUEIL</a>");
	TCPPutString(sktHTTP, "<a href=\"parametres.htm\">PARAMETRES</a>");
	TCPPutString(sktHTTP, "<a href=\"teleinfo.htm\">TELEINFO</a>");
	if (Sparkbox.Type_Monitoring & MONITORING_MYNETMEMO) TCPPutString(sktHTTP, "<a href=\"mynetmemo.htm\">MYNETMEMO</a>");
	TCPPutString(sktHTTP, "<a href=\"password.htm\">MOT DE PASSE</a>");
	TCPPutString(sktHTTP, "<a href=\"reseau.htm\">RESEAU</a>");
	TCPPutString(sktHTTP, "<a href=\"donnees.htm\">DONNEES MENSUELLES</a>");
	TCPPutString(sktHTTP, "<a href=\"log.htm\">HISTORIQUE</a>");
	TCPPutString(sktHTTP, "<a href=\"status.xml\">Page XML</a>");
	TCPPutString(sktHTTP, "<a href=\"about.htm\">A PROPOS</a>");		
	TCPPutString(sktHTTP, "<a href=\"reboot.htm\">REBOOT</a>");
	TCPPutString(sktHTTP, "</div>");	
	
}

void HTTPPrint_rel_existe(unsigned char num)
{
	if (ADTEK_HTTP_Return(20))return;
	if (num > NB_RELAIS)
	{
		TCPPutString( sktHTTP, "disabled=\"disabled\"" );
	}
	
}

// Uptime
void HTTPPrint_Uptime(void)
{	
	ultoa(Http_byte, cpt1s, 10 );
	TCPPutString( sktHTTP, Http_byte );
}
	
void HTTPPrint_led(unsigned	char num)
{
	if (num == 1)
	{
		if (LED1 == LED_ON)  TCPPutString( sktHTTP,"1" );
		else				 TCPPutString( sktHTTP,"0" );
	}
	else 
	{
		if (LED2 == LED_ON)  TCPPutString( sktHTTP,"1" );
		else				 TCPPutString( sktHTTP,"0" );
	}
} 


void HTTPPrint_bp(void)
{
	if (BP_FILTRE == 1)	TCPPutString( sktHTTP,"0" );
	else				TCPPutString( sktHTTP,"1" );
}

void HTTPPrint_pilot(void)
{
	if (ADTEK_HTTP_Return(20))return;

	if (Evse.state == STATE_A)		TCPPutString( sktHTTP,"STATE_A" );
	else if (Evse.state == STATE_B) TCPPutString( sktHTTP,"STATE_B" );
	else if (Evse.state == STATE_C) TCPPutString( sktHTTP,"STATE_C" );
	else if (Evse.state == STATE_D) TCPPutString( sktHTTP,"STATE_D" );
	else if (Evse.state == STATE_E) TCPPutString( sktHTTP,"STATE_E" );
	else if (Evse.state == STATE_F) TCPPutString( sktHTTP,"STATE_F" );
}
void HTTPPrint_ac(unsigned char num)
{
	if (num == 1)
	{
		if (AC1 == 1)	TCPPutString( sktHTTP,"0" );
		else			TCPPutString( sktHTTP,"1" );
	}
	else
	{
		if (AC2 == 1)	TCPPutString( sktHTTP,"0" );
		else			TCPPutString( sktHTTP,"1" );
	}
}

void HTTPPrint_temp(void)
{
	short temp;
	temp = Evse.Temp * 10;

	HectoTempToStr( temp ,Http_byte2);
	TCPPutString( sktHTTP, Http_byte2 );
}