/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 * Nom:			HTTP_TELEINFO.C
 * Fonction :	Gestion de la page Teleinfo
 *
 *  SARL ADTEK
 **********************************************************************************************************
 * Author | Jean Arhainx  |  Date  19/03/2014   |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or
 * send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *********************************************************************************************************/
#define __HTTP_TELEINFO_C

#include "TCPIPConfig.h"
#include "TCPIP Stack/TCPIP.h"
#include "0_SPARKBOX.h"
#include "teleinfo.h"
#include "http.h"


HTTP_IO_RESULT HTTPPostTeleinfo(void)
{
	strcpypgm2ram((char*)curHTTP.data, (ROM char*)"teleinfo.htm");		
	curHTTP.httpStatus = HTTP_REDIRECT;
	return HTTP_IO_DONE;
}



void HTTPPrint_tele(unsigned char no_tele, unsigned char info)
{
	unsigned int val_i;
	
	Http_byte2[0]=0;
	no_tele--;
	if ((no_tele != 0)&& (no_tele !=1))
	{
		no_tele = 0;
	}
	
	switch(info)
	{
        case 0:
			if (strcmp(Compteur[no_tele].adco,"") != 0)
			{
				strcat(Http_byte2,Compteur[no_tele].adco);
			}
			break;
			
		case 1:	
				strcat(Http_byte2,OptarifToString(no_tele));
			break;
			
		case 2:
			if (strcmp(Compteur[no_tele].isousc,"") != 0)
			{
				strcat(Http_byte2,Compteur[no_tele].isousc);
				strcat(Http_byte2," A");
			}	
			break;
		
		case 102:
			if (strcmp(Compteur[no_tele].isousc,"") != 0)
			{
				strcat(Http_byte2,Compteur[no_tele].isousc);
			}	
			break;	
				
		case 3:
			if (strcmp(Compteur[no_tele].base,"") != 0)
			{
				strcat(Http_byte2,WattToKwatt(Compteur[no_tele].base));
			}	
			break;
			
		case 103:
			if (strcmp(Compteur[no_tele].base,"") != 0)
			{
				strcat(Http_byte2,Compteur[no_tele].base);
			}	
			break;
			
		case 4:
			if (strcmp(Compteur[no_tele].hc_hc,"") != 0)
			{
				strcat(Http_byte2,WattToKwatt(Compteur[no_tele].hc_hc));
			}
			break;
		
		case 104:
			if (strcmp(Compteur[no_tele].hc_hc,"") != 0)
			{
				strcat(Http_byte2,Compteur[no_tele].hc_hc);
			}
			break;	
			
		case 5:
			if (strcmp(Compteur[no_tele].hc_hp,"") != 0)
			{
				strcat(Http_byte2,WattToKwatt(Compteur[no_tele].hc_hp));
			}	
			break;	
			
		case 105:
			if (strcmp(Compteur[no_tele].hc_hp,"") != 0)
			{
				strcat(Http_byte2,Compteur[no_tele].hc_hp);
			}	
			break;		
						
		case 6:
			strcat(Http_byte2,WattToKwatt(Compteur[no_tele].ejp_hn));
			break;
			
		case 106:
			strcat(Http_byte2,Compteur[no_tele].ejp_hn);
			break;	
				
		case 7:
			strcat(Http_byte2,WattToKwatt(Compteur[no_tele].ejp_hpm));
			break;
			
		case 107:
			strcat(Http_byte2,Compteur[no_tele].ejp_hpm);
			break;	
			
		case 8:
			strcat(Http_byte2,WattToKwatt(Compteur[no_tele].bbr_hc_jb));
			break;
			
		case 108:
			strcat(Http_byte2,Compteur[no_tele].bbr_hc_jb);
			break;	
			
		case 9:
			strcat(Http_byte2,WattToKwatt(Compteur[no_tele].bbr_hp_jb));
			break;
			
		case 109:
			strcat(Http_byte2,Compteur[no_tele].bbr_hp_jb);
			break;	
			
		case 10:
			strcat(Http_byte2,WattToKwatt(Compteur[no_tele].bbr_hc_jw));
			break;
			
		case 110:
			strcat(Http_byte2,Compteur[no_tele].bbr_hc_jw);
			break;	
			
		case 11:
			strcat(Http_byte2,WattToKwatt(Compteur[no_tele].bbr_hp_jw));
			break;
			
		case 111:
			strcat(Http_byte2,Compteur[no_tele].bbr_hp_jw);
			break;							
			
		case 12:
			strcat(Http_byte2,WattToKwatt(Compteur[no_tele].bbr_hc_jr));
			break;
			
		case 112:
			strcat(Http_byte2,Compteur[no_tele].bbr_hc_jr);
			break;			
			
		case 13:
			strcat(Http_byte2,WattToKwatt(Compteur[no_tele].bbr_hp_jr));
			break;
			
		case 113:
			strcat(Http_byte2,Compteur[no_tele].bbr_hp_jr);
			break;	
			
		case 15:
			strcat(Http_byte2,PtecToString(no_tele));
			break;
			
		case 16:
			strcat(Http_byte2,Compteur[no_tele].demain);
			break;
			
		case 171:
			if (strcmp(Compteur[no_tele].iinst1,"") != 0)
			{
				strcat(Http_byte2,Compteur[no_tele].iinst1);
			}	
			break;
			
		case 172:
			if (strcmp(Compteur[no_tele].iinst2,"") != 0)
			{
				strcat(Http_byte2,Compteur[no_tele].iinst2);
			}	
			break;
			
		case 173:
			if (strcmp(Compteur[no_tele].iinst3,"") != 0)
			{
				strcat(Http_byte2,Compteur[no_tele].iinst3);
			}	
			break;
			
		case 191:
			if (strcmp(Compteur[no_tele].imax1,"") != 0)
			{
				strcat(Http_byte2,Compteur[no_tele].imax1);
			}	
			break;	
		
		case 192:
			if (strcmp(Compteur[no_tele].imax2,"") != 0)
			{
				strcat(Http_byte2,Compteur[no_tele].imax2);;
			}	
			break;
			
		case 193:
			if (strcmp(Compteur[no_tele].imax3,"") != 0)
			{
				strcat(Http_byte2,Compteur[no_tele].imax3);
			}	
			break;
	
		case 194:
			if (strcmp(Compteur[no_tele].pmax,"") != 0)
			{
				strcat(Http_byte2,Compteur[no_tele].pmax);
			}	
			break;		
		
		case 20:
			if (strcmp(Compteur[no_tele].papp,"") != 0)
			{
				strcat(Http_byte2,Compteur[no_tele].papp);
			}	
			break; 
			
		case 120:
			if (strcmp(Compteur[no_tele].papp,"") != 0)
			{
				strcat(Http_byte2,Compteur[no_tele].papp);
			}	
			break; 	
		
		case 40: // Puissance moyenne sur 1 minute
			if (Compteur[no_tele].etat == CAPTEUR_OK)
			{
				if (strcmp(Compteur[no_tele].calc_puis_s,"") != 0)
				{
					strcat(Http_byte2,Compteur[no_tele].calc_puis_s);
				}
				else
				{
					strcat(Http_byte2,"0");
				}	
				strcat(Http_byte2," W");
			}	
			break;
		
		case 140: // Puissance moyenne sur 1 minute
			if (Compteur[no_tele].etat == CAPTEUR_OK)
			{
				if (strcmp(Compteur[no_tele].calc_puis_s,"") != 0)
				{
					strcat(Http_byte2,Compteur[no_tele].calc_puis_s);
				}
				else
				{
					strcat(Http_byte2,"0");
				}	
			}	
			break;	
			
		case 41:
			if (Compteur[no_tele].calc_index != 0)
			{
				ultoa(Http_byte,Compteur[no_tele].calc_index,10);
				strcat(Http_byte2,Http_byte);
				strcat(Http_byte2," Wh (");
				val_i = Compteur[no_tele].calc_index / 1000;
				ultoa(Http_byte,val_i,10);
				strcat(Http_byte2,Http_byte);
				strcat(Http_byte2," kWh)");
			}	
			break;	
			
		case 141:
			if (Compteur[no_tele].calc_index != 0)
			{
				ultoa(Http_byte,Compteur[no_tele].calc_index,10);
				strcat(Http_byte2,Http_byte);
			}	
			break;	
			
		case 42:
			if (Compteur[no_tele].calc_max_puis != 0)
			{
				ultoa(Http_byte,Compteur[no_tele].calc_max_puis,10);
				strcat(Http_byte2,Http_byte);
				strcat(Http_byte2," W");
			}	
			break;	
			
		case 142:
			if (Compteur[no_tele].calc_max_puis != 0)
			{
				ultoa(Http_byte,Compteur[no_tele].calc_max_puis,10);
				strcat(Http_byte2,Http_byte);
			}	
			break;		
			
		case 43:
			if (Compteur[no_tele].calc_max_papp != 0)
			{
				ultoa(Http_byte,Compteur[no_tele].calc_max_papp,10);
				strcat(Http_byte2,Http_byte);
				strcat(Http_byte2," VA");
			}	
			break;		
			
		case 143:
			if (Compteur[no_tele].calc_max_papp != 0)
			{
				ultoa(Http_byte,Compteur[no_tele].calc_max_papp,10);
				strcat(Http_byte2,Http_byte);
			}	
			break;			
			
		case 21:
			strcat(Http_byte2,Compteur[no_tele].hhphc);
			break;
			
		case 26:
			if (Compteur[no_tele].erreur > 0)
			{
				uitoa(Compteur[no_tele].erreur, Http_byte);
				strcat(Http_byte2,Http_byte);
				strcat(Http_byte2,"");
			}	
			break;
		default:
			strcat(Http_byte2,"??");
			break;		
	}
	if (Http_byte2[0] == 0) TCPPutString( sktHTTP, " ");	
	else TCPPutString( sktHTTP, Http_byte2);	
}



