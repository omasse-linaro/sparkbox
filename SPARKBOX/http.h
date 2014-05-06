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
#ifndef _HTTP_H
    #define _HTTP_H          
	#include "0_SPARKBOX.h"
   	#include "Eeprom_i2c.h"
	#include "teleinfo.h"
	#include "mynetmemo.h"

	extern char 					Temp_c[250]; // Pour être sûr d'accepter le buffer retourné par la page WEB
	extern BYTE						Http_byte[500];
	extern int  					Temp_i;
	extern unsigned char 			num;
	extern short 					Http_Temp[NB_MAX_CAPTEURS]; // ZONE DE STOCKAGE
	extern BYTE 					Http_byte2[500];
	extern time_t   	   			message_test_alarme_mail;
	extern time_t   	   			message_test_alarme_sms;
	
	extern BOOL lastSuccess;
	extern BOOL lastFailure;
	
	HTTP_IO_RESULT 	HTTPPostMynetmemo(void);
	HTTP_IO_RESULT 	HTTPPostReseau(void);
	HTTP_IO_RESULT 	HTTPPostTeleinfo(void);
	HTTP_IO_RESULT 	HTTPPostPassword(void);
    HTTP_IO_RESULT  HTTPPostParametres(void);
    HTTP_IO_RESULT  HTTPPostDonnees(void);
    HTTP_IO_RESULT HTTPPostConfiguration(void);
	void 			HTTPPrintIP(IP_ADDR ip);
	void 			Affiche_Etat_Relais(void);
	void 			Affiche_Temp(unsigned char num);
	void 			Affiche_Temp_All(void);
	
	unsigned char ADTEK_HTTP_Return(WORD size);
	
#endif
