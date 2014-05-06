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
#ifndef _TEMPERATURE_H
    #define _TEMPERATURE_H          
    #include "0_SPARKBOX.h"
      
	unsigned char *HectoTempToStr3(short HectoTemp);
	void HectoTempToStr(short HectoTemp,unsigned char* out);
	BOOL StringToHectoTemp(BYTE* str, short* stemp);
	unsigned char *Temptostr(unsigned char id);
	short Filtre_Median(unsigned char No_Capteur, short valeur);
	void Init_Filtre_Median(void);
	
#endif
