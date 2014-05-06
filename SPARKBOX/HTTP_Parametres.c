/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 * Nom:			HTTP_PARAMETRE.C
 * Fonction :	Gestion de la page Parametres
 *
 *  SARL ADTEK
 **********************************************************************************************************
 * Author | Jean Arhainx  |  Date  19/03/2014   |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or
 * send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *********************************************************************************************************/
#define __HTTP_PARAMETRES_C

#include "TCPIPConfig.h"
#include "TCPIP Stack/TCPIP.h"
#include "0_SPARKBOX.h"
#include "mynetmemo.h"
#include "http.h"
#include "divers.h"
#include "analogique.h"
#include "log.h"

unsigned char Erreur_Http_Parametre;

HTTP_IO_RESULT HTTPPostParametres(void)
{
	unsigned char monit;
	unsigned char email;
	unsigned char menu;
	unsigned char modif;
	unsigned char gmt;
    STRUCT_SPARKBOX  newSparkbox;
    

	
	Erreur_Http_Parametre = 99;
    // Sauvegarde des données 
	monit 		= 0;	
	email		= 0;
	menu		= 0;
	modif 		= 0;	
	gmt 		= 0;  
	newSparkbox = Sparkbox;
	
	
	
	if( curHTTP.byteCount > TCPIsGetReady(sktHTTP) + TCPGetRxFIFOFree(sktHTTP) )
	{
		Erreur_Http_Parametre = 200;
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
			Erreur_Http_Parametre = 201;
			goto ConfigFailure;
		}	
		// Read a form field value
		if( HTTPReadPostValue(curHTTP.data + 6, sizeof(curHTTP.data)-6-2) != HTTP_READ_OK )
		{
			Erreur_Http_Parametre = 202;
			goto ConfigFailure;
		}
        
        if(!strncmp((char*)curHTTP.data, (ROM char*)"ma_",3))
		{
			strcpy ( Temp_c, (char*) curHTTP.data + 3 ); 
	        num = (unsigned char) atoi( Temp_c );	
			email = email |num;
			modif = TRUE;
		}
		else if(!strncmp((char*)curHTTP.data, (ROM char*)"mo",2))
		{
			strcpy ( Temp_c, (char*) curHTTP.data + 2 ); 
	        num = (unsigned char) atoi( Temp_c );
			monit = monit | num;
			modif = TRUE;
		}
		else if(!strncmp((char*)curHTTP.data, (ROM char*)"menu",4))
		{
			strcpy ( Temp_c, (char*) curHTTP.data + 6 ); 
	        num = (unsigned char) atoi( Temp_c );
			menu = num;
			modif = TRUE;
		}
		else if(!strncmp((char*)curHTTP.data, (ROM char*)"co00",4))
		{
			memset(Temp_c,0x00,6);
			memcpy(Temp_c,(char*)curHTTP.data+6,sizeof(curHTTP.data)-6);
			Temp_i = atoi(Temp_c);
			if ( ( Temp_i >= 8 ) && ( Temp_i <= 63 ) )
			{
				newSparkbox.Max_Amp = Temp_i;
			}
			else
			{
				Erreur_Http_Parametre = 0;
				goto ConfigFailure;
			}
			modif = TRUE;
		}
		else if(!strncmp((char*)curHTTP.data, (ROM char*)"co01",4))
		{
			memset(Temp_c,0x00,6);
			memcpy(Temp_c,(char*)curHTTP.data+6,sizeof(curHTTP.data)-6);
			Temp_i = atoi(Temp_c);
			if ( ( Temp_i >= 8 ) && ( Temp_i <= 63 ) )
			{
				newSparkbox.Amp = Temp_i;
			}
			else
			{
				Erreur_Http_Parametre = 1;
				goto ConfigFailure;
			}
			modif = TRUE;
		}
		else if(!strncmp((char*)curHTTP.data, (ROM char*)"co02",4))
		{
			memset(Temp_c,0x00,6);
			memcpy(Temp_c,(char*)curHTTP.data+6,sizeof(curHTTP.data)-6);
			Temp_i = atoi(Temp_c);
			if ( ( Temp_i >=0 ) && ( Temp_i <= 60 ) )
			{
				newSparkbox.Gfci = Temp_i;
			}
			else
			{
				Erreur_Http_Parametre = 2;
				goto ConfigFailure;
			}
			modif = TRUE;
		}
		else if(!strncmp((char*)curHTTP.data, (ROM char*)"co03",4))
		{
			memset(Temp_c,0x00,6);
			memcpy(Temp_c,(char*)curHTTP.data+6,sizeof(curHTTP.data)-6);
			Temp_i = atoi(Temp_c);
			if ( ( Temp_i >=0 ) && ( Temp_i <= 1 ) )
			{
				newSparkbox.Diode = Temp_i;
			}
			else
			{
				Erreur_Http_Parametre = 3;
				goto ConfigFailure;
			}
			modif = TRUE;
		}
		else if(!strncmp((char*)curHTTP.data, (ROM char*)"co04",4))
		{
			memset(Temp_c,0x00,6);
			memcpy(Temp_c,(char*)curHTTP.data+6,sizeof(curHTTP.data)-6);
			Temp_i = atoi(Temp_c);
			if ( ( Temp_i >=0 ) && ( Temp_i <= 1 ) )
			{
				newSparkbox.Collage_Relais = Temp_i;
			}
			else
			{
				Erreur_Http_Parametre = 4;
				goto ConfigFailure;
			}
			modif = TRUE;
		}
		else if(!strncmp((char*)curHTTP.data, (ROM char*)"co05",4))
		{
			memset(Temp_c,0x00,6);
			memcpy(Temp_c,(char*)curHTTP.data+6,sizeof(curHTTP.data)-6);
			Temp_i = atoi(Temp_c);
			if ( ( Temp_i == 0 ) || (( Temp_i >=8 ) && ( Temp_i <= 63 ) ))
			{
				newSparkbox.Amp_Reduit1 = Temp_i;
			}
			else
			{
				Erreur_Http_Parametre = 5;
				goto ConfigFailure;
			}
			modif = TRUE;
		}
		else if(!strncmp((char*)curHTTP.data, (ROM char*)"co06",4))
		{
			memset(Temp_c,0x00,6);
			memcpy(Temp_c,(char*)curHTTP.data+6,sizeof(curHTTP.data)-6);
			Temp_i = atoi(Temp_c);
			if ( ( Temp_i == 0 ) || (( Temp_i >=8 ) && ( Temp_i <= 63 ) ))
			{
				newSparkbox.Amp_Reduit2 = Temp_i;
			}
			else
			{
				Erreur_Http_Parametre = 6;
				goto ConfigFailure;
			}
			modif = TRUE;
		}
		else if(!strncmp((char*)curHTTP.data, (ROM char*)"co07",4))
		{
			memset(Temp_c,0x00,6);
			memcpy(Temp_c,(char*)curHTTP.data+6,sizeof(curHTTP.data)-6);
			Temp_i = atoi(Temp_c);
			if ( ( Temp_i >=0 ) && ( Temp_i <= 3 ) )
			{
				newSparkbox.Lcd = Temp_i;
			}
			else
			{
				Erreur_Http_Parametre = 7;
				goto ConfigFailure;
			}
			modif = TRUE;
		}
		else if(!strncmp((char*)curHTTP.data, (ROM char*)"co08",4))
		{
			memset(Temp_c,0x00,6);
			memcpy(Temp_c,(char*)curHTTP.data+6,sizeof(curHTTP.data)-6);
			Temp_i = atoi(Temp_c);
			if ( ( Temp_i == 0 ) || (( Temp_i >=3 ) && ( Temp_i <= 5 ) ))
			{
				newSparkbox.Ventilation = Temp_i;
			}
			else
			{
				Erreur_Http_Parametre = 8;
				goto ConfigFailure;
			}
			modif = TRUE;
		}
		// Coeff GFCI
		else if(!strncmp((char*)curHTTP.data, (ROM char*)"co09",4))
		{
			if(!StringToHectoTemp(curHTTP.data+6, &newSparkbox.Coef_Gfci))
			{
				Erreur_Http_Parametre = 9;
				goto ConfigFailure;
			}
			modif = TRUE;
		}
    }
       
    //Sauvegarde des parametres 	
   	if (monit != Sparkbox.Type_Monitoring)
   	{
   		modif = 1;
   	}	
   	if (email != Sparkbox.Type_Email) 		modif = 1;
   	if (menu  != Sparkbox.Type_Menu) 		modif = 1;
   	if (gmt	  != Sparkbox.Ecart_Gmt)		modif = 1;
   	if (modif)
   	{
		// Test de cohérence des puissances
		if (newSparkbox.Amp > newSparkbox.Max_Amp) Erreur_Http_Parametre = 90;
		if (newSparkbox.Amp_Reduit1 > newSparkbox.Amp) Erreur_Http_Parametre = 91;
		if (newSparkbox.Amp_Reduit2 > newSparkbox.Amp_Reduit1) Erreur_Http_Parametre = 92;
		if (Erreur_Http_Parametre != 99) goto ConfigFailure;

	   	// On ne sauvegarde pas en version de démonstration
	    if (FONCTION != FONCTION_DEMO)
	    {
			// On vérifie si on a modifié le coefficient GFCI pour une prise en compte immédiate
			if (Sparkbox.Coef_Gfci != newSparkbox.Coef_Gfci)
			{
				Sparkbox.Coef_Gfci			= newSparkbox.Coef_Gfci;
				Calcul_Coeff_GFCI();
				BD_Enregistre_Coef_GFCI(); // Le véritable stockage est dans la mémoire Flash !
			}
		    Sparkbox.Max_Amp			= newSparkbox.Max_Amp;
			Sparkbox.Amp				= newSparkbox.Amp;
			Sparkbox.Gfci				= newSparkbox.Gfci;
			Sparkbox.Diode				= newSparkbox.Diode;
			Sparkbox.Collage_Relais		= newSparkbox.Collage_Relais;
			Sparkbox.Amp_Reduit1		= newSparkbox.Amp_Reduit1;
			Sparkbox.Amp_Reduit2		= newSparkbox.Amp_Reduit2;
			Sparkbox.Lcd				= newSparkbox.Lcd;
			Sparkbox.Ventilation		= newSparkbox.Ventilation;
	   		Sparkbox.Type_Monitoring 	= monit;
	   		Sparkbox.Type_Email			= email;
	   		Sparkbox.Type_Menu			= menu;
	   		Eeprom_Ecriture_Regul(Sparkbox);
			Init_Relais_Manuel();
	   	}	
   		Ajout_Ligne_Log("HTTP: Mise à jour Paramètres");	
   	} 	  	
    return HTTP_IO_DONE;	
	// CONFIG FAILURE
    ConfigFailure:
	lastFailure = TRUE;
	strcpypgm2ram((char*)curHTTP.data, (ROM char*)"parametres.htm");
	curHTTP.httpStatus = HTTP_REDIRECT;		
	return HTTP_IO_DONE;
}


HTTP_IO_RESULT  HTTPPostInstallateur(void)
{
	unsigned char install;

	install	= 0;	
	
	
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
        
        // Mot de passe
		if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"pwd")) 
		{
			memset(Http_byte,0x00,21);	
			memcpy(Http_byte,(char*)curHTTP.data+6,sizeof(curHTTP.data)-6);
			if(!strcmppgm2ram((char*)Http_byte, (ROM char*)"adtek")) 
			{
				install = 1;
			}	
		}		
    }
       
   	if (install)
   	{	   	
	   	// On ne bascule pas en version de démonstration
	    if (FONCTION != FONCTION_DEMO)
	    {
			strcpypgm2ram((char*)curHTTP.data, (ROM char*)"index.htm");
			curHTTP.httpStatus = HTTP_REDIRECT;		
			Ajout_Ligne_Log("HTTP: Passage en mode Installateur");	
			Mode_Admin = 0x81;
			Mode_Admin_cpt1s = cpt1s + 3600;
	   	}	
   	
   	} 	  	
   	
    return HTTP_IO_DONE;
    	
	// CONFIG FAILURE
    ConfigFailure:
	lastFailure = TRUE;
	strcpypgm2ram((char*)curHTTP.data, (ROM char*)"installateur.htm");
	curHTTP.httpStatus = HTTP_REDIRECT;		
	return HTTP_IO_DONE;
}


//--------------------------------------------------------------------------------------------

void HTTPPrint_email_mode(unsigned char num)
{
	if (Sparkbox.Type_Email & num)
	{
		TCPPutROMString(sktHTTP, (ROM BYTE*) " checked=\"checked\"" );
	}
}
		
void HTTPPrint_monit_mode(unsigned char num)
{
	if (Sparkbox.Type_Monitoring & num)
	{
		TCPPutROMString(sktHTTP, (ROM BYTE*) " checked=\"checked\"" );
	}
}
		
void HTTPPrint_menu_mode(unsigned char num)
{
	if (Sparkbox.Type_Menu & num)
	{
		TCPPutROMString(sktHTTP, (ROM BYTE*) " checked=\"checked\"" );
	}
}
void HTTPPrint_gmt()
{
	ctoa(Sparkbox.Ecart_Gmt,Http_byte);
	TCPPutString(sktHTTP, Http_byte);
}



void HTTPPrint_config(unsigned char type, unsigned char num)
{
	unsigned char legende[60]="";
	unsigned char param[10]="";
	unsigned char valeur[15]="";
	unsigned char unite[5]="";
	unsigned char maxlength[20]="";
	unsigned char size[15]="";
	unsigned char name[15]="";
	unsigned char ok = 0;

	if (ADTEK_HTTP_Return(300))return;

	// Traitement des chaines de caractères
	// <td><input type="text" maxlength="5" size="6" name="000" value="~as(0,0,0,0)~"/></td>
	if (type == MAX_AMP)
	{
		strcpy(legende,"Ampérage maximal disponible sur la borne" );
		strcpy(param,"MAX_AMP");
		strcpy(name,"name=\"co00\" ");
		ok = 1;
		ultoa(valeur,Sparkbox.Max_Amp,10);
		strcpy(maxlength, "maxlength=\"4\" ");
		strcpy(size, "size=\"6\" ");
		strcpy(unite,"A");
	}
	else if (type == AMP)
	{
		strcpy(legende,"Ampérage programmé pour la charge");
		strcpy(param,"AMP");
		strcpy(name,"name=\"co01\" ");
		ok = 1;
		ultoa(valeur,Sparkbox.Amp,10);
		strcpy(maxlength, "maxlength=\"4\" ");
		strcpy(size, "size=\"6\" ");
		strcpy(unite,"A");
	}
	else if (type == GFCI)
	{
		strcpy(legende,"Test de fuite de courant (0 = désactivé, Std=30mA Max=60mA)");
		strcpy(param,"GFCI");
		strcpy(name,"name=\"co02\" ");
		ok = 1;
		ultoa(valeur,Sparkbox.Gfci,10);
		strcpy(maxlength, "maxlength=\"4\" ");
		strcpy(size, "size=\"6\" ");
		strcpy(unite,"mA");
	}
	else if (type == DIODE)
	{
		strcpy(legende,"Test de présence de diode  (0 = NON , 1 = OUI)");
		strcpy(param,"DIODE");
		strcpy(name,"name=\"co03\" ");
		ok = 1;
		ultoa(valeur,Sparkbox.Diode,10);
		strcpy(maxlength, "maxlength=\"4\" ");
		strcpy(size, "size=\"6\" ");
		strcpy(unite," ");
	}
	else if (type == RELAIS_STUCK)
	{
		strcpy(legende,"Test de collage de relais  (0 = NON , 1 = OUI)");
		strcpy(param,"COL_REL");
		strcpy(name,"name=\"co04\" ");
		ok = 1;
		ultoa(valeur,Sparkbox.Collage_Relais,10);
		strcpy(maxlength, "maxlength=\"4\" ");
		strcpy(size, "size=\"6\" ");
		strcpy(unite," ");
	}
	else if (type == AMP_REDUIT1)
	{
		strcpy(legende,"Ampérage réduit 1 (1er niveau de délestage)");
		strcpy(param,"AMP_RED1");
		strcpy(name,"name=\"co05\" ");
		ok = 1;
		ultoa(valeur,Sparkbox.Amp_Reduit1,10);
		strcpy(maxlength, "maxlength=\"4\" ");
		strcpy(size, "size=\"6\" ");
		strcpy(unite,"A");
	}
	else if (type == AMP_REDUIT2)
	{
		strcpy(legende,"Ampérage réduit 2 (2eme niveau de délestage)");
		strcpy(param,"AMP_RED2");
		strcpy(name,"name=\"co06\" ");
		ok = 1;
		ultoa(valeur,Sparkbox.Amp_Reduit2,10);
		strcpy(maxlength, "maxlength=\"4\" ");
		strcpy(size, "size=\"6\" ");
		strcpy(unite,"A");
	}
	else if (type == LCD)
	{
		strcpy(legende,"Type LCD (0=aucun, 1 = Interne, 2 = SPI)");
		strcpy(param,"LCD");
		strcpy(name,"name=\"co07\" ");
		ok = 1;
		ultoa(valeur,Sparkbox.Lcd,10);
		strcpy(maxlength, "maxlength=\"4\" ");
		strcpy(size, "size=\"6\" ");
		strcpy(unite," ");
	}
	else if (type == VENTILATION)
	{
		strcpy(legende,"Ventilation (0 = aucune, 3 = Relais3,...)");
		strcpy(param,"VENTIL");
		strcpy(name,"name=\"co08\" ");
		ok = 1;
		ultoa(valeur,Sparkbox.Ventilation,10);
		strcpy(maxlength, "maxlength=\"4\" ");
		strcpy(size, "size=\"6\" ");
		strcpy(unite," ");
	}
	else if (type == COEF_GFCI)
	{
		strcpy(legende,"Coefficient GFCI (défaut = 4.5)");
		strcpy(param,"COEF_GFCI");
		strcpy(name,"name=\"co09\" ");
		ok = 1;
		HectoTempToStr(Sparkbox.Coef_Gfci, valeur); // La valeur stockée = *100
		strcpy(maxlength, "maxlength=\"4\" ");
		strcpy(size, "size=\"6\" ");
		strcpy(unite," ");
	}
	// On insère une ligne au tableau que si elle est remplie !
	if (ok)
	{
		// Début Tableau
		TCPPutString(sktHTTP, "<tr>");
		// 1ere colonne
		TCPPutString(sktHTTP,"<td class=\"c1\">");
		TCPPutString(sktHTTP, param);
		TCPPutString(sktHTTP,"</td>");
		// 2eme colonne
		TCPPutString(sktHTTP,"<td class=\"c2\"><input type=\"text\" ");
		TCPPutString(sktHTTP, maxlength);
		TCPPutString(sktHTTP, size);
		TCPPutString(sktHTTP, name);
		TCPPutString(sktHTTP, "value=\"");
		TCPPutString(sktHTTP, valeur);
		TCPPutString(sktHTTP, "\"/>");
		TCPPutString(sktHTTP,"</td>");
		// 3eme colonne
		TCPPutString(sktHTTP,"<td class=\"c3\">");
		TCPPutString(sktHTTP, unite);
		TCPPutString(sktHTTP,"</td>");
		// 4eme colonne
		TCPPutString(sktHTTP,"<td class=\"c4\">");
		TCPPutString(sktHTTP, legende);
		TCPPutString(sktHTTP,"</td>");
		// Fin tableau
		TCPPutString(sktHTTP,"</tr>");
	}
}


void HTTPPrint_Erreur_Parametre(void)
{
	ultoa(Http_byte,Erreur_Http_Parametre,10);
	TCPPutString(sktHTTP,Http_byte);
}