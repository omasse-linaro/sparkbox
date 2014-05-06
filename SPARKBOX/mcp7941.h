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
#ifndef __MCP7941_H
#define __MCP7941_H
	#include "0_SPARKBOX.h"
	
	 #define  ADDR_MCP7941_WRITE   0xde       //  DEVICE ADDR for RTCC MCHP  (writes) 
     #define  ADDR_MCP7941_READ    0xdf       //  DEVICE ADDR for RTCC MCHP  (reads) 
     //.............................................................................................
     #define  ADDR_SEC          0x00       //  address of SECONDS      register 
     #define  ADDR_MIN          0x01       //  address of MINUTES      register 
     #define  ADDR_HOUR         0x02       //  address of HOURS        register 
     #define  ADDR_DAY          0x03       //  address of DAY OF WK    register 
     #define  ADDR_STAT         0x03       //  address of STATUS       register 
     #define  ADDR_DATE         0x04       //  address of DATE         register  
     #define  ADDR_MNTH         0x05       //  address of MONTH        register 
     #define  ADDR_YEAR         0x06       //  address of YEAR         register 
     #define  ADDR_CTRL         0x07       //  address of CONTROL      register 
     #define  ADDR_CAL          0x08       //  address of CALIB        register 
     #define  ADDR_ULID         0x09       //  address of UNLOCK ID    register
     //............................................................................................
     #define  ADDR_ALM0SEC      0x0a       //  address of ALARM0 SEC   register 
     #define  ADDR_ALM0MIN      0x0b       //  address of ALARM0 MIN   register 
     #define  ADDR_ALM0HR       0x0c       //  address of ALARM0 HOUR  register 
     #define  ADDR_ALM0CTL      0x0d       //  address of ALARM0 CONTR register
     #define  ADDR_ALM0DAT      0x0e       //  address of ALARM0 DATE  register 
     #define  ADDR_ALM0MTH      0x0f       //  address of ALARM0 MONTH register 
//............................................................................................. 
     #define  ADDR_ALM1SEC      0x11       //  address of ALARM1 SEC   register 
     #define  ADDR_ALM1MIN      0x12       //  address of ALARM1 MIN   register 
     #define  ADDR_ALM1HR       0x13       //  address of ALARM1 HOUR  register 
     #define  ADDR_ALM1CTL      0x14       //  address of ALARM1 CONTR register
     #define  ADDR_ALM1DAT      0x15       //  address of ALARM1 DATE  register 
     #define  ADDR_ALM1MTH      0x16       //  address of ALARM1 MONTH register 
//.............................................................................................       
     #define  ADDR_SAVtoBAT_MIN 0x18       //  address of T_SAVER MIN(VDD->BAT)
     #define  ADDR_SAVtoBAT_HR  0x19       //  address of T_SAVER HR (VDD->BAT) 
     #define  ADDR_SAVtoBAT_DAT 0x1a       //  address of T_SAVER DAT(VDD->BAT) 
     #define  ADDR_SAVtoBAT_MTH 0x1b       //  address of T_SAVER MTH(VDD->BAT) 
//.............................................................................................
     #define  ADDR_SAVtoVDD_MIN 0x1c       //  address of T_SAVER MIN(BAT->VDD)
     #define  ADDR_SAVtoVDD_HR  0x1d       //  address of T_SAVER HR (BAT->VDD) 
     #define  ADDR_SAVtoVDD_DAT 0x1e       //  address of T_SAVER DAT(BAT->VDD) 
     #define  ADDR_SAVtoVDD_MTH 0x1f       //  address of T_SAVER MTH(BAT->VDD)        
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                  GLOBAL CONSTANTS RTCC - INITIALIZATION 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//     #define  PM                0x20       //  post-meridian bit (ADDR_HOUR)  // TODO
     #define  OUT_PIN           0x80       //  = b7 (ADDR_CTRL) 
     #define  SQWE              0x40       //  SQWE = b6 (ADDR_CTRL) 
     #define  ALM_NO            0x00       //  no alarm activated        (ADDR_CTRL) 
     #define  ALM_0             0x10       //  ALARM0 is       activated (ADDR_CTRL)
     #define  ALM_1             0x20       //  ALARM1 is       activated (ADDR_CTRL)
     #define  ALM_01            0x30       //  both alarms are activated (ADDR_CTRL)
     #define  MFP_01H           0x00       //  MFP = SQVAW(01 HERZ)      (ADDR_CTRL)  
     #define  MFP_04K           0x01       //  MFP = SQVAW(04 KHZ)       (ADDR_CTRL)  
     #define  MFP_08K           0x02       //  MFP = SQVAW(08 KHZ)       (ADDR_CTRL)  
     #define  MFP_32K           0x03       //  MFP = SQVAW(32 KHZ)       (ADDR_CTRL)  
     #define  MFP_64H           0x04       //  MFP = SQVAW(64 HERZ)      (ADDR_CTRL)
     #define  ALMx_POL          0x80       //  polarity of MFP on alarm  (ADDR_ALMxCTL)   
     #define  ALMxC_SEC         0x00       //  ALARM compare on SEC      (ADDR_ALMxCTL)              
     #define  ALMxC_MIN         0x10       //  ALARM compare on MIN      (ADDR_ALMxCTL)   
     #define  ALMxC_HR          0x20       //  ALARM compare on HOUR     (ADDR_ALMxCTL)   
     #define  ALMxC_DAY         0x30       //  ALARM compare on DAY      (ADDR_ALMxCTL)   
     #define  ALMxC_DAT         0x40       //  ALARM compare on DATE     (ADDR_ALMxCTL)   
     #define  ALMxC_ALL         0x70       //  ALARM compare on all param(ADDR_ALMxCTL)    
     #define  ALMx_IF           0x08       //  MASK of the ALARM_IF      (ADDR_ALMxCTL)
     #define  OSCON             0x20       //  state of the oscillator(running or not)
     #define  VBATEN            0x08       //  enable battery for back-up  
     #define  SQVAW    PORTAbits.RA4       //  square wave MFP from RTCC      
     #define  START_32KHZ       0x80       //  start crystal: ST = b7 (ADDR_SEC)
     #define  LP                0x20       //  mask for the leap year bit(MONTH REG)   
     #define  HOUR_12           0x40       //  12 hours format   (ADDR_HOUR)
	


	void 				MCP7941_Init_I2c();
	unsigned char 		MCP7941_Init();
	void 				MCP7941_i2c_wait(unsigned int cnt);
	unsigned char 		MCP7941_Read(unsigned char rtcc_reg);
	unsigned char 		MCP7941_Write(unsigned char rtcc_reg, unsigned char time_var);
	unsigned char 		MCP7941_WriteLongLong(unsigned char rtcc_reg, unsigned long long time_var);
	unsigned long long 	MCP7941_ReadLongLong(unsigned char rtcc_reg);
	unsigned char 		MCP7941_Ecris_An(unsigned short an);
	unsigned short 		MCP7941_Lis_An(void);
	unsigned char 		MCP7941_Ecris_Mois(unsigned char mois);
	unsigned char 		MCP7941_Lis_Mois(void);
	unsigned char 		MCP7941_Ecris_Jour(unsigned char jour);
	unsigned char 		MCP7941_Lis_Jour(void);
	unsigned char 		MCP7941_Ecris_Heure(unsigned char heure);
	unsigned char 		MCP7941_Lis_Heure(void);
	unsigned char 		MCP7941_Ecris_Minute(unsigned char min);
	unsigned char 		MCP7941_Lis_Minute(void);
	unsigned char 		MCP7941_Ecris_Seconde(unsigned char sec);
	unsigned char 		MCP7941_Lis_Seconde(void);
	unsigned char 		MCP7941_Lis_UTC(STRUCT_DATE_ADTEK *tps);
	unsigned char 		MCP7941_Clock(unsigned char etat);
#endif
