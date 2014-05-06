/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 *  SARL ADTEK
 **********************************************************************************************************
 * Author | Jean Arhainx  |  Date  19/03/2014   |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or
 * send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *********************************************************************************************************/
#ifndef __RTC_H
#define __RTC_H
	#include "0_SPARKBOX.h"
	
	// ETATS UTILISES PENDANT LA TRANSMISSION TCP
	#define ADTEK_TS_DONE	0
	#define ADTEK_TS_START  1
	#define ADTEK_TS_SOCKET_OBTAINED 2
	#define ADTEK_TS_ATTENTE_REPONSE 3
	#define ADTEK_TS_DISCONNECT 4
	#define ADTEK_TS_MAJ_RTC 5
	
 	#define TICK_5SECONDES TICK_SECOND * 5
	

    unsigned char 	BCD2hex( unsigned char bcd_val);
    unsigned char 	hex2BCD( unsigned char hex_val);
    unsigned char * date_jh(void);
    void 			ConvertUtcSecToString(INT32 utc, char* time_str);
	void 			ExtractUTCAnneeMoisJour(INT32 utc, unsigned short *an, unsigned char *mois, unsigned char *jour);
	void 			ExtractUTC_Temps(INT32 utc, STRUCT_DATE_ADTEK *tps, char decal);
	void 			PadBuffer (DWORD value, BYTE * buffer);
	void 			Process_ADTEK_Get_Timestamp(void);
	
#endif
