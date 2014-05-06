/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 * Nom:			MCP7941.C
 * Fonction :	GESTION DE L'HORLOGE MCP7941
 *
 *  SARL ADTEK
 **********************************************************************************************************
 * Author | Jean Arhainx  |  Date  19/03/2014   |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or
 * send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *********************************************************************************************************/

#include <plib.h> 
#include "0_SPARKBOX.h"
#include <time.h>
#include "divers.h"
#include "mcp7941.h"
#include "i2c.h"
#include "GenericTypeDefs.h"


// Définitions pour le Bus I2C
#define Frequence_MCP7941	100000  // 100 Khz
#define MODELE_MCP7941		79410

#if (defined ADT22)
	#define MCP7941_I2C_BUS		I2C2 	// 
#else
	#error Il faut definir une carte pour le MCP7941 !
#endif	
	

// INIT_I2C_MCP7941 --------------------------------------------------------------
void MCP7941_Init_I2c()
{
	I2CSetFrequency(MCP7941_I2C_BUS, GetPeripheralClock(), Frequence_MCP7941);
    I2CEnable(MCP7941_I2C_BUS, TRUE);
}

//***************************************************************************
// void Init_MCP7941()
//
//  Initialisation du MCP79410
//  Démarre l'oscillateur au besoin (avec initialisation : 2001,2,3 4h5m0s
//***************************************************************************
unsigned char MCP7941_Init()
{
	unsigned char day=0;   	
	
	// On vérifie que l'oscillateur fonctionne (OSCON bit). Attention pas de garantie fréquence
    day = MCP7941_Read(ADDR_DAY);   
	if((day&OSCON)!=OSCON)
	{
	 	// L'oscillateur ne fonctionnait pas. On met à jour arbitrairement l'heure et on démarre
	 	day = 0;
		day += MCP7941_Write(ADDR_DAY,day|VBATEN);		// On autorise l'utilisation de la batterie
		day += MCP7941_Write(ADDR_YEAR,0x01);       	// YEAR  register : (20)01         
		day += MCP7941_Write(ADDR_MNTH,1);   	    	//  MONTH register : Janvier
		day += MCP7941_Write(ADDR_DATE,1);   	    	//  DATE  register : jour 	
		day += MCP7941_Write(ADDR_HOUR,1);   	    	//  HOUR  register : heure 	
		day += MCP7941_Write(ADDR_MIN,1) ;   	    	//  MIN   register : minute	 
		day += MCP7941_Write(ADDR_CTRL,ALM_NO+OUT_PIN);	//  Pas d'alarmes et pas de pin de sortie
		day += MCP7941_Write(ADDR_SEC,START_32KHZ);		//  SEC   register : 0 sec et start 32khz oscillateur
		if (day == 0) // Programmation I2C ok!
		{
			Ajout_Ligne_Log("STRT: Raz + Démarrage Horloge RTC");
		}
		else
		{
			Ajout_Ligne_Log("STRT: Démarrage Horloge RTC - Vérifier I2C");
		}
		return(0);
	}
	else
	{
		return(1);
	}
}

//***************************************************************************
// unsigned char MCP7941_Write(unsigned char rtcc_reg, unsigned char time_var)
//
//  Ecriture d'un octet dans un registre du MCP79410
//  rtcc_reg = Adresse registre
//  time_var = octet à écrire
//  Retourne 0 si Ok, sinon retourne un code d'erreur (1,2,3)
//***************************************************************************
unsigned char MCP7941_Write(unsigned char rtcc_reg, unsigned char time_var)
{ 
	UINT8	i2cData[3];
    int     Index;
    int     DataSz;
    BOOL    Success = TRUE;

    i2cData[0] 	= ADDR_MCP7941_WRITE;
  	i2cData[1] 	= rtcc_reg;			
   	i2cData[2] 	= time_var;        	
    DataSz 		= 3; // 3 Octet au total
    
    if( !StartTransfer(MCP7941_I2C_BUS,FALSE) ) return 1;

    Index = 0;
    while( Success && (Index < DataSz) )
    {
        if (TransmitOneByte(MCP7941_I2C_BUS,i2cData[Index]))
        {
            Index++;
            if(!I2CByteWasAcknowledged(MCP7941_I2C_BUS))
            {
                return 2;
            }
        }
        else
        {
            return 3;
        }
    }
    StopTransfer(MCP7941_I2C_BUS);
    return 0;
}	

//***************************************************************************
// unsigned char MCP7941_Read(unsigned char rtcc_reg)
//
//  Lecture d'un octet d'un registre du MCP79410
//  rtcc_reg = Adresse registre
//***************************************************************************
unsigned char MCP7941_Read(unsigned char rtcc_reg)
{
	UINT8	i2cData[2];
    int     Index;
    int     DataSz;
    BOOL    Success = TRUE;
    UINT8   i2cbyte;
    
    i2cData[0] 	= ADDR_MCP7941_WRITE;
    i2cData[1] 	= (rtcc_reg);	
    DataSz		= 2;
    
    if( !StartTransfer(MCP7941_I2C_BUS,FALSE)) Success = FALSE;

    Index = 0;
    while( Success & (Index < DataSz) )
    {
        if (TransmitOneByte(MCP7941_I2C_BUS,i2cData[Index])) 
        	{ Index++;}
        else
        	{ Success = FALSE;}

        if(!I2CByteWasAcknowledged(MCP7941_I2C_BUS)) Success = FALSE;
    }

    if(Success)
    {
        if( !StartTransfer(MCP7941_I2C_BUS,TRUE) ) while(1); 

        if (TransmitOneByte(MCP7941_I2C_BUS,ADDR_MCP7941_READ))
        {
            if(!I2CByteWasAcknowledged(MCP7941_I2C_BUS)) Success = FALSE;
        }
        else
        {
            Success = FALSE;
        }
    }

    if(Success)
    {
        if(I2CReceiverEnable(MCP7941_I2C_BUS, TRUE) == I2C_RECEIVE_OVERFLOW)
        {
            Success = FALSE;
        }
        else
        {
            while(!I2CReceivedDataIsAvailable(MCP7941_I2C_BUS));
            i2cbyte = I2CGetByte(MCP7941_I2C_BUS);
        }

    }

    StopTransfer(MCP7941_I2C_BUS);
    
    return i2cbyte;
}


//***************************************************************************
// unsigned char MCP7941_Writelonglong(unsigned char rtcc_reg, longlong time_var)
//
//  Ecriture d'un octet dans un registre du MCP79410
//  rtcc_reg = Adresse registre
//  time_var = 64 bits à écrire
//  Retourne 0 si Ok, sinon retourne un code d'erreur (1,2,3)
//***************************************************************************
unsigned char MCP7941_WriteLongLong(unsigned char rtcc_reg, unsigned long long time_var)
{ 
	UINT8	i2cData[10];
    int     Index;
    int     DataSz;
    BOOL    Success = TRUE;

    i2cData[0] 	= ADDR_MCP7941_WRITE;
  	i2cData[1] 	= rtcc_reg;			
   	i2cData[9] 	= ((unsigned char)((time_var) & 0x00000000000000FF));
   	i2cData[8] 	= ((unsigned char)((time_var >> 8) & 0x00000000000000FF));     
   	i2cData[7] 	= ((unsigned char)((time_var >> 16) & 0x00000000000000FF)); 
   	i2cData[6] 	= ((unsigned char)((time_var >> 24) & 0x00000000000000FF));
   	i2cData[5] 	= ((unsigned char)((time_var >> 32) & 0x00000000000000FF));    
   	i2cData[4] 	= ((unsigned char)((time_var >> 40) & 0x00000000000000FF)); 
   	i2cData[3] 	= ((unsigned char)((time_var >> 48) & 0x00000000000000FF));
   	i2cData[2] 	= ((unsigned char)((time_var >> 56) & 0x00000000000000FF));


    DataSz 		= 10; // 3 Octet au total
    
    if( !StartTransfer(MCP7941_I2C_BUS,FALSE) ) return 1;

    Index = 0;
    while( Success && (Index < DataSz) )
    {
        if (TransmitOneByte(MCP7941_I2C_BUS,i2cData[Index]))
        {
            Index++;
            if(!I2CByteWasAcknowledged(MCP7941_I2C_BUS))
            {
                return 2;
            }
        }
        else
        {
            return 3;
        }
    }
    StopTransfer(MCP7941_I2C_BUS);
    return 0;
}

//***************************************************************************
// unsigned char MCP7941_ReadLongLong(unsigned char rtcc_reg)
//
//  Lecture d'un octet d'un registre du MCP79410
//  rtcc_reg = Adresse registre
//***************************************************************************
unsigned long long MCP7941_ReadLongLong(unsigned char rtcc_reg)
{
	UINT8			i2cData[8];
	unsigned char 	cpt;
	long long 		result;
	long long 		lltemp;
	
	for (cpt = 0; cpt < 8; cpt++)
	{
    	i2cData[cpt] = MCP7941_Read(rtcc_reg);
    	rtcc_reg++;
 	}
 	 
 	lltemp 	= i2cData[0]; result  = lltemp<<56;
 	lltemp 	= i2cData[1]; result += lltemp<<48;
 	lltemp 	= i2cData[2]; result += lltemp<<40;  
  	lltemp 	= i2cData[3]; result += lltemp<<32;   
 	lltemp 	= i2cData[4]; result += lltemp<<24;
 	lltemp 	= i2cData[5]; result += lltemp<<16;
 	lltemp 	= i2cData[6]; result += lltemp<<8;
 	lltemp 	= i2cData[7]; result += lltemp;
    return result;
}

//*********************************************************************************
//	unsigned char 	RTC_Ecris_An(unsigned short an);
//	unsigned short 	RTC_Lis_An(void);
//	unsigned char 	RTC_Ecris_Mois(unsigned char mois);
//	unsigned char 	RTC_Lis_Mois(void);
//	unsigned char 	RTC_Ecris_Jour(unsigned char jour);
//	unsigned char 	RTC_Lis_Jour(void);
//	unsigned char 	RTC_Ecris_Heure(unsigned char heure);
//	unsigned char 	RTC_Lis_Heure(void);
//	unsigned char 	RTC_Ecris_Minute(unsigned char min);
//	unsigned char 	RTC_Lis_Minute(void);
//	unsigned char 	RTC_Ecris_Seconde(unsigned char sec);
//	unsigned char 	RTC_Lis_Seconde(void);
//
//  Fonction d'écritures et lectures des registres de données
//  N'écris (et ne lis) que les bits nécéssaires
//
//  ATTENTION : Il est trés conseillé de désactiver l'horloge avant d'écrire l'heure
//
//**********************************************************************************
// AN -------------------------------------------------
unsigned char MCP7941_Ecris_An(unsigned short an)
{	// On ne garde que les dizaines et l'unité de an
	// On ne traite que si an <100 ou (an>1900 & an<2100 dans ce cas on enlève 200 au résultat)
	if ((an > 1999) && (an < 2100)) 
	{
		an = an - 2000;
	}
	else if (an > 100)
	{	// Erreur, on quitte
		return 9;
	}
	return MCP7941_Write(ADDR_YEAR,hex2BCD(an));
}

unsigned short MCP7941_Lis_An(void)
{
	return (BCD2hex(MCP7941_Read(ADDR_YEAR)) + 2000);
}

// MOIS -------------------------------------------
unsigned char MCP7941_Ecris_Mois(unsigned char mois)
{
	if (mois > 12)
	{	// Erreur, on quitte
		return 9;
	}
	return MCP7941_Write(ADDR_MNTH,hex2BCD(mois));
}
unsigned char MCP7941_Lis_Mois(void)
{
	return (BCD2hex(MCP7941_Read(ADDR_MNTH) & 0x1F));
}

// JOUR -------------------------------------------
unsigned char MCP7941_Ecris_Jour(unsigned char jour)
{
	if (jour > 31)
	{	// Erreur, on quitte
		return 9;
	}
	return MCP7941_Write(ADDR_DATE,hex2BCD(jour));
}
unsigned char MCP7941_Lis_Jour(void)
{
	return (BCD2hex(MCP7941_Read(ADDR_DATE) & 0x3F ));
}

// HEURE -------------------------------------------
unsigned char MCP7941_Ecris_Heure(unsigned char heure)
{
	if (heure > 59)
	{	// Erreur, on quitte
		return 9;
	}
	return MCP7941_Write(ADDR_HOUR,hex2BCD(heure));
}
unsigned char MCP7941_Lis_Heure(void)
{	// Au format 24h
	return (BCD2hex(MCP7941_Read(ADDR_HOUR) & 0x3F));
}

// MINUTE -------------------------------------------
unsigned char MCP7941_Ecris_Minute(unsigned char min)
{
	if (min > 59)
	{	// Erreur, on quitte
		return 9;
	}
	return MCP7941_Write(ADDR_MIN,hex2BCD(min));
}
unsigned char MCP7941_Lis_Minute(void)
{
	return (BCD2hex(MCP7941_Read(ADDR_MIN) & 0x7F));
}

// SECONDE -------------------------------------------
unsigned char MCP7941_Ecris_Seconde(unsigned char sec)
{
	if (sec > 59)
	{	// Erreur, on quitte
		return 9;
	}
	return MCP7941_Write(ADDR_SEC,hex2BCD(sec) | START_32KHZ);
}
unsigned char MCP7941_Lis_Seconde(void)
{
	return (BCD2hex(MCP7941_Read(ADDR_SEC) & 0x7F));
}

// HORLOGE
unsigned char MCP7941_Clock(unsigned char etat)
{
	unsigned char sec;
	sec = MCP7941_Read(ADDR_SEC) & 0x7F;
	if (etat == START)
	{
		MCP7941_Write(ADDR_SEC,sec + START_32KHZ);
	}
	else
	{
		MCP7941_Write(ADDR_SEC,sec);
	}
}

//***************************************************************************
// unsigned char MCP7941_Lis_UTC(STRUCT_DATE_ADTEK *tps)
//
//  Lecture de l'horloge du MCP79410 puis transformation en STRUCT_DATE_ADTEK
//***************************************************************************
unsigned char MCP7941_Lis_UTC(STRUCT_DATE_ADTEK *tps)
{
	struct tm tm1;
	
	tps->annee		= MCP7941_Lis_An();
	tps->mois		= MCP7941_Lis_Mois();
	tps->jour		= MCP7941_Lis_Jour();
	tps->heure		= MCP7941_Lis_Heure();
	tps->minute		= MCP7941_Lis_Minute();
	tps->seconde	= MCP7941_Lis_Seconde();

	tm1.tm_sec 		= (int)tps->seconde;
	tm1.tm_min		= (int)tps->minute;
	tm1.tm_hour 	= (int)tps->heure;
	tm1.tm_wday 	= 0;
	tm1.tm_yday 	= 0;
	tm1.tm_mday		= (int)tps->jour;
	tm1.tm_mon		= (int)tps->mois - 1;
	tm1.tm_year		= (int)(tps->annee - 1900);
	tps->utc  		= mktime(&tm1);
	tps->utc_fr		= tps->utc + (Sparkbox.Ecart_Gmt * 3600);
	return 1;
}