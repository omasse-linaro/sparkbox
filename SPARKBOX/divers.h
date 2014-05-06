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
#ifndef _DIVERS_H
    #define _DIVERS_H          
    #include "0_SPARKBOX.h"
   
   	void 			ctoa(char Value, BYTE* Buffer);
   	unsigned char 	Etat_Relais(unsigned char no_relais);
	unsigned char 	Relais(unsigned char no_relais, unsigned char etat_relais);
	unsigned char * No_Serie(void);	
	unsigned char * Compte_Cms(void);
	void 			PadBuffer (DWORD value, BYTE * buffer);
	void 			Init_Relais_Manuel(void);
	void 			Process_Relais_Manuel(void);
	void 			PadLeftZero(BYTE buffer[], unsigned char longueur_totale);
	unsigned char 	Piezzo_Etat(void);
	unsigned char 	SPICalcutateBRG(unsigned int pb_clk, unsigned int spi_clk);
	char 			*strrstr(char *string, char *find);
	void 			lltoa( BYTE* Buffer, long long Value, unsigned char radix);
	int 			strcasecmp(const unsigned char *s1, const unsigned char *s2);
#endif
