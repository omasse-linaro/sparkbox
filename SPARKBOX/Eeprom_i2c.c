/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 * Nom:			EEPROM_IC2.C
 * Fonction :	Gestion EEProm
 *
 *  SARL ADTEK
 **********************************************************************************************************
 * Author | Jean Arhainx  |  Date  19/03/2014   |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or
 * send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *********************************************************************************************************/

//-------------------------------------------------------------------------------------------
//  24AA64   |    ( A1=A2=A3=0v)     |           EEPROM 64K bits 8 Ko    IC6 0x0000->0x2000 |
//-------------------------------------------------------------------------------------------
//  ________________________________________________________________________________________|
// |Start   |   Stop | Taille | Description                                                 |
// |--------|--------|--------|-------------------------------------------------------------|
// | 0x0000 |        | struct |  Réseau (AppConfig)                                         |
// |--------|--------|--------|-------------------------------------------------------------|
// | 0x0099 | 0x0099 |   1d   |  Parité Config Réseau                                       |
// |--------|--------|--------|-------------------------------------------------------------|
// | 0x0100 |        | struct |  Sauvegarde structure Sparkbox et autres (1177)Octet Max    |
// |--------|--------|--------|-------------------------------------------------------------|
// | 0x05FF | 0x05FF |   1d   |  Parité Sparkbox et autres                                  |
// |--------|--------|--------|-------------------------------------------------------------|
// |--------|--------|--------|-------------------------------------------------------------|
// | 0x1700 |        | struct |  Structure Mynetmemo     			                        |
// |--------|--------|--------|-------------------------------------------------------------|
// | 0x1799 | 0x1799 |   1d   |  Parité Mynetmemo         		                     	    |
// |--------|--------|--------|-------------------------------------------------------------|
// | 0x1800 |        | struct |  Structure User (password)			                        |
// |--------|--------|--------|-------------------------------------------------------------|
// | 0x1899 | 0x1899 |   1d   |  Parité Password			  				                |
// |--------|--------|--------|-------------------------------------------------------------|
// | 0x1900 | 0x1900 |   1d   |  Numéro de carte (5)ADT05, (7)ADT07, (18)ADT18 .....        |
// |--------|--------|--------|-------------------------------------------------------------|
// | 0x1901 | 0x1901 |   1d   |  Version de Carte V0, V1, ...				                |
// |--------|--------|--------|-------------------------------------------------------------|
// | 0x1902 | 0x1902 |   1d   |  Nombre de relais			  				                |
// |--------|--------|--------|-------------------------------------------------------------|
// | 0x1903 | 0x1903 |   1d   |  Fonction 0=SparkBox   ....	         			            |
// |________|________|________|_____________________________________________________________|
#include <plib.h> 
#include "TCPIP Stack/TCPIP.h"
#include "0_SPARKBOX.h"
#include <Eeprom_i2c.h>
#include "GenericTypeDefs.h"
#include "teleinfo.h"

// Adressage des mémoires
#define ADR_EEPROM_SYSTEME 		0x50	//0b1010000 Serial EEPROM address

#define ADR_TCPIP				0x0000
#define ADR_TCPIP_PARITE		0x0099
#define ADR_REGUL				0x0100
#define ADR_REGUL_PARITE		0x05FF
#define ADR_MYNETMEMO	     	0x1700
#define ADR_MYNETMEMO_PARITE	0x1799
#define ADR_USER	     		0x1800
#define ADR_USER_PARITE			0x1899

unsigned int erreur_eeprom_cpt1s;

// Variables globales I2C
//unsigned char i2cbyte;

// PRIMITIVES DE GESTION EEPROM --------------------------------------------------------------------------------------------
void Init_eeprom()
{ 
	I2CSetFrequency(EEPROM_I2C_BUS, GetPeripheralClock(), Frequence_EEPROM);
    I2CEnable(EEPROM_I2C_BUS, TRUE);
    erreur_eeprom_cpt1s = 0;
}

void i2c_wait(unsigned int cnt)
{
	while(--cnt)
	{
		Nop();
		Nop();
	}
}

void Ecrit_Octet_Eeprom(unsigned char Addresse_I2c,unsigned int Adresse_memoire,unsigned char Caractere)
{
    UINT8               i2cData[10];
    I2C_7_BIT_ADDRESS   SlaveAddress;
    int                 Index;
    int                 DataSz;
    BOOL                Acknowledged;
    BOOL                Success = TRUE;
    unsigned char 		Read_Caractere;

    Read_Caractere = Lit_Octet_Eeprom(Addresse_I2c, Adresse_memoire);
	// Inutile d"écrire si c'est déja le bon caractère
    if ( Read_Caractere != Caractere )
    {

	    // Initialize the data buffer
	    I2C_FORMAT_7_BIT_ADDRESS(SlaveAddress, Addresse_I2c, I2C_WRITE);
	    i2cData[0] = SlaveAddress.byte;
   		i2cData[1] = ((Adresse_memoire >> 8) & 0x00FF);	// EEPROM location to read (high address byte)
    	i2cData[2] = (Adresse_memoire & 0x00FF);        // EEPROM location to read (low address byte)
	    i2cData[3] = Caractere;              			// Data to write
	    DataSz = 4;
	    
	    // Start the transfer to write data to the EEPROM
	    if( !StartTransfer(EEPROM_I2C_BUS,FALSE) )
	    {
		    if ((cpt1s - erreur_eeprom_cpt1s) > 3600) 
		    {
		    	erreur_eeprom_cpt1s = cpt1s;
		    	Ajout_Ligne_Log("I2C : Erreur I2C sur Ecriture EEPROM (code=001)");
		    }
	       	return;
	    }
	
	    // Transmit all data
	    Index = 0;
	    while( Success && (Index < DataSz) )
	    {
	        // Transmit a byte
	        if (TransmitOneByte(EEPROM_I2C_BUS,i2cData[Index]))
	        {
	            // Advance to the next byte
	            Index++;
	
	            // Verify that the byte was acknowledged
	            if(!I2CByteWasAcknowledged(EEPROM_I2C_BUS))
	            {
	                Success = FALSE;
	            }
	        }
	        else
	        {
	            Success = FALSE;
	        }
	    }
	
	    // End the transfer (hang here if an error occured)
	    StopTransfer(EEPROM_I2C_BUS);
	    if(!Success)
	    {
	        if ((cpt1s - erreur_eeprom_cpt1s) > 3600) 
		    {
		    	erreur_eeprom_cpt1s = cpt1s;
		    	Ajout_Ligne_Log("I2C : Erreur I2C sur Ecriture EEPROM (code=002)");
		    }
	       	return;
	    }
	
	
	    // Wait for EEPROM to complete write process, by polling the ack status.
	    Acknowledged = FALSE;
	    do
	    {
	        // Start the transfer to address the EEPROM
	        if( !StartTransfer(EEPROM_I2C_BUS,FALSE) )
	        {
	           if ((cpt1s - erreur_eeprom_cpt1s) > 3600) 
			    {
			    	erreur_eeprom_cpt1s = cpt1s;
			    	Ajout_Ligne_Log("I2C : Erreur I2C sur Ecriture EEPROM (code=003)");
			    }
	       		return;
	        }
	        
	        // Transmit just the EEPROM's address
	        if (TransmitOneByte(EEPROM_I2C_BUS,SlaveAddress.byte))
	        {
	            // Check to see if the byte was acknowledged
	            Acknowledged = I2CByteWasAcknowledged(EEPROM_I2C_BUS);
	        }
	        else
	        {
	            Success = FALSE;
	        }
	
	        // End the transfer (stop here if an error occured)
	        StopTransfer(EEPROM_I2C_BUS);
	    } while (Acknowledged != TRUE);
	}


}

unsigned char Lit_Octet_Eeprom(unsigned char Addresse_I2c,unsigned int Adresse_memoire)
{
	UINT8               i2cData[10];
    I2C_7_BIT_ADDRESS   SlaveAddress;
    int                 Index;
    int                 DataSz;
    BOOL                Success = TRUE;
    UINT8               i2cbyte;
    
    // Initialize the data buffer
    I2C_FORMAT_7_BIT_ADDRESS(SlaveAddress, Addresse_I2c, I2C_WRITE);
    i2cData[0] = SlaveAddress.byte;
    i2cData[1] = ((Adresse_memoire >> 8) & 0x00FF);	// EEPROM location to read (high address byte)
    i2cData[2] = (Adresse_memoire & 0x00FF);        // EEPROM location to read (low address byte)
    DataSz = 3;
    
    // Start the transfer to read the EEPROM.
    if( !StartTransfer(EEPROM_I2C_BUS,FALSE) )
    {
        if ((cpt1s - erreur_eeprom_cpt1s) > 3600) 
	    {
	    	erreur_eeprom_cpt1s = cpt1s;
	    	Ajout_Ligne_Log("IEC : Erreur I2C sur Lecture EEPROM (code=004)");
	    }
       	return;
    }
    
    // Address the EEPROM.
    Index = 0;
    while( Success & (Index < DataSz) )
    {
        // Transmit a byte
        if (TransmitOneByte(EEPROM_I2C_BUS,i2cData[Index])) 	Index++;
        else													Success = FALSE;
        
        // Verify that the byte was acknowledged
        if(!I2CByteWasAcknowledged(EEPROM_I2C_BUS)) Success = FALSE;
    }

    // Restart and send the EEPROM's internal address to switch to a read transfer
    if(Success)
    {
        // Send a Repeated Started condition
        if( !StartTransfer(EEPROM_I2C_BUS,TRUE) ) 
        {
        	if ((cpt1s - erreur_eeprom_cpt1s) > 3600) 
		    {
		    	erreur_eeprom_cpt1s = cpt1s;
		    	Ajout_Ligne_Log("I2C : Erreur I2C sur Lecture EEPROM (code=005)");
		    }
	       	return;
        } 

        // Transmit the address with the READ bit set
        I2C_FORMAT_7_BIT_ADDRESS(SlaveAddress, Addresse_I2c, I2C_READ);
        if (TransmitOneByte(EEPROM_I2C_BUS,SlaveAddress.byte))
        {
            // Verify that the byte was acknowledged
            if(!I2CByteWasAcknowledged(EEPROM_I2C_BUS)) Success = FALSE;
        }
        else
        {
            Success = FALSE;
        }
    }

    // Read the data from the desired address
    if(Success)
    {
        if(I2CReceiverEnable(EEPROM_I2C_BUS, TRUE) == I2C_RECEIVE_OVERFLOW)
        {
            Success = FALSE;
        }
        else
        {
            while(!I2CReceivedDataIsAvailable(EEPROM_I2C_BUS));
            i2cbyte = I2CGetByte(EEPROM_I2C_BUS);
        }

    }

    // End the transfer (stop here if an error occured)
    StopTransfer(EEPROM_I2C_BUS);
    
    return i2cbyte;
}




// GESTION EEPROM RESEAU ----------------------------------------------------------------------------------------
void Eeprom_Ecriture_IP(APP_CONFIG Ip)
{
	unsigned int pos;
	unsigned int i;
	unsigned char *p;
	unsigned char parite;
	
	parite = 0;
	pos = ADR_TCPIP;
	p = (unsigned char *)&Ip;
	for ( i = 0; i < sizeof(APP_CONFIG); i++ )
    {
	    Ecrit_Octet_Eeprom(ADR_EEPROM_SYSTEME, pos,*p);
	    parite = parite ^ *p;
		pos++;
		p++;
    }
	Ecrit_Octet_Eeprom(ADR_EEPROM_SYSTEME, ADR_TCPIP_PARITE, parite);
}



unsigned char  Eeprom_Lecture_IP(APP_CONFIG *Config)
{
	unsigned int 	pos;
	unsigned int 	i;
	unsigned char 	*p;
	unsigned char 	car;
	unsigned char 	parite;
	unsigned char 	parite_ee;
	APP_CONFIG 		Config_Lue;

	pos = ADR_TCPIP;

	p = (unsigned char *)&Config_Lue;


	parite = 0;
	for ( i = 0; i < sizeof(*Config); i++ )
   	{
	    car = Lit_Octet_Eeprom(ADR_EEPROM_SYSTEME, pos);
		*p= car;
		parite = parite ^ car;
		pos++;
		p++;
  	}
	parite_ee = Lit_Octet_Eeprom(ADR_EEPROM_SYSTEME, ADR_TCPIP_PARITE);
	
	// Load the default NetBIOS Host Name
	memcpypgm2ram(Config->NetBIOSName, (ROM void*)MY_DEFAULT_HOST_NAME, 16);
	FormatNetBIOSName(AppConfig.NetBIOSName);
	Config->Flags.bInConfigMode = TRUE;
	
	if (parite_ee == parite)
   	{
	   	// Parité OK, on recopie les paramètres TCP/IP SAUF ADRESSE MAC
	   	Config->MyIPAddr.Val 			= Config_Lue.MyIPAddr.Val;
		Config->MyMask.Val 				= Config_Lue.MyMask.Val ;
		Config->MyGateway.Val 			= Config_Lue.MyGateway.Val;
		Config->PrimaryDNSServer.Val 	= Config_Lue.PrimaryDNSServer.Val;
		Config->SecondaryDNSServer.Val 	= Config_Lue.SecondaryDNSServer.Val;
		Config->Flags.bIsDHCPEnabled 	= Config_Lue.Flags.bIsDHCPEnabled;
		if ((Config->MyMACAddr.v[0] == 0x00) && (Config->MyMACAddr.v[1] == 0x00) && (Config->MyMACAddr.v[2] == 0x00) && 
		(Config->MyMACAddr.v[3] == 0x00) && (Config->MyMACAddr.v[4] == 0x00) && (Config->MyMACAddr.v[5] == 0x00))
		{	// L'adresse MAC est vierge ! On y met celle par défaut	lue dans le pic 32 par MacInit
			memcpypgm2ram(Config->MyMACAddr.v, SerializedMACAddress, sizeof(AppConfig.MyMACAddr));
		}	
		// Sinon l'adresse MAC a du déjà être mise dans la structure par StackInit.
    	return 1;
   	}
   	else
   	{	// Mauvaise Parité, on recharge les paramètres par défaut	
		Eeprom_RAZ_IP(Config);
		return 0;
   	}
}

void Eeprom_RAZ_IP(APP_CONFIG *Config)
{
 	Config->MyIPAddr.Val = MY_DEFAULT_IP_ADDR_BYTE1 | MY_DEFAULT_IP_ADDR_BYTE2<<8ul | MY_DEFAULT_IP_ADDR_BYTE3<<16ul | MY_DEFAULT_IP_ADDR_BYTE4<<24ul;
 	Config->MyMask.Val = MY_DEFAULT_MASK_BYTE1 | MY_DEFAULT_MASK_BYTE2<<8ul | MY_DEFAULT_MASK_BYTE3<<16ul | MY_DEFAULT_MASK_BYTE4<<24ul;
 	Config->MyGateway.Val = MY_DEFAULT_GATE_BYTE1 | MY_DEFAULT_GATE_BYTE2<<8ul | MY_DEFAULT_GATE_BYTE3<<16ul | MY_DEFAULT_GATE_BYTE4<<24ul;
 	  	// Serveurs DNS
 	Config->PrimaryDNSServer.Val = MY_DEFAULT_PRIMARY_DNS_BYTE1 | MY_DEFAULT_PRIMARY_DNS_BYTE2<<8ul  | MY_DEFAULT_PRIMARY_DNS_BYTE3<<16ul  | MY_DEFAULT_PRIMARY_DNS_BYTE4<<24ul;
	Config->SecondaryDNSServer.Val = MY_DEFAULT_SECONDARY_DNS_BYTE1 | MY_DEFAULT_SECONDARY_DNS_BYTE2<<8ul  | MY_DEFAULT_SECONDARY_DNS_BYTE3<<16ul  | MY_DEFAULT_SECONDARY_DNS_BYTE4<<24ul;

	// Load the default NetBIOS Host Name
	memcpypgm2ram(Config->NetBIOSName, (ROM void*)MY_DEFAULT_HOST_NAME, 16);
	FormatNetBIOSName(AppConfig.NetBIOSName);

	

	#if defined(RAZ_IP_STATIQUE)
		Config->Flags.bIsDHCPEnabled = FALSE; // IP STATIQUE
	#else
		Config->Flags.bIsDHCPEnabled = TRUE; // DHCP
	#endif	
 	Config->Flags.bInConfigMode = TRUE;
 	
 	// Adresse MAC
	if ((Config->MyMACAddr.v[0] == 0x00) && (Config->MyMACAddr.v[1] == 0x00) && (Config->MyMACAddr.v[2] == 0x00) && 
	(Config->MyMACAddr.v[3] == 0x00) && (Config->MyMACAddr.v[4] == 0x00) && (Config->MyMACAddr.v[5] == 0x00))
	{	// L'adresse MAC est vierge ! On y met celle par défaut	
		memcpypgm2ram((void*)&AppConfig.MyMACAddr, (ROM void*)SerializedMACAddress, sizeof(AppConfig.MyMACAddr));
	//	memcpypgm2ram((void*)&Config.MyMACAddr, (ROM void*)SerializedMACAddress, sizeof(AppConfig.MyMACAddr));
	}	
	// Sinon l'adresse MAC a du déjà être mise dans la structure par StackInit.
 	Eeprom_Ecriture_IP(*Config);
 	
}


//********************************************************************************************************************
//--------------------------------------------------------------------------------------------------------------------
//  EEPROM UTILISATEUR
//--------------------------------------------------------------------------------------------------------------------
//********************************************************************************************************************

/***************************************************
****************************************************/
// régulation, onewire et autres parmètres utilisateur
void Eeprom_Ecriture_Regul(STRUCT_SPARKBOX regul)
{
	unsigned int pos;
	unsigned int i;
	unsigned char *p;
	unsigned char parite;
	
	parite = 0;
	pos = ADR_REGUL;
	p = (unsigned char *)&regul;
	for ( i = 0; i < sizeof(STRUCT_SPARKBOX); i++ )
    {
	    Ecrit_Octet_Eeprom(ADR_EEPROM_SYSTEME, pos,*p);
	    parite = parite ^ *p;
		pos++;
		p++;
    }
	Ecrit_Octet_Eeprom(ADR_EEPROM_SYSTEME, ADR_REGUL_PARITE, parite);
}

unsigned char Eeprom_Lecture_Regul(STRUCT_SPARKBOX *regul)
{
	unsigned int pos;
	unsigned int i;
	unsigned char *p;
	unsigned char car;
	unsigned char parite;
	unsigned char parite_ee;
	unsigned char cpt_i2c;

	pos = ADR_REGUL;

	p = (unsigned char *) regul;
	parite = 0;
	for ( i = 0; i < sizeof(*regul); i++ )
	{
		car = Lit_Octet_Eeprom(ADR_EEPROM_SYSTEME, pos);
		*p= car;
		parite = parite ^ car;
		pos++;
		p++;
	}
	parite_ee = Lit_Octet_Eeprom(ADR_EEPROM_SYSTEME, ADR_REGUL_PARITE);
   if (parite_ee == parite)
   {
		// RAZ des CAPTEURS .. au cas ou ! (Correction problème 0.2c)
		for (cpt_i2c = 0; cpt_i2c < NB_MAX_CAPTEURS; cpt_i2c++)
		{
			regul->Capteur[cpt_i2c].Etat		= CAPTEUR_AUCUN;
			regul->Capteur[cpt_i2c].No			= 0;
			regul->Capteur[cpt_i2c].Type		= AUCUN;
			regul->Capteur[cpt_i2c].Id[0]		= 0x00;
			regul->Capteur[cpt_i2c].Temperature	= 0;
			regul->Capteur[cpt_i2c].Temperature_s[0] = 0x00;
		}

		// FIXE 			25 car max   "                         "
		strcpy(regul->Capteur[0].Nom, "TELE1: IINST");
		strcpy(regul->Capteur[1].Nom, "TEMPERATURE");
		strcpy(regul->Capteur[2].Nom, "ETAT PILOT");
		strcpy(regul->Capteur[3].Nom, "COURANT");
		strcpy(regul->Capteur[4].Nom, "GFCI");
		strcpy(regul->Capteur[5].Nom, "TELE1: PUISSANCE");
		strcpy(regul->Capteur[6].Nom, "TELE1: INDEX");
		strcpy(regul->Capteur[7].Nom, "TELE2: IINST");
		strcpy(regul->Capteur[8].Nom, "TELE2: PUISSANCE");
		strcpy(regul->Capteur[9].Nom, "TELE2: IINST");
		strcpy(regul->Capteur[10].Nom,"RESERVE");
		strcpy(regul->Capteur[11].Nom,"RESERVE");
		strcpy(regul->Capteur[12].Nom,"RESERVE");
		strcpy(regul->Capteur[13].Nom,"RESERVE");
		strcpy(regul->Capteur[14].Nom,"RESERVE");
		strcpy(regul->Capteur[15].Nom,"RESERVE");
    	return 1;
   }
   return(0);
}


void Eeprom_Raz_Regul(STRUCT_SPARKBOX *regul)
{
	unsigned char cpt_i2c;
	
	// EVSE
	regul->Max_Amp = 30;
	regul->Amp = 16;
	regul->Diode = 1;
	regul->Gfci = 30;
	regul->Amp_Reduit1 = 10;
	regul->Amp_Reduit2 = 8;
	regul->Collage_Relais = 0;			// Test de collage de relais
	regul->Lcd = 1;						// LCD Interne
	regul->Coef_Gfci = 450;				// 450 * 4.5
	regul->Delestage_Teleinfo	= NON;	// Pas de délestage piloté par tele1
	regul->Reserve_Teleinfo	= 0;		// Reserve en ampérage à conserver avant délestage
	regul->Arret_Sur_Baisse = NON;		// Arrêt de la charge sur baisse de l'intensité  = NON par défaut

    // Monitoring
    regul->Type_Monitoring 	= MONITORING_AUCUN;

 	strcpy(regul->Xpl_Name,"");
 	regul->Xpl_Intervalle	= 1; // 1 minute
 	regul->Xpl_Fonction		= XPL;
	
	// RAZ des CAPTEURS			    
    for (cpt_i2c = 0; cpt_i2c < NB_MAX_CAPTEURS; cpt_i2c++)
    {
    	regul->Capteur[cpt_i2c].Etat		= CAPTEUR_AUCUN;
    	regul->Capteur[cpt_i2c].No			= 0;
    	regul->Capteur[cpt_i2c].Type		= AUCUN;
    	regul->Capteur[cpt_i2c].Id[0]		= 0x00; 	
    	regul->Capteur[cpt_i2c].Temperature	= 0;
    	regul->Capteur[cpt_i2c].Temperature_s[0] = 0x00;
    }

    // FIXE 			25 car max   "                         "
    strcpy(regul->Capteur[0].Nom, "TELE1: IINST");
    strcpy(regul->Capteur[1].Nom, "TEMPERATURE");
    strcpy(regul->Capteur[2].Nom, "ETAT PILOT");
    strcpy(regul->Capteur[3].Nom, "COURANT");
    strcpy(regul->Capteur[4].Nom, "GFCI");
    strcpy(regul->Capteur[5].Nom, "TELE1: PUISSANCE");
    strcpy(regul->Capteur[6].Nom, "TELE1: INDEX");
    strcpy(regul->Capteur[7].Nom, "TELE2: IINST");
    strcpy(regul->Capteur[8].Nom, "TELE2: PUISSANCE");
    strcpy(regul->Capteur[9].Nom, "TELE2: IINST");
    strcpy(regul->Capteur[10].Nom,"RESERVE");
    strcpy(regul->Capteur[11].Nom,"RESERVE");
    strcpy(regul->Capteur[12].Nom,"RESERVE");
    strcpy(regul->Capteur[13].Nom,"RESERVE");
    strcpy(regul->Capteur[14].Nom,"RESERVE");
    strcpy(regul->Capteur[15].Nom,"RESERVE");

    regul->Type_Menu 			= MENU_NORMAL;	
    regul->Type_Email			= EMAIL_RECAP_NONE;
    
    Eeprom_Ecriture_Regul(*regul);
}
void Controle_Coherence_Regul(void)
{
	if (Sparkbox.Debug > DEBUG_MAX)
	{
		Sparkbox.Debug = DEBUG_NONE;
	}
}
//********************************************************************************************************************
//--------------------------------------------------------------------------------------------------------------------
//  USER
//--------------------------------------------------------------------------------------------------------------------
//********************************************************************************************************************
void Eeprom_Ecriture_User(STRUCT_USER user)
{
	unsigned int pos;
	unsigned int i;
	unsigned char *p;
	unsigned char parite;
	
	parite = 0;
	pos = ADR_USER;
	p = (unsigned char *)&user;
	for ( i = 0; i < sizeof(STRUCT_USER); i++ )
    {
	    Ecrit_Octet_Eeprom(ADR_EEPROM_SYSTEME,pos,*p);
	    parite = parite ^ *p;
		pos++;
		p++;
    }
	Ecrit_Octet_Eeprom(ADR_EEPROM_SYSTEME,ADR_USER_PARITE,parite);
}

unsigned char Eeprom_Lecture_User(STRUCT_USER *user)
{
	unsigned int pos;
	unsigned int i;
	unsigned char *p;
	unsigned char car;
	unsigned char parite;
	unsigned char parite_ee;
	
	pos = ADR_USER;
	p = (unsigned char *) user;
	parite = 0;
	for ( i = 0; i < sizeof(*user); i++ )
    {
	    car = Lit_Octet_Eeprom(ADR_EEPROM_SYSTEME,pos);
		*p= car;
		parite = parite ^ car;
		pos++;
		p++;
    }
	parite_ee = Lit_Octet_Eeprom(ADR_EEPROM_SYSTEME,ADR_USER_PARITE);
    if (parite_ee == parite)
    {
    	return 1;
    }
    return(0);
}


void Eeprom_Raz_User(STRUCT_USER *user)
{
	strcpy(&user->Login[0],"admin");
	strcpy(&user->Password[0],"admin");
	Eeprom_Ecriture_User(*user);
}



//********************************************************************************************************************
//--------------------------------------------------------------------------------------------------------------------
//  MYNETMEMO
//--------------------------------------------------------------------------------------------------------------------
//********************************************************************************************************************
void Eeprom_Ecriture_Mynetmemo(STRUCT_MYNETMEMO monitoring)
{
	unsigned int pos;
	unsigned int i;
	unsigned char *p;
	unsigned char parite;
	
	parite = 0;
	pos = ADR_MYNETMEMO;
	p = (unsigned char *)&monitoring;
	for ( i = 0; i < sizeof(STRUCT_MYNETMEMO); i++ )
    {
	    Ecrit_Octet_Eeprom(ADR_EEPROM_SYSTEME,pos,*p);
	    parite = parite ^ *p;
		pos++;
		p++;
    }
	Ecrit_Octet_Eeprom(ADR_EEPROM_SYSTEME,ADR_MYNETMEMO_PARITE,parite);
}

unsigned char Eeprom_Lecture_Mynetmemo(STRUCT_MYNETMEMO *monitoring)
{
	unsigned int pos;
	unsigned int i;
	unsigned char *p;
	unsigned char car;
	unsigned char parite;
	unsigned char parite_ee;
	
	pos = ADR_MYNETMEMO;
	p = (unsigned char *) monitoring;
	parite = 0;
	for ( i = 0; i < sizeof(*monitoring); i++ )
    {
	    car = Lit_Octet_Eeprom(ADR_EEPROM_SYSTEME,pos);
		*p= car;
		parite = parite ^ car;
		pos++;
		p++;
    }
	parite_ee = Lit_Octet_Eeprom(ADR_EEPROM_SYSTEME,ADR_MYNETMEMO_PARITE);
    if (parite_ee == parite)
    {
    	return 1;
    }
    return(0);
}


void Eeprom_Raz_Mynetmemo(STRUCT_MYNETMEMO *monitoring)
{
	int i;
	
	strcpy(&monitoring->ServerName[0],"mynetmemo.com");
	monitoring->ServerPort = 80;
	strcpy(&monitoring->Login[0],"");
	strcpy(&monitoring->Password[0],"");	
	for (i=0;i<NB_MAX_CAPTEURS;i++)
	{
		monitoring->ID_Mynetmemo[i] = 0; // Aucun envois paramétrés
	}
	
	
   Eeprom_Ecriture_Mynetmemo(*monitoring);
}


// Zone de configuration hardware ----------------------------------------------
// Permet de connaitre l'architecture de la carte
// Zones définies au début de ce source et qui commence à 0x1900

void Eeprom_Ecriture_Config(unsigned short adresse, unsigned char valeur)
{
	Ecrit_Octet_Eeprom(ADR_EEPROM_SYSTEME,adresse,valeur);
}

unsigned char Eeprom_Lecture_Config(unsigned short adresse)
{
	return(Lit_Octet_Eeprom(ADR_EEPROM_SYSTEME,adresse));
}



