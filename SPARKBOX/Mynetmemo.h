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
#ifndef __MYNETMEMO_H
	#define __MYNETMEMO_H
	
	// ETATS UTILISES PENDANT LA TRANSMISSION TCP
	#define SM_DONE	0
	#define SM_START  1
	#define SM_SOCKET_OBTAINED 2
	#define SM_DISCONNECT 3	
	
	// Rythme Process (100ms)
	#define TICK_MYNETMEMO	((QWORD)TICKS_PER_SECOND/10ull)
	
   typedef struct
   {
		BYTE 				ServerName[41];	// mynetmemo.com
 	 	WORD 				ServerPort;		 	// 80
 	   	unsigned char  		Login[21];   		// 20 caractères + 0x00
      	unsigned char  		Password[21]; 		// 20 caractères + 0x00
     	unsigned short 		ID_Mynetmemo[NB_MAX_CAPTEURS]; // Numéro de capteur Mynetmemo (0 à 65535)
   } STRUCT_MYNETMEMO;  // 117

	STRUCT_MYNETMEMO Mynetmemo;
	
	STRUCT_SOCKET_BD_CURL Mynetmemo_Socket[NB_MAX_CAPTEURS];

	void Initialise_Mynetmemo(void);
	void Envoi_Donnees_Mynetmemo(unsigned char id_mesure_adtek,unsigned char * capteur);
	void Process_Mynetmemo(void);
	void Process_Jour_Mynetmemo(void);
	
#endif


