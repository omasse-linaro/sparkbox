

/*********************************************************************
 * Envoi des températures 
 *
 * Karine 	 : 00-1E-D0-04-00-03 
 * http://mynetmemo.com/php3/mesure_graph.php?lotmes_secret=igoll_93&nbjour=1
 * 72=T ext,73=T ret,74=T dep,75=PAC
     
 * Hervé     : 00-1E-D0-04-00-01 
 * http://mynetmemo.com/php3/mesure_graph.php?lotmes_secret=ezoqurri_38&nbjour=1
 * 78=T ret,79=T dep,80=T ext,81=T amb,82=T ecs,83=T pisc, 84=PAC, 85,86,87 
 * Test Jean : 00-1E-D0-04-00-05
 * Jean ?    : 00-1E-D0-04-00-04
 ********************************************************************/
 
//#define DEBUG_BDPV
 
#include "0_ADTEK.h"
#include "teleinfo.h"
#include "divers.h"
#include "log.h"
#include "http.h"
#include "bdpv.h"

#define TICK_5SECONDES TICK_SECOND * 5 


unsigned char   Bdpv_Serveur[40]; 
unsigned char	DataUrl[512];
unsigned short	Idx_DataUrl;
unsigned char 	Bdpv_Adco[13];
unsigned char	Bdpv_Index[10];
unsigned char	Bdpv_Date[13];
unsigned char	Bdpv_Api_Demandeur[25];
unsigned char	Bdpv_Api_Secret[26];
unsigned char	Bdpv_Api_Sig[33];  //(16*2+1)
unsigned short	Bdpv_Port_Serveur;

WORD 			nb_recu;
unsigned int	probleme_envoi_bdpv; // A zéro sauf si il faut relancer un envoi vers BDPV. dans ce cas la valeur est celle du cpt1s qui doit déclencher l'envoi
  
void 			Calcul_Date_Bdpv(void);
void 			Calcul_Api_Sig(void);
unsigned char 	ToHex(unsigned char hex);
unsigned char	Analyse_Reponse_BDPV(unsigned char *ptr_reponse);
char *			strrstr(char *string, char *find);

STRUCT_SOCKET_BD_CURL Bdpv_Socket;


//***************************************************************************************
// INITIALISE_BDPV
//
void Initialise_Bdpv(void)
{
	Bdpv_Socket.DataUploadState = BDPV_DONE;
	Bdpv_Socket.DataUploadSocket = INVALID_SOCKET;
	Bdpv_Socket.Envois_Effectues = 0;
	Bdpv_Socket.Erreurs = 0;
	Bdpv_Socket.Envois_Demandes = 0;
	Bdpv_Socket.Last_Erreur = 0;
	Bdpv_Socket.Last_Send_Ok = 0;
	probleme_envoi_bdpv = 0;
}

//***************************************************************************************
// PROCESS_JOUR_BDPV
// Nettoyage journalier des statistiques structures 
void Process_Jour_Bdpv(void)
{
	Bdpv_Socket.Envois_Effectues = 0;
	Bdpv_Socket.Erreurs = 0;
	Bdpv_Socket.Envois_Demandes = 0;
	Bdpv_Socket.Last_Erreur = 0;
	probleme_envoi_bdpv = 0;
}

void Envoi_Donnees_Bdpv(unsigned char * capteur)
{
	// On vérifie que le monitoring vers BDPV activé
	// On recalcule toutes les zones. Ce n'est pas grave car on ne doit avoir qu'un envoi par jour
	if (Regul.Type_Monitoring & MONITORING_BDPV)
	{
		// Debug only !
		#if defined (DEBUG_BDPV)
			strcpy(Bdpv_Serveur,Regul.Bdpv_ServerName);
			Bdpv_Port_Serveur = Regul.Bdpv_ServerPort;
			strcpy(Bdpv_Adco,"021028711311");
			strcpy(Bdpv_Index, "020873928");						
			strcpy(Bdpv_Date,"090320120813");
//			strcpy(Bdpv_Adco,"040722194143");
//			strcpy(Bdpv_Index, "015384500");						
//			strcpy(Bdpv_Date,"030320122238");
			strcpy(Bdpv_Api_Demandeur,"adt_");
			strcat(Bdpv_Api_Demandeur,Regul.Bdpv_Login);
			strcpy(Bdpv_Api_Secret,"2491_");
			strcat(Bdpv_Api_Secret,Regul.Bdpv_Clef);
			Ajout_Ligne_Log("BDPV: Test envoi de données vers BDPV (DEBUG)");
			// Doit donner : "http://bdpv.fr/_service/z_teleinfo_gen2.php?ADCO=040722194143&INDEX=015384499&DATE=030320122237&api_demandeur=adt_invite&api_sig=9feec1c2a2b77d55aaaa20366a6cd146"
			                               //_service/z_teleinfo_gen2.php?ADCO=040722194143&INDEX=015384499&DATE=030320122237&api_demandeur=adt_invite&api_sig=9feec1c2a2b77d55aaaa20366a6cd146
			                              		                               
		// Cas normal	
		#else
			strcpy(Bdpv_Serveur,Regul.Bdpv_ServerName);
			Bdpv_Port_Serveur = Regul.Bdpv_ServerPort;
			strcpy(Bdpv_Adco,Compteur[0].adco);
			strcpy(Bdpv_Index, capteur);						
			Calcul_Date_Bdpv();
			strcpy(Bdpv_Api_Demandeur,"adt_");
			strcat(Bdpv_Api_Demandeur,Regul.Bdpv_Login);
			strcpy(Bdpv_Api_Secret,"2491_");
			strcat(Bdpv_Api_Secret,Regul.Bdpv_Clef);		
		#endif
		Calcul_Api_Sig();		
		Bdpv_Socket.DataUploadState = BDPV_START;
	}			
}


// Quand le capteur est en etat BDPV_DONE, il n'y a pas de mesures a envoyer.

void Process_Bdpv(void)
{
	static DWORD			t_sav_dms		= 0;
	static DWORD			t_get			= 0;
	static DWORD			tps				= 0;
	static unsigned char	reponse_count 	= 0;
	static unsigned char 	regime_count	= 0;
	static unsigned char	resultat_bdpv	= 0;
	static unsigned char	quitte			= 0;
	
	
	switch (Bdpv_Socket.DataUploadState)
	{
		case BDPV_START: //Ouverture Socket
			Bdpv_Socket.DataUploadSocket = TCPOpen((DWORD)Bdpv_Serveur, TCP_OPEN_RAM_HOST,(WORD) Bdpv_Port_Serveur, TCP_PURPOSE_DEFAULT); 
			resultat_bdpv = 0;
			quitte = 0;
			probleme_envoi_bdpv = 0; 
			if(Bdpv_Socket.DataUploadSocket == INVALID_SOCKET)	
			{
				Bdpv_Socket.DataUploadState = BDPV_DONE; // Abandon envoi
				Bdpv_Socket.Erreurs++;
				Bdpv_Socket.Last_Erreur = 0x02;
			}
			else
			{
				Bdpv_Socket.DataUploadState = BDPV_SOCKET_OBTAINED;
				Bdpv_Socket.DataUploadTimer = TickGet();
			}	
		break;
		
		case BDPV_SOCKET_OBTAINED: // Envoi Socket
			if(!TCPIsConnected(Bdpv_Socket.DataUploadSocket))
			{ 	
				if((TickGet() - (Bdpv_Socket.DataUploadTimer)) > TICK_5SECONDES) // 5 secondes pour obtenir le socket
				{
					Bdpv_Socket.DataUploadState = BDPV_DISCONNECT; // Abandon envoi
					Bdpv_Socket.Erreurs++;
					Bdpv_Socket.Last_Erreur = 0x03;
				}
			}
			else
			{
				#if defined (DEBUG_BDPV)	
					Ajout_Ligne_Log("BDPV: Préparation chaine pour BDPV (DEBUG)");	
				#endif
				// Fabrication de la chaine de caractère a envoyer dans l'url (get)		
				#if defined (DEBUG_BDPV)
					sprintf((char *)&DataUrl,"/_service/z_teleinfo_gen.php?ADCO=%s&INDEX=%s&DATE=%s&api_demandeur=%s&api_sig=%s",Bdpv_Adco,Bdpv_Index,Bdpv_Date,Bdpv_Api_Demandeur,Bdpv_Api_Sig);					
					//sprintf((char *)&DataUrl,"/_service/z_teleinfo_gen2.php?ADCO=%s&INDEX=%s&DATE=%s&api_demandeur=%s&api_sig=%s",Bdpv_Adco,Bdpv_Index,Bdpv_Date,Bdpv_Api_Demandeur,Bdpv_Api_Sig);					
				#else
					sprintf((char *)&DataUrl,"/_service/z_teleinfo_gen.php?ADCO=%s&INDEX=%s&DATE=%s&api_demandeur=%s&api_sig=%s",Bdpv_Adco,Bdpv_Index,Bdpv_Date,Bdpv_Api_Demandeur,Bdpv_Api_Sig);					
				#endif
				if(TCPIsPutReady(Bdpv_Socket.DataUploadSocket) < strlen(DataUrl) + 84) // Le buffer ne pourrait pas recevoir la chaîne (84 taille max autres strings a envoyer ci apres)
				{
					Bdpv_Socket.DataUploadState = BDPV_DISCONNECT; // Abandon envoi
					Bdpv_Socket.Erreurs++;
					Bdpv_Socket.Last_Erreur = 0x04;
				}	
				else
				{			
					
					TCPPutROMString(Bdpv_Socket.DataUploadSocket, (ROM BYTE*)"GET ");
					TCPPutString(Bdpv_Socket.DataUploadSocket, (BYTE*)&DataUrl);
					TCPPutROMString(Bdpv_Socket.DataUploadSocket, (ROM BYTE*)" HTTP/1.0\r\nHost: ");
					TCPPutString(Bdpv_Socket.DataUploadSocket, Bdpv_Serveur);
					TCPPutROMString(Bdpv_Socket.DataUploadSocket, (ROM BYTE*)"\r\nConnection: close\r\n\r\n");
					// Send the packet
					TCPFlush(Bdpv_Socket.DataUploadSocket);
					Bdpv_Socket.DataUploadState = BDPV_ATTENTE_REPONSE;
					reponse_count = 0;
					regime_count  = 0;
					Bdpv_Socket.Envois_Effectues++;
					Idx_DataUrl = 0;
					Bdpv_Socket.DataUploadTimer = TickGet();
				}	
			}
		break;
		
		case BDPV_ATTENTE_REPONSE: // Attente d'une réponse pendant 1 seconde
			// Comptage des caractères reçus
			nb_recu = TCPIsGetReady(Bdpv_Socket.DataUploadSocket);
			if (nb_recu > 0)
			{
				// Test si dépassement cacacité
				if((nb_recu + Idx_DataUrl) > sizeof(DataUrl) - 1)
				{ 
					if ( nb_recu < Idx_DataUrl)
					{
						Idx_DataUrl = Idx_DataUrl - nb_recu;
					}
					else
					{
						nb_recu = (sizeof(DataUrl) -Idx_DataUrl) - 1;
				 		quitte = 1;
				 		TCPDiscard(Bdpv_Socket.DataUploadSocket);
				 		Idx_DataUrl = 0;
				 	}	
				}
				if (quitte != 1)
				{
					nb_recu = TCPGetArray(Bdpv_Socket.DataUploadSocket, &DataUrl[Idx_DataUrl], nb_recu);
					Idx_DataUrl = Idx_DataUrl + nb_recu;
					DataUrl[Idx_DataUrl] = '\0';
					#if defined (DEBUG_BDPV)	
						Ajout_Ligne_Log(DataUrl);
					#endif	
				}	
			}
			if((quitte == 1) || ((TickGet() - Bdpv_Socket.DataUploadTimer) > (TICK_SECOND*5)) || (!TCPIsConnected(Bdpv_Socket.DataUploadSocket)))
			{
				#if defined (DEBUG_BDPV)	
					Ajout_Ligne_Log("BDPV: Analyse réponse BDPV.");
				#endif
				resultat_bdpv = Analyse_Reponse_BDPV(strrstr(DataUrl,"\r\n\r"));
				Bdpv_Socket.DataUploadState = BDPV_DISCONNECT; 
			}
					
		break;	
		
		case BDPV_DISCONNECT: // Deconnexion socket
				TCPDisconnect(Bdpv_Socket.DataUploadSocket);
				Bdpv_Socket.DataUploadSocket = INVALID_SOCKET;
				Bdpv_Socket.DataUploadState = BDPV_DONE;

				if (resultat_bdpv == 0)
				{
					// Problème envoi BDPV
					probleme_envoi_bdpv  = cpt1s + 3600; // On programme un envoi dans une heure
					// On ajoute une trace de débogage !
					strcpy(Http_byte,"BDPV: Serveur=");
					strcat(Http_byte,Bdpv_Serveur);
					strcat(Http_byte," ADCO=");
					strcat(Http_byte,Bdpv_Adco);
					Ajout_Ligne_Log(Http_byte);
					
					strcpy(Http_byte,"BDPV: Index=");
					strcat(Http_byte,Bdpv_Index);
					strcat(Http_byte," Date=");
					strcat(Http_byte,Bdpv_Date);
					strcat(Http_byte," Login=");
					strcat(Http_byte,Regul.Bdpv_Login);
					Ajout_Ligne_Log(Http_byte);
					
					strcpy(Http_byte,"BDPV: Signature=");
					strcat(Http_byte,Bdpv_Api_Sig);
					Ajout_Ligne_Log(Http_byte);
					
				}
				else
				{
					Bdpv_Socket.Last_Send_Ok 	= utc.utc_fr;
					probleme_envoi_bdpv 		= 0; 	// 07/03/13 Cette ligne corrige peut être le bug ?
				}
		break;	
	}
}

void Calcul_Date_Bdpv(void)
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
	INT32 ut;

    days = utc.utc_fr / 86400;
    ut = utc.utc_fr - (days * 86400);
    hours = ut / 3600;
    ut -= ((DWORD)hours * 3600);
    minutes = ut / 60;
    ut -= (minutes * 60);
    seconds = ut;

    year = 1970;
    // This algorithm will iteratively determine how many years have passed
    // There is a mathematical way to determine how many years have passed,
    // but the equation is complicated by the lack of a leap day on years
    // divisible by 100 (except if the year is also divisible by 400)
    while (((year % 4 == 0) && (days >= 366)) || ((year % 4 != 0) && (days >= 365)))
    {
        if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
        {
            // It's a Leap Year
            days -= 366;
        }
        else
        {
            // Not Leap Year
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

    // Convertion vers JJMMAAAAHHMM
    // JJ/MM/AAAA
    ultoa (buffer,days,10);
    PadBuffer (days, buffer);
    memcpy (Bdpv_Date, buffer, 2);
    counter += 2;
    
    uitoa (month,buffer);
    PadBuffer (month, buffer);
    memcpy (Bdpv_Date + counter, buffer, 2);
    counter += 2;
    
    uitoa (year,buffer);
    PadBuffer (year, buffer);
    memcpy (Bdpv_Date + counter, buffer, 4);
    counter += 4;
    
    uitoa (hours, buffer);
    PadBuffer (hours, buffer);
    memcpy (Bdpv_Date + counter, buffer, 2);
    counter += 2;
    
    uitoa (minutes, buffer);
    PadBuffer (minutes, buffer);
    memcpy (Bdpv_Date + counter, buffer, 2);
    counter += 2;
  
    *(Bdpv_Date + counter++) = 0;
}

void Calcul_Api_Sig(void)
{	
	unsigned char 	i_sig;
	unsigned char 	c_sig;
	unsigned char 	md5_Resultat[16];
	HASH_SUM 	  	md5;
	
	MD5Initialize(&md5);

	MD5AddData(&md5, Bdpv_Api_Secret, strlen(Bdpv_Api_Secret));	
	MD5AddData(&md5, "ADCO", 4);
	MD5AddData(&md5, Bdpv_Adco, strlen(Bdpv_Adco));
	MD5Calculate(&md5, md5_Resultat);
	MD5AddData(&md5, "DATE", 4);
	MD5AddData(&md5, Bdpv_Date, strlen(Bdpv_Date));
	MD5Calculate(&md5, md5_Resultat);
	MD5AddData(&md5, "INDEX", 5);
	MD5AddData(&md5, Bdpv_Index, strlen(Bdpv_Index));
	MD5Calculate(&md5, md5_Resultat);
	MD5AddData(&md5, "api_demandeur", 13);
	MD5AddData(&md5, Bdpv_Api_Demandeur, strlen(Bdpv_Api_Demandeur));
			
	MD5Calculate(&md5, md5_Resultat);
	// Transformation md5
	for (i_sig = 0; i_sig < 16; i_sig++)
	{
		c_sig = md5_Resultat[i_sig] / 16;
		Bdpv_Api_Sig[i_sig*2]=ToHex(c_sig);
		c_sig = md5_Resultat[i_sig] - ( c_sig * 16);
		Bdpv_Api_Sig[(i_sig*2)+1]=ToHex(c_sig);
	}
	Bdpv_Api_Sig[32]=0x00;
}

unsigned char ToHex(unsigned char hex)
{
	if (hex < 10)
	{
		return(hex + 0x30);		
	}
	else
	{
		return(hex + 0x57);
	}
}

unsigned char Analyse_Reponse_BDPV(unsigned char *ptr_reponse)
{
	unsigned char rep[81];
	unsigned char *ptr;
	
	if (ptr_reponse != NULL)
	{
		ptr_reponse = ptr_reponse+4;
		strcpy(rep,"BDPV:");
		// On copie le maximum de caractères. Le 0x00 doit être copié de dedans mais on en ajoute un au cas ou
		memcpy(&rep[5],ptr_reponse,75);	 // 75 = 81-6
		rep[80]=0x00;
	  	if ( (ptr = strchr(rep, 0x2E)) != NULL ) // recherche d'un '.'
 		{
    		rep[ptr-rep] = 0x00;
		}
		Ajout_Ligne_Log(rep);
		if ((ptr_reponse[0] == 0x33) || (ptr_reponse[0] == 0x34))
		{
			return 1;
		}	
	}
	else
	{
		Ajout_Ligne_Log("BDPV: Pas de réponse.");
	}
	return 0;	
}





// A garder
/*
Je viens de tenter et j'ai bien une signature fausse.

J'ai mis en place une url modifiée (avec un 2) qui est en mode debug
http://bdpv.fr/_service/z_teleinfo_gen2.php?ADCO=040722194143&INDEX=015384499&DATE=030320122237&api_demandeur=adt_invite&api_sig=feb79ef9e384c3f2d65ab588cc2bc36c

Comme tu puex le voir, il y a un soucis dans ta signature
Voilà ce que reçois le script PHP
api_sig = feb79ef9e384c3f2d65ab588cc2bc36c
api_demandeur = adt_invite
(util_ajax_api_secret) api_demandeur : adt_invite
utilisateur : invite
mot de passe : invite
mot de passe attendue : invite  <=   Je vais le chercher dans la base de données
api_secret : 2491_invite <= Je vais le chercher dans mon trousseau de
clef. 2491 étant ce que j'ai du te donner.

Argument de la ligne de commande
ADCO : 040722194143
INDEX : 015384499
DATE : 030320122237
api_demandeur : adt_invite
api_sig => Pas dans le calcul
api_sig qui sera converti en md5 :
2491_inviteADCO040722194143DATE030320122237INDEX015384499api_demandeuradt_invite
2491_inviteADCO021028711311DATE090320120956INDEX020877410api_demandeuradt_tigrou81
api_sig en md5 : 9feec1c2a2b77d55aaaa20366a6cd146
api_sig =feb79ef9e384c3f2d65ab588cc2bc36c
api_sig_calcule = 9feec1c2a2b77d55aaaa20366a6cd146
api_sig =feb79ef9e384c3f2d65ab588cc2bc36c
api_sig_calcule = 9feec1c2a2b77d55aaaa20366a6cd146
-5 - Erreur, la signature est incorrecte
*/

// Jean
//2491_tigrou81ADCO021028711311DATE090320120956INDEX020877410api_demandeuradt_tigrou