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
#ifndef _EVSE_H
    #define _EVSE_H          
	#include "0_SPARKBOX.h"
    
    // PILOT
	#define STATE_A				1	// +12v		N/A	DC	// Not Connected
	#define STATE_B				2	// +9v		-12v	1kHz		// EV Connected (Ready)
	#define STATE_C				3	// +6v		-12v	1kHz		// EV Charge
	#define STATE_D				4	// +3v		-12v	1kHz		// EV Charge Venti. Required
	#define STATE_E				5	// 0v		0v	N/A		// Error
	#define STATE_F				6	// N/A		-12v	N/A		// Unknow Error
	
	#define NONE					0x00
	
	#define DEFAUT_GROUND			0x01
	#define DEFAUT_GROUND__			0xFE
	
	#define DEFAUT_DIODE			0x02
	#define DEFAUT_DIODE__			0xFD
	
	#define DEFAUT_RELAIS			0x04
	#define DEFAUT_RELAIS__			0xFB

	#define DEFAUT_GFCI				0x08
	#define DEFAUT_GFCI__			0xF7

	// Gestion EVSE
    typedef struct
    {
        unsigned char 	state;		// Etat
        //unsigned char	Amp;		// Ampérage disponible
        unsigned char	DutyCycle;	// Rapport Cyclique 	
        unsigned char	Default;
        int				Min;
        int				Max;
        unsigned int	Heure_Debut;
        unsigned int	Heure_Fin;
        unsigned char	Etat_Relais;
        unsigned int	Courant;
        unsigned int	Courant_Diff;
        int				Vref2;
        int				Temp;
        
    } STRUCT_EVSE;
   

   	
   	extern 	STRUCT_EVSE 		Evse;

   	extern  unsigned char Amp	[16];
   	
   	int Init_Timer_1kHz(void);
   	int Init_EVSE(void);
   	int Pilot(unsigned char ampere);
   	int Process_EVSE(void);
   	
   	void Process_BP(void);
   
#endif



