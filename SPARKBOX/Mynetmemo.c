/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 * Nom:			Mynetmemo.c
 * Fonction :	GESTION DE L'ENVOI DE DONNEES VERS MYNETMEMO
 *
 *  SARL ADTEK
 **********************************************************************************************************
 * Author | Jean Arhainx  |  Date  19/03/2014   |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or
 * send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *********************************************************************************************************/

#include "0_SPARKBOX.h"
#include "mynetmemo.h"

#define TICK_5SECONDES TICK_SECOND * 5 

unsigned char * Mynetmemo_Filtre(unsigned char * cap);

//***************************************************************************************
// INITIALISE_MYNETMEMO
//
void Initialise_Mynetmemo(void)
{
	unsigned char i_mynet;
	for (i_mynet = 0 ; i_mynet < NB_MAX_CAPTEURS ; i_mynet++)
	{
		Mynetmemo_Socket[i_mynet].DataUploadState = SM_DONE;
		Mynetmemo_Socket[i_mynet].DataUploadSocket = INVALID_SOCKET;
		Mynetmemo_Socket[i_mynet].Envois_Effectues = 0;
		Mynetmemo_Socket[i_mynet].Erreurs = 0;
		Mynetmemo_Socket[i_mynet].Envois_Demandes = 0;
		Mynetmemo_Socket[i_mynet].Last_Erreur = 0;
	}
}

//***************************************************************************************
// PROCESS_JOUR_MYNETMEMO
// Nettoyage journalier des statistiques structures 
void Process_Jour_Mynetmemo(void)
{
	unsigned char i_mynet;
	for (i_mynet = 0 ; i_mynet < NB_MAX_CAPTEURS ; i_mynet++)
	{
		Mynetmemo_Socket[i_mynet].Envois_Effectues = 0;
		Mynetmemo_Socket[i_mynet].Erreurs = 0;
		Mynetmemo_Socket[i_mynet].Envois_Demandes = 0;
		Mynetmemo_Socket[i_mynet].Last_Erreur = 0;
	}
}

void Envoi_Donnees_Mynetmemo(unsigned char id_mesure_adtek, unsigned char * capteur)
{
	// On v�rifie que le monitoring vers Mynetmemo soit activ�
	if (Sparkbox.Type_Monitoring & MONITORING_MYNETMEMO)
	{
		// On v�rifie si le capteur doit bien �tre envoye sur Mynetmemo
		if (Mynetmemo.ID_Mynetmemo[id_mesure_adtek] != 0)  
		{
			Mynetmemo_Socket[id_mesure_adtek].Envois_Demandes++;
			// On v�rifie que le capteur ne soit pas une cha�ne vide "" et qu'un envoi ne soit pas d�j� en cours
			if ((capteur[0]!=0x00)&&(Mynetmemo_Socket[id_mesure_adtek].DataUploadState == SM_DONE)) 
			{
				Mynetmemo_Socket[id_mesure_adtek].DataUploadState = SM_START;
				strcpy(Mynetmemo_Socket[id_mesure_adtek].Mesure, Mynetmemo_Filtre(capteur));
			}
			else
			{
				Mynetmemo_Socket[id_mesure_adtek].Erreurs++;
				Mynetmemo_Socket[id_mesure_adtek].Last_Erreur = 0x01;
			}		
		}
	}			
}

unsigned char * Mynetmemo_Filtre(unsigned char * cap)
{
	static unsigned char Temp_Mynet[20];
	unsigned char cpt_mf;
	unsigned char fini_mf;
	
	cpt_mf			= 0;
	fini_mf 		= 0;
	Temp_Mynet[0]	= 0x00; // Au cas ou
	
 	while (!fini_mf)
	{
	  if (*cap == 0x00)
	  {
	  	Temp_Mynet[cpt_mf]	= 0x00;
	  	fini_mf 			= 1;
	  }
	  else
	  {
	  	if (*cap == 0x2C) // "," , on remplace par un point
	 	{
	  		Temp_Mynet[cpt_mf] = 0x2E; // "."
	  		cpt_mf++;
	  		cap++;
	  	}
	  	else if (*cap == 0x20) // Espace, on ne recopie pas
	 	{
	  		cap++;
	  	}
	  	else // autres caract�res
	  	{
	  		Temp_Mynet[cpt_mf] = *cap; // ","
	  		cpt_mf++;
	  		cap++;
	  	} 
	  }	
	}
	return(Temp_Mynet);
}


// Quand le capteur est en etat SM_DONE, il n'y a pas de mesures a envoyer.
// Dans ce cas on passe au capteur suivant. (idtcp++)
// Quand on commence une �mission on vas jusqu'a la fin �tape par �tape (a chaque occurence de Process_Mynetmemo)
// sauf erreur ou dans ce cas on passe au capteur suivant

void Process_Mynetmemo(void)
{
	static unsigned char 	idtcp 		= 0;
	static DWORD			t_sav_dms	= 0;
	static DWORD			tps			= 0;
	unsigned char			DataUrl[251];
	
	tps = TickGet();	
	// On n'ex�cute le process qu'au bout d'un temps pr�d�fini (100ms)
	if ( tps - t_sav_dms >= TICK_MYNETMEMO)
	{  
		t_sav_dms = tps;

		switch (Mynetmemo_Socket[idtcp].DataUploadState)
		{
			case SM_START: //R�servation Socket
				Mynetmemo_Socket[idtcp].DataUploadSocket = TCPOpen((DWORD)&Mynetmemo.ServerName[0], TCP_OPEN_RAM_HOST, Mynetmemo.ServerPort, TCP_PURPOSE_DEFAULT); 
				if(Mynetmemo_Socket[idtcp].DataUploadSocket == INVALID_SOCKET)	
				{
					Mynetmemo_Socket[idtcp].DataUploadState = SM_DONE; // Abandon envoi
					Mynetmemo_Socket[idtcp].Erreurs++;
					Mynetmemo_Socket[idtcp].Last_Erreur = 0x02;
				}
				else
				{
					Mynetmemo_Socket[idtcp].DataUploadState = SM_SOCKET_OBTAINED;
					Mynetmemo_Socket[idtcp].DataUploadTimer = TickGet();
				}	
			break;
			
			case SM_SOCKET_OBTAINED: // Envoi Socket
				if(!TCPIsConnected(Mynetmemo_Socket[idtcp].DataUploadSocket))
				{ 	
					if((TickGet() - (Mynetmemo_Socket[idtcp].DataUploadTimer)) > TICK_5SECONDES) // 5 secondes pour avoir le socket
					{
						Mynetmemo_Socket[idtcp].DataUploadState = SM_DISCONNECT; // Abandon envoi
						Mynetmemo_Socket[idtcp].Erreurs++;
						Mynetmemo_Socket[idtcp].Last_Erreur = 0x03;
					}
				}
				else
	
					Mynetmemo_Socket[idtcp].DataUploadTimer = TickGet();
					sprintf((char *)&DataUrl,"/mesure_set.php?uid_write=%s&mesure_id=%i&valeur=%s",Mynetmemo.Password,(int)Mynetmemo.ID_Mynetmemo[idtcp],Mynetmemo_Socket[idtcp].Mesure);					
					if(TCPIsPutReady(Mynetmemo_Socket[idtcp].DataUploadSocket) < strlen(DataUrl) + 84) // Le buffer ne pourrait pas recevoir la cha�ne
					{
						Mynetmemo_Socket[idtcp].DataUploadState = SM_DISCONNECT; // Abandon envoi
						Mynetmemo_Socket[idtcp].Erreurs++;
						Mynetmemo_Socket[idtcp].Last_Erreur = 0x04;
					}	
					else
					{									
						TCPPutROMString(Mynetmemo_Socket[idtcp].DataUploadSocket, (ROM BYTE*)"GET ");
						TCPPutString(Mynetmemo_Socket[idtcp].DataUploadSocket, (BYTE*)&DataUrl);
						TCPPutROMString(Mynetmemo_Socket[idtcp].DataUploadSocket, (ROM BYTE*)" HTTP/1.0\r\nHost: ");
						TCPPutString(Mynetmemo_Socket[idtcp].DataUploadSocket, Mynetmemo.ServerName);
						TCPPutROMString(Mynetmemo_Socket[idtcp].DataUploadSocket, (ROM BYTE*)"\r\nConnection: close\r\n\r\n");
						// Send the packet
						TCPFlush(Mynetmemo_Socket[idtcp].DataUploadSocket);
						Mynetmemo_Socket[idtcp].DataUploadState = SM_DISCONNECT;
						Mynetmemo_Socket[idtcp].Envois_Effectues++;
					}	
			break;
			
			case SM_DISCONNECT: // Deconnexion socket
					TCPDisconnect(Mynetmemo_Socket[idtcp].DataUploadSocket);
					Mynetmemo_Socket[idtcp].DataUploadSocket = INVALID_SOCKET;
					Mynetmemo_Socket[idtcp].DataUploadState = SM_DONE;
	
			break;	
		}
	
		if( Mynetmemo_Socket[idtcp].DataUploadState == SM_DONE)
		{
			// Passage au capteur suivant
			idtcp++;   
			if (idtcp == NB_MAX_CAPTEURS) idtcp = 0; 
		}
	}
}


