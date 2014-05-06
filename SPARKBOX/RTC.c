/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 * Nom:			RTC.C
 * Fonction :	Primitives RTC
 *
 *  SARL ADTEK
 **********************************************************************************************************
 * Author | Jean Arhainx  |  Date  19/03/2014   |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or
 * send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *********************************************************************************************************/

#include <plib.h> 
#include "0_SPARKBOX.h"
#include "rtc.h"
#include "GenericTypeDefs.h"

// Définition des serveurs de TS
#define ADTEK_NB_Serveurs	 2
unsigned char ADTEK_Serveurs[ADTEK_NB_Serveurs][20] = {"91.121.56.211","www.adtek.fr"}; 

STRUCT_SOCKET_BD_CURL 	ADTEK_TS_Socket; 	// Socket de gestion de la connexion TCP avec le TS
unsigned char			ADTEK_DataUrl[512];		// Zone de réception des données de la connexion TCP avec le TS

// FONCTIONS PRIVEES
time_t 	Analyse_Reponse_ADTEK_TS(unsigned char *ptr_reponse);
void RTC_Mise_a_jour(time_t temps_sntp, time_t temps_tz);


//***************************************************************************
// unsigned char BCD2hex( unsigned char bcd_val)
//
//  Conversion de BCD vers hexadécimal
//  Pas de contrôle de validité
//***************************************************************************
unsigned char BCD2hex( unsigned char bcd_val)
{
    return ( 10 * ( ( bcd_val & 0xF0 ) >> 4 ) + ( bcd_val & 0x0F) );  
}

//***************************************************************************
// unsigned char hex2BCD( unsigned char hex_val)
//
//  Conversion d'hexadécimal vers BCD
//  Pas de contrôle de validité
//***************************************************************************
unsigned char hex2BCD( unsigned char hex_val)
{
    return ( ( ( ( hex_val / 10 ) << 4 ) | ( hex_val % 10 ) ) );
}

//***************************************************************************
// unsigned char * date_jh(void)
//
//  Retourne la date et l'heure sous forme ascii
//  ex :23/04/2012 12:13:42
//***************************************************************************
unsigned char * date_jh(void)
{
	static unsigned char out[19];
	
	ConvertUtcSecToString(utc.utc_fr, out);
	out[19]=0;
	
	return(out);
}


//***************************************************************************
// void ConvertUtcSecToString(INT32 utc, char* time_str)
//
//  Conversion du timestamp UTC vers une chaine de caractères
//
//***************************************************************************
void ConvertUtcSecToString(INT32 utc, char* time_str)
{
    WORD seconds;
    WORD minutes;
    WORD hours;
    DWORD days;
    WORD year;
    BYTE monthArray[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    WORD month = 0;
    BYTE buffer[5];
    BYTE counter = 0;

    days = utc / 86400;
    utc -= (days * 86400);
    hours = utc / 3600;
    utc -= ((DWORD)hours * 3600);
    minutes = utc / 60;
    utc -= (minutes * 60);
    seconds = utc;

    year = 1970;
    // This algorithm will iteratively determine how many years have passed. There is a mathematical way to determine how many years have passed, but the equation is complicated by the lack of a leap day on years divisible by 100 (except if the year is also divisible by 400)
    while (((year % 4 == 0) && (days >= 366)) || ((year % 4 != 0) && (days >= 365)))
    {
        if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
        { // It's a Leap Year  
            days -= 366;
        }
        else
        { // Not Leap Year
            days -= 365;
        }
        year++;
    }
    // If the current year is a leap year, add another day to February
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
    {
        monthArray[1]++;
    }
    // Determine the current month
    while (days >= monthArray[month])
    {
        days -= monthArray[month];
        month++;
    }
    month++;
    days++;

    // Convert to standard DD-MM-YYYY hh:mm:ss
    ultoa (buffer,days,10);
    PadBuffer (days, buffer);
    buffer[2] = '/';
    memcpy (time_str, buffer, 3);
    counter += 3;
    
    uitoa (month,buffer);
    PadBuffer (month, buffer);
    buffer[2] = '/';
    memcpy (time_str + counter, buffer, 3);
    counter += 3;
    
    uitoa (year,buffer);
    PadBuffer (year, buffer);
    buffer[4] = ' ';
    memcpy (time_str + counter, buffer, 5);
    counter += 5;
    
    uitoa (hours, buffer);
    PadBuffer (hours, buffer);
    buffer[2] = ':';
    memcpy (time_str + counter, buffer, 3);
    counter += 3;
    
    uitoa (minutes, buffer);
    PadBuffer (minutes, buffer);
    buffer[2] = ':';
    memcpy (time_str + counter, buffer, 3);
    counter += 3;
    
    uitoa (seconds, buffer);
    PadBuffer (seconds, buffer);
    memcpy (time_str + counter, buffer, 2);
    counter += 2;
    
    *(time_str + counter++) = 0;   
}

//*******************************************************************************************************
// void ExtractUTCAnneeMoisJour(INT32 utc, unsigned short *an, unsigned char *mois, unsigned char *jour)
//
//  Extraction du jour, mois, an  du timestamp UTC
//  Entrée : Timestamp UTC
//  Sortie : Jour, mois, an (4 chiffres)
//*******************************************************************************************************
void ExtractUTCAnneeMoisJour(INT32 utc, unsigned short *an, unsigned char *mois, unsigned char *jour)
{
    DWORD days;
    WORD year;
    WORD month = 0;
	BYTE monthArray[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    days = utc / 86400;

    year = 1970;
    while (((year % 4 == 0) && (days >= 366)) || ((year % 4 != 0) && (days >= 365)))
    {
        if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) 
        	{ days -= 366; }
        else
        	{ days -= 365; }
        year++;
    }
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
    {
        monthArray[1]++;
    }
    while (days >= monthArray[month])
    {
        days -= monthArray[month];
        month++;
    }
    month++;
    days++;
	
	*an 	= (unsigned short)year;
	*mois 	= (unsigned char)month;
	*jour	= (unsigned char)days;
}

//*************************************************************************
// void ExtractUTC_Temps(INT32 utc, STRUCT_DATE_ADTEK *tps,char decal)
//
//  Transformation du timestamp UTC en structure de date STRUCT_DATE_ADTEK 
//  Entrée : Timestamp UTC, decal = décalage par rapport au GMT en heures
//  Sortie : STRUCT_DATE_ADTEK
//*************************************************************************
void ExtractUTC_Temps(INT32 utc, STRUCT_DATE_ADTEK *tps, char decal)
{
	BYTE monthArray[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	INT32 t;
	DWORD days;
    WORD year;
    WORD month = 0;
	
	// On garde le Timestamp
	tps->utc = utc;
	// On ajoute le TimeZone	
	tps->utc_fr = utc + (decal * 3600);
	t = tps->utc_fr;
	
	tps->mois 		= 0;
	tps->jour 		= t / 86400;
	days 			= t / 86400;
    t   	   	   -= ((DWORD)tps->jour * 86400);
    tps->heure 		= t / 3600;
    t	 	  	   -= ((DWORD)tps->heure * 3600);
    tps->minute		= t / 60;
    t 		   	   -= ((DWORD)tps->minute * 60);
    tps->seconde	= t;

    year = 1970;
    while (((year % 4 == 0) && (days >= 366)) || ((year % 4 != 0) && (days >= 365)))
    {
        if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
        	{ days -= 366; }
        else
        	{ days -= 365; }
        year++;
    }
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
    {
        monthArray[1]++;
    }
    while (days >= monthArray[month])
    {
        days -= monthArray[month];
        month++;
    }
    month++;
    days++;
	
	tps->annee 	= (unsigned short)year;
	tps->mois 	= (unsigned char)month;
	tps->jour	= (unsigned char)days;
}

//*************************************************************************
// time_t Process_ADTEK_Get_Timestamp(void)
//
//  Récupère le Timestamp d'un server ADTEK !
//  Le process SNTP gère automatiquement les moments de re-synchronisation
//  Essaye à chaque appel si l'heure est inférieure à la date de création du programme (donc heure fausse)
//  Essaye à 0h30 du matin et gère un minimum de 23h entre 2 resynchronisations
//  On affiche une erreur immédiatement, mais on empêche le même affichage d'erreur pendant une heure
//  Sortie : Timestamp  ou 0 en cas d'erreur !
//*************************************************************************
void Process_ADTEK_Get_Timestamp(void)
{
	static time_t 			ADTEK_temps			= 0; // Timestamp UTC (GMT)
	static time_t 			ADTEK_tz			= 0; // Timezone exprimé en secondes (ex 3600 = GMT+1, 7200 = GMT+2)	
	static unsigned char	resultat_adtek_ts	= 0;
	static unsigned char	quitte_adtek_ts		= 0;
	static unsigned short	Idx_DataUrl			= 0;
	static WORD 			nb_recu				= 0;
	static unsigned char	TS_Dernier_Serveur  = 0; // Numéro de serveur à contacter
	static unsigned int		TS_Prochain_TS		= 0; // cpt1s qui vas déclencher la prochaine acquisition
	static unsigned int		TS_Prochain_Erreur	= 0; // cpt1s qui vas déclencher le prochaine affichage d'erreurs
	
	// Gestion des demandes de Timestamp. Uniquement pendant les périodes d'attentes
	if (ADTEK_TS_Socket.DataUploadState == ADTEK_TS_DONE)
	{
		// On attends l'heure prévue pour une nouvelle acquisition RTC
		if (TS_Prochain_TS <= cpt1s)
		{
			ADTEK_TS_Socket.DataUploadState = ADTEK_TS_START;
		}
	}	
		
	
	switch (ADTEK_TS_Socket.DataUploadState)
	{
		case ADTEK_TS_START: //Ouverture Socket
			ADTEK_TS_Socket.DataUploadSocket = TCPOpen((DWORD)ADTEK_Serveurs[TS_Dernier_Serveur], TCP_OPEN_RAM_HOST,(WORD) 80, TCP_PURPOSE_DEFAULT); 
			resultat_adtek_ts = 0;
			quitte_adtek_ts = 0;
			if(ADTEK_TS_Socket.DataUploadSocket == INVALID_SOCKET)	
			{
				ADTEK_TS_Socket.DataUploadState = ADTEK_TS_DONE; // Abandon envoi
				ADTEK_TS_Socket.Erreurs++;
				ADTEK_TS_Socket.Last_Erreur = 0x02;
			}
			else
			{
				ADTEK_TS_Socket.DataUploadState = ADTEK_TS_SOCKET_OBTAINED;
				ADTEK_TS_Socket.DataUploadTimer = TickGet();
			}	
		break;
		
		case ADTEK_TS_SOCKET_OBTAINED: // Envoi Socket
			if(!TCPIsConnected(ADTEK_TS_Socket.DataUploadSocket))
			{ 	
				if((TickGet() - (ADTEK_TS_Socket.DataUploadTimer)) > TICK_5SECONDES) // 5 secondes pour obtenir le socket
				{
					ADTEK_TS_Socket.DataUploadState = ADTEK_TS_DISCONNECT; // Abandon envoi
					ADTEK_TS_Socket.Erreurs++;
					ADTEK_TS_Socket.Last_Erreur = 0x03;
				}
			}
			else
			{					
				if(TCPIsPutReady(ADTEK_TS_Socket.DataUploadSocket) < 150) // Le buffer ne pourrait pas recevoir la chaîne (84 taille max autres strings a envoyer ci apres)
				{
					ADTEK_TS_Socket.DataUploadState = ADTEK_TS_DISCONNECT; // Abandon envoi
					ADTEK_TS_Socket.Erreurs++;
					ADTEK_TS_Socket.Last_Erreur = 0x04;
				}	
				else
				{			
					
					TCPPutROMString(ADTEK_TS_Socket.DataUploadSocket, (ROM BYTE*)"GET /ts.php");
					TCPPutROMString(ADTEK_TS_Socket.DataUploadSocket, (ROM BYTE*)" HTTP/1.0\r\nHost: ");
					TCPPutString(ADTEK_TS_Socket.DataUploadSocket, ADTEK_Serveurs[TS_Dernier_Serveur]);
					TCPPutROMString(ADTEK_TS_Socket.DataUploadSocket, (ROM BYTE*)"\r\nConnection: close\r\n\r\n");
					// Send the packet
					TCPFlush(ADTEK_TS_Socket.DataUploadSocket);
					ADTEK_TS_Socket.DataUploadState = ADTEK_TS_ATTENTE_REPONSE;
					ADTEK_TS_Socket.Envois_Effectues++;
					Idx_DataUrl = 0;
					ADTEK_TS_Socket.DataUploadTimer = TickGet();
				}	
			}
		break;
		
		case ADTEK_TS_ATTENTE_REPONSE: // Attente d'une réponse pendant 1 seconde
			// Comptage des caractères reçus
			nb_recu = TCPIsGetReady(ADTEK_TS_Socket.DataUploadSocket);
			if (nb_recu > 0)
			{
				// Test si dépassement cacacité
				if((nb_recu + Idx_DataUrl) > sizeof(ADTEK_DataUrl) - 1)
				{ 
					if ( nb_recu < Idx_DataUrl)
					{
						Idx_DataUrl = Idx_DataUrl - nb_recu;
					}
					else
					{
						nb_recu = (sizeof(ADTEK_DataUrl) -Idx_DataUrl) - 1;
				 		quitte_adtek_ts = 1;
				 		TCPDiscard(ADTEK_TS_Socket.DataUploadSocket);
				 		Idx_DataUrl = 0;
				 	}	
				}
				if (quitte_adtek_ts != 1)
				{
					nb_recu = TCPGetArray(ADTEK_TS_Socket.DataUploadSocket, &ADTEK_DataUrl[Idx_DataUrl], nb_recu);
					Idx_DataUrl = Idx_DataUrl + nb_recu;
					ADTEK_DataUrl[Idx_DataUrl] = '\0';	
				}	
			}
			if((quitte_adtek_ts == 1) || ((TickGet() - ADTEK_TS_Socket.DataUploadTimer) > (TICK_SECOND*5)) || (!TCPIsConnected(ADTEK_TS_Socket.DataUploadSocket)))
			{
				ADTEK_TS_Socket.DataUploadState = ADTEK_TS_DISCONNECT; 
				ADTEK_temps = Analyse_Reponse_ADTEK_TS((unsigned char *)strrstr(ADTEK_DataUrl,"TS="));
				ADTEK_tz 	= Analyse_Reponse_ADTEK_TS((unsigned char *)strrstr(ADTEK_DataUrl,"TZ="));
			}
					
		break;	
		
		case ADTEK_TS_DISCONNECT: // Deconnexion socket
			TCPDisconnect(ADTEK_TS_Socket.DataUploadSocket);
			ADTEK_TS_Socket.DataUploadSocket 	= INVALID_SOCKET;
			ADTEK_TS_Socket.Last_Send_Ok 		= utc.utc_fr;
			// Erreur, le Timestamp n'a pas été lu. On vas changer de serveur pour le prochain essai
			if (ADTEK_temps < TEMPS_MIN) 
			{   
				// Changement de serveurs
				if (TS_Dernier_Serveur  == ADTEK_NB_Serveurs)
				{
				 	TS_Dernier_Serveur = 0;
				 	// Toutes les heures, en cas d'échec de connexion à tous les serveurs de temps, on affiche un message
				 	if(TS_Prochain_Erreur <= cpt1s)
				 	{
				 		Ajout_Ligne_Log("RTC : Echec de connexion aux serveurs de temps");
				 		TS_Prochain_Erreur = cpt1s + 3600;
				 	}	
				} 	
				else
				{
					TS_Dernier_Serveur++;
				}	
				// Avant une minute, on teste toute les secondes
				if (cpt1s < 60)
				{
					TS_Prochain_TS = cpt1s + 1;
				}
				else // Après une minute, on teste toute les 15 secondes
				{
					TS_Prochain_TS = cpt1s + 15;
				}	
				ADTEK_TS_Socket.DataUploadState = ADTEK_TS_DONE;
			}
			else // Acquisition TS Ok, On programme la prochaine acquisition
			{
				ADTEK_TS_Socket.DataUploadState	= ADTEK_TS_MAJ_RTC;
			}	
		break;
				
		case ADTEK_TS_MAJ_RTC: // Mise à jour de la RTC !
			RTC_Mise_a_jour(ADTEK_temps,ADTEK_tz);
			ADTEK_temps = 0;
			ADTEK_TS_Socket.DataUploadState	= ADTEK_TS_DONE;
			TS_Prochain_TS = cpt1s + 3600; // Toutes les heures
			TS_Dernier_Serveur = 0; // Prochain serveur = numéro 0!
		break;				
	}
}


//*************************************************************************
// time_t Analyse_Reponse_ADTEK_TS(unsigned char *ptr_reponse)
//
//  Récupère le Timestamp de la réponse de ts.php (Script ADTEK)
//  Pour cela la prcédire est appelée avec la chaine de caractère après <body>
//  Sortie : Timestamp  ou 0 en cas d'erreur !
//*************************************************************************
time_t Analyse_Reponse_ADTEK_TS(unsigned char *ptr_reponse)
{
	unsigned char 	rep[31];
	unsigned char 	*ptr;
	time_t 			temps_recu = 0;
	
	if (ptr_reponse != NULL)
	{
		ptr_reponse = ptr_reponse+3; // On se place après le = 
		// On copie le maximum de caractères. Le 0x00 doit être copié de dedans mais on en ajoute un au cas ou
		memcpy(&rep[0],ptr_reponse,sizeof(rep));	 
		rep[30]=0x00;
	  	if ( (ptr = strchr(rep, 0x3B)) != NULL ) // recherche d'un ';' venant  de la fin du champ
 		{
    		rep[ptr-rep] = 0x00;
		}
		temps_recu = atol(rep);
		return(temps_recu);
	}
	return 0;	
}


//*************************************************************************
//  void RTC_Mise_a_jour(time_t temps_sntp)
//  
//  Met à jour la structure de temps de la carte et de l'horloge RTC
//  interne si elle existe
//*************************************************************************
void RTC_Mise_a_jour(time_t temps_sntp, time_t temps_tz)
{
	unsigned char			temps_c1[81];
	unsigned char			temps_c2[20];
	time_t					temps_1			= 0; 
	char					old_gmt;
	time_t					tz;
	STRUCT_DATE_ADTEK		sav_utc;

	// Gestion du Timezone
	tz = (temps_tz / 3600);
	if ((Sparkbox.Ecart_Gmt != (char)tz) && ((char)tz < 12))
	{
		// Le timezone à changé
		Sparkbox.Ecart_Gmt = (char)tz;
		Eeprom_Ecriture_Regul(Sparkbox);
		strcpy(temps_c1,"RTC : Changement Décalage GMT: ");
		ltoa(temps_c2,(long)tz,10);
		strcat(temps_c1,temps_c2);
		strcat(temps_c1,"h");
		Ajout_Ligne_Log(temps_c1);
	}
	
	if (temps_sntp > TEMPS_MIN) // Normalement toujours > car déjà testé avant!
	{
		temps_1 = 0;
		// Calcul du décalage	
		if ((utc.utc != temps_sntp) || (old_gmt != Sparkbox.Ecart_Gmt))
		{	
			strcpy(temps_c1,"RTC : Décalage ");
			if (temps_sntp > utc.utc)
			{
				temps_1 = (unsigned int) (temps_sntp - utc.utc);
				strcat(temps_c1,"+");
			}	 
			else
			{
				temps_1 = (unsigned int) (utc.utc - temps_sntp);
				strcat(temps_c1,"-");
			}	
			if (temps_1 > 1) // On ne corrige que si écart > 1 secondes
			{
				ltoa(temps_c2,temps_1,10);
				strcat(temps_c1,temps_c2);
				strcat(temps_c1,"s");
				//strcat(temps_c1," ts = ");ultoa(temps_c2,temps_sntp,10);strcat(temps_c1,temps_c2); // Pour debug NTP
					
				// Mémorisation timezone
				old_gmt = Sparkbox.Ecart_Gmt;
	
		    	if (temps_1 > 21600) // Décalage > à 6 h; Comme le décalage est important, on remet à jour les stats
		    	{
					// On met à jour le tableau journalier
				//	Init_Jour();
				}
				// Transforme l'heure reçue (Timestamp) en structure ADTEK !
				ExtractUTC_Temps(temps_sntp,&utc,tz); // Avec décalage gmt (tz)
				// On sauvegarde l'heure dans la RTC si elle existe (ADT18)
				ExtractUTC_Temps(temps_sntp,&sav_utc,0); // On part de l'heure utc (sans décalage GMT)
				MCP7941_Clock(STOP); // Obligatoire sinon l'RTC s'arrête
				MCP7941_Ecris_An(sav_utc.annee);
				MCP7941_Ecris_Mois(sav_utc.mois);
				MCP7941_Ecris_Jour(sav_utc.jour);
				MCP7941_Ecris_Heure(sav_utc.heure);
				MCP7941_Ecris_Minute(sav_utc.minute);
				MCP7941_Ecris_Seconde(sav_utc.seconde);
				MCP7941_Clock(START); // Obligatoire sinon l'RTC s'arrête
				strcat(temps_c1,", Sauvegarde heure dans RTC.");					

				// Ajout de la ligne log
				Ajout_Ligne_Log(temps_c1);
			}			
		}
	}	
}			



