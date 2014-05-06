/*********************************************************************
 *
 *	Hardware specific definitions
 *
 *********************************************************************/

#ifndef __HARDWARE_PROFILE_H
#define __HARDWARE_PROFILE_H

#include "GenericTypeDefs.h"
#include "Compiler.h"



// GESTION CARTE ---------------------------------------------------------
#define SPARKBOX

// DEFINIR LA CARTE UTILISEE (ADT07 - V0 non autorisée)
#define ADT22V0
//*****************************************************
// Attention il faut aussi modifier dans TCPIPConfig.h
//******************************************************

// Ne pas Toucher !!!!!!!!!!!!!!!!
#if defined(ADT22V0) // ADT22 
	#define ADT22
	#define V0
#else
	#error Aucune carte definie !	
#endif


// Déconnecte le capteur et sa valeur dans Regul pour débogguer et modifier les valeurs à la main
//#define DEBUG_CAPTEUR

// Si commenté, alors on sera en DHCP
#define RAZ_IP_STATIQUE  
	
// Gestion de quelques incohérances
#if ( defined(ADT22) && defined(ADT18))
	#error ADT22 et ADT18 definies en meme temps !
#endif	
#if ( defined(ADT18) && !defined(V0) )
	#error ADT18 n existe qu en V0 !
#endif	
#if (!defined(ADT22) && !defined(ADT18))
	#error Aucune carte definie !
#endif

// PIC32MX processor
#if defined(__PIC32MX__) 	
	#define GetSystemClock()		(80000000ul)      
	#define GetInstructionClock()	(GetSystemClock()/1)
	#define GetPeripheralClock()	(GetInstructionClock()/1)
#else
	#error PIC32MX Obligatoire !
#endif


// ETHERNET -----------------------------------------------------------------------------------
#if defined(ADT07)	// External SMSC PHY configuration	
	#define	PHY_RMII				// external PHY runs in RMII mode
	#define	PHY_CONFIG_PRIMARY		// alternate configuration used
	#define	PHY_ADDRESS			0x1	// the address of the National DP83848 PHY
#elif (defined(ADT22))     
	// ENC624J600 Interface Configuration
    #define ENC100_INTERFACE_MODE			0
    #define ENC100_PSP_USE_INDIRECT_RAM_ADDRESSING
    // SS1 - RD9
	#define ENC100_CS_TRIS					(TRISDbits.TRISD9)
	#define ENC100_CS_IO					(LATDbits.LATD9)
	// SDI1 - RC4 // SO is ENCX24J600 Serial Out, which needs to connect to the PIC SDI pin for SPI mode
	#define ENC100_SO_WR_B0SEL_EN_TRIS		(TRISCbits.TRISC4)	
	#define ENC100_SO_WR_B0SEL_EN_IO		(PORTCbits.RC4)
    // SDO1 - RD0 // SI is ENCX24J600 Serial In, which needs to connect to the PIC SDO pin for SPI mode	
	#define ENC100_SI_RD_RW_TRIS			(TRISDbits.TRISD0)	
	#define ENC100_SI_RD_RW_IO				(LATDbits.LATD0)
	// SCK1 - RD10
	#define ENC100_SCK_AL_TRIS				(TRISDbits.TRISD10)
	//dfine ENC100_SCK_AL_IO				(PORTDbits.RD10)
	// ENC624J600 SPI SFR register selection 
	#define ENC100_ISR_ENABLE		(IEC0bits.INT2IE)
	#define ENC100_ISR_FLAG			(IFS0bits.INT2IF)
	#define ENC100_ISR_POLARITY		(INTCONbits.INT2EP)	
	#define ENC100_ISR_PRIORITY		(IPC2bits.INT2IP)	
	#define ENC100_SPI_ENABLE		(ENC100_SPICON1bits.ON)
	#define ENC100_SPI_IF			(IFS0bits.SPI1RXIF)
	#define ENC100_SSPBUF			(SPI1BUF)
	#define ENC100_SPICON1			(SPI1CON)
	#define ENC100_SPISTATbits		(SPI1STATbits)
	#define ENC100_SPICON1bits		(SPI1CONbits)
	#define ENC100_SPIBRG			(SPI1BRG)
#else
	#error "Problème configuration Ethernet dans HardwareProfile.h"
#endif


// LED, Boutons,... -------------------------------------------------------------------------------------
#if defined(ADT22) 
	// LED 1 (Carte PIC)
	#define LED1_TRIS	   	    (TRISEbits.TRISE2)
	#define LED1				(LATEbits.LATE2)
	
	// LED 2 (Bouton)
	#define LED2_TRIS			(TRISEbits.TRISE1)
	#define LED2				(LATEbits.LATE1)
	
	#define DEBUG_TRIS			(TRISAbits.TRISA14)
	#define DEBUG				(LATAbits.LATA14)
	#define DEBUG2_TRIS			(TRISAbits.TRISA15)
	#define DEBUG2				(LATAbits.LATA15)
	      
	// Boutons
	#define BOUTON_TRIS			(TRISCbits.TRISC3)
	#define	BOUTON				(PORTCbits.RC3)
	
	#define BP_EXT_TRIS			(TRISEbits.TRISE0)
	#define	BP_EXT				(PORTEbits.RE0)
		
	#define BUTTON3_IO			(PORTCbits.RC3) // pour tcpip
	
	// Entrée température
	#define TEMP_TRIS			(TRISBbits.TRISB6)
	#define	TEMP				(PORTBbits.RB6)
	
	// Relais
	// Voir dans divers.h quel relais est géré ou pas (par des GET)
	#define RELAIS1_TRIS		(TRISBbits.TRISB12)
	#define RELAIS1				(LATBbits.LATB12)
	#define RELAIS2_TRIS		(TRISBbits.TRISB13)
	#define RELAIS2				(LATBbits.LATB13)
	#define RELAIS3_TRIS		(TRISBbits.TRISB14)
	#define RELAIS3				(LATBbits.LATB14)		
	#define RELAIS4_TRIS		(TRISBbits.TRISB15)
	#define RELAIS4				(LATBbits.LATB15)
	
	// OPTOS
	#define OPTO1_TRIS			(TRISBbits.TRISB4)
	#define	OPTO1				(PORTBbits.RB4)
	#define OPTO2_TRIS			(TRISBbits.TRISB5)
	#define	OPTO2				(PORTBbits.RB5)
	
	// LCD
	#define LCD_EN_TRIS			(TRISCbits.TRISC14)		
	#define LCD_EN				(LATCbits.LATC14)
	
	#define LCD_RS_TRIS			(TRISCbits.TRISC13)		
	#define LCD_RS				(LATCbits.LATC13)
	
	#define LCD_CMD_AFF_TRIS	(TRISAbits.TRISA4)		
	#define LCD_CMD_AFF			(LATAbits.LATA4)
	
	// "pilot" J1772
	#define PILOT_IN_TRIS		(TRISDbits.TRISD4)
	#define PILOT_IN			(PORTDbits.RD4)	
	
	#define AC1_TRIS			(TRISFbits.TRISF1)
	#define AC1					(PORTFbits.RF1)	
	
	#define AC2_TRIS			(TRISGbits.TRISG15)
	#define AC2					(PORTGbits.RG15)	
	
	#define PILOT_TRIS		    (TRISFbits.TRISF0)
	#define PILOT			    (PORTFbits.RF0)	
	

#else
   #error "Definir une carte dans le fichier HardwareProfile.h"        
#endif

// SST25VF016  --------------------------------------------------------------------------------------------
#if defined(ADT22)
		#define USE_SST25VF016
		#define SST25_SPI_CHANNEL	 4
		#define SPI_CHANNEL_4_ENABLE
		#define SST25_CS_LAT		(LATFbits.LATF8)
		#define SST25_CS_TRIS	    (TRISFbits.TRISF8)

	#else
		#error "Hardware profile not defined ( SST016).  See available profiles in HardwareProfile.h and modify or create one."
	#endif
	
	// Ports I2C pour déblocage "manuel"
        
	#if defined(ADT212)
        #define SDA_Eeprom_TRIS           (TRISAbits.TRISA3)      // SDA2
        #define SDA_Eeprom                (PORTAbits.RA3)     
        #define SCL_Eeprom_TRIS           (TRISAbits.TRISA2)      // SCL2
        #define SCL_Eeprom                (LATAbits.LATA2)
    #endif

#endif



       