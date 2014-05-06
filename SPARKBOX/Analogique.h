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
#ifndef ANALOGIQUE_H
    #define ANALOGIQUE_H
    
    #include <stdlib.h>
    #include "HardwareProfile.h" 
    #include "0_SPARKBOX.h"

	#define NB_ANALOGIQUE 5
    
    #define R_MIN        8000
    #define R_MAX       17000
    
    typedef struct 
	{
	    unsigned char   fonction;       // 0 : inutilisé, autres valeurs : fonction régul + 1
	    short           adc;
	    signed 	 short  temperature;
	    unsigned char	Etat;					// Indique l'état du capteur (présent,défectueux,...)	
	} STRUCT_ANALOG;

    extern STRUCT_ANALOG 	Analog[NB_ANALOGIQUE];

    void analogiqueInit(void);
    void analogiqueStart(void);
	void Calcul_Coeff_GFCI(void);
    
#endif

