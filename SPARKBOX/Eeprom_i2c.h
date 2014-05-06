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
#ifndef __EEPROM_I2C_H
#define __EEPROM_I2C_H

	#include "0_SPARKBOX.h"
	#include "mynetmemo.h"
	
	// Définitions pour le Bus I2C
	#define Frequence_EEPROM		100000

	#define EEPROM_I2C_BUS			I2C2 	// I2C2A
	
	
	
    void Init_eeprom();
    void i2c_wait(unsigned int cnt);
    void Ecrit_Octet_Eeprom(unsigned char Addresse_I2c,unsigned int Adresse_memoire,unsigned char Caractere);
	unsigned char Lit_Octet_Eeprom(unsigned char Addresse_I2c,unsigned int Adresse_memoire);
    
	void Init_eeprom();
	void Eeprom_Ecriture_IP(APP_CONFIG Ip);
	unsigned char  Eeprom_Lecture_IP(APP_CONFIG *Config);
	void Eeprom_RAZ_IP(APP_CONFIG *Config);
    
    void Eeprom_Ecriture_Regul(STRUCT_SPARKBOX regul);
	unsigned char Eeprom_Lecture_Regul(STRUCT_SPARKBOX *regul);
	void Eeprom_Raz_Regul(STRUCT_SPARKBOX *regul);
	void Controle_Coherence_Regul(void);
    
	void Eeprom_Ecriture_User(STRUCT_USER user);
	unsigned char Eeprom_Lecture_User(STRUCT_USER *user);
	void Eeprom_Raz_User(STRUCT_USER *user);
	
	void Eeprom_Ecriture_Mynetmemo(STRUCT_MYNETMEMO monitoring);
	unsigned char Eeprom_Lecture_Mynetmemo(STRUCT_MYNETMEMO *monitoring);
	void Eeprom_Raz_Mynetmemo(STRUCT_MYNETMEMO *monitoring);
	
	void Eeprom_Ecriture_Config(unsigned short adresse, unsigned char valeur);
	unsigned char Eeprom_Lecture_Config(unsigned short adresse);	
#endif
