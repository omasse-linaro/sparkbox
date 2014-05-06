/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 * Nom:			i2c.c
 * Fonction :	Primitives I2C
 *
 *  SARL ADTEK
 **********************************************************************************************************
 * Author | Jean Arhainx  |  Date  19/03/2014   |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or
 * send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *********************************************************************************************************/

#include <p32xxxx.h>               
#include <plib.h>						
#include "0_SPARKBOX.h"
#include "HardwareProfile.h"		
#include "i2c.h"
#include "TCPIP Stack/TCPIP.h" // Pour DelayMs

// misc constants
#define POLL_LIMIT  200
#define TRUE    1
#define FALSE   0

#define ACK     TRUE
#define NACK    FALSE

// Prototypes fonctions
BOOL I2CAckHasCompleted( I2C_MODULE id );

BOOL StartTransfer( I2C_MODULE i2cBus, BOOL restart )
{
    I2C_STATUS  status;
    unsigned int compteur = 0;
    
    #define LIMIT 10000

    // Send the Start (or Restart) signal
    if(restart)
    {
        I2CRepeatStart(i2cBus);
    }
    else
    {
        // Wait for the bus to be idle, then start the transfer
        compteur = 0;
        do
        {      
            compteur++;
        } while( !I2CBusIsIdle(i2cBus) && (compteur < LIMIT) );
        
        if ( compteur == LIMIT )
        {
            Nop();
        }

        if(I2CStart(i2cBus) != I2C_SUCCESS)
        {
            //Bus collision during transfer Start
            return FALSE;
        }
    }

    // Wait for the signal to complete
    compteur = 0;
    do
    {
        status = I2CGetStatus(i2cBus);
        compteur++;

    } while ( !(status & I2C_START)  && (compteur < LIMIT) ); // TODO, point bloquant Jean constaté le 1/12/2010 et le 28/03/2011

    if ( compteur == LIMIT )
	{
		Nop();
	}
    
    return TRUE;
}

/*******************************************************************************
  Function:
    BOOL TransmitOneByte( UINT8 data )

  Summary:
    This transmits one byte to the DS2482.

  Description:
    This transmits one byte to the DS2482, and reports errors for any bus
    collisions.

  Precondition:
    The transfer must have been previously started.

  Parameters:
    data    - Data byte to transmit

  Returns:
    TRUE    - Data was sent successfully
    FALSE   - A bus collision occured

  Example:
    <code>
    TransmitOneByte(0xAA);
    </code>

  Remarks:
    This is a blocking routine that waits for the transmission to complete.
  *****************************************************************************/

BOOL TransmitOneByte( I2C_MODULE i2cBus, UINT8 data )
{
    unsigned int compteur = 0;
    
    #define LIMIT 10000
    
    // Wait for the transmitter to be ready
    do
    {
        compteur++;
    } while(!I2CTransmitterIsReady(i2cBus) && (compteur < LIMIT) );
    
    if ( compteur == LIMIT )
	{
		Nop();
		return FALSE;
	}

    // Transmit the byte
    if(I2CSendByte(i2cBus, data) == I2C_MASTER_BUS_COLLISION)
    {
        // I2C Master Bus Collision
        return FALSE;
    }

    // Wait for the transmission to finish
    compteur = 0;
    do
    {
        compteur++;
    } while( !I2CTransmissionHasCompleted(i2cBus) && (compteur < LIMIT) );
    
    if ( compteur == LIMIT )
	{
		Nop();
		return FALSE;
	}

    return TRUE;
}

/*******************************************************************************
  Function:
    void StopTransfer( void )

  Summary:
    Stops a transfer to/from the CIRCUIT.

  Description:
    This routine Stops a transfer to/from the DS2482, waiting (in a 
    blocking loop) until the Stop condition has completed.

  Precondition:
    The I2C module must have been initialized & a transfer started.

  Parameters:
    None.
    
  Returns:
    None.
    
  Example:
    <code>
    StopTransfer();
    </code>

  Remarks:
    This is a blocking routine that waits for the Stop signal to complete.
  *****************************************************************************/
  
void StopTransfer( I2C_MODULE i2cBus )
{
    I2C_STATUS  status;
    unsigned int compteur = 0;

	#define LIMIT 10000

    // Send the Stop signal
    I2CStop(i2cBus);

    // Wait for the signal to complete
    do
    {
        status = I2CGetStatus(i2cBus);
		compteur++;

    } while ( !(status & I2C_STOP) && (compteur < LIMIT) );

	if ( compteur == LIMIT )
	{
		Nop();
	}
}



 
 /*******************************************************************************
  Function:
    BOOL I2CAckHasCompleted( I2C_MODULE id )
    
    Fonction correctrice !
    
  *****************************************************************************/
/*
BOOL I2CAckHasCompleted ( I2C_MODULE id )
{
	I2C_REGISTERS * const i2cRegisters = i2cBase[id];

	return( !(i2cRegisters->I2CxSTAT & 0x1F) );
}
*/
/*******************************************************************************
 *
 * Adaptation des fonctions de la note d'application Maxim vers la librairie
 * Microchip
 *
 *
 ******************************************************************************/

// Fonction identique
//I2CByteWasAcknowledged(I2C_MODULE i2cBus)


BYTE mI2CGetByte(I2C_MODULE i2cBus, BOOL ackNack)
{
    BYTE status = 0;
    
    // Version sur registres directement
    /*
    if ( I2C2STATbits.I2COV )
    {
        I2C2STATbits.I2COV = 0;
        // Erreur : I2C receive overflow
        // En cas d'erreur, on retourne 0, ce qui n'est pas idéal
        return status;
    }
    else
    {
        I2C2CONbits.RCEN = 1; // start read process
        while( !I2C2STATbits.RBF );

        status = I2C2RCV;
        
        if ( ackNack == ACK )
        {
            I2C2CONbits.ACKDT = 0;
            I2C2CONbits.ACKEN = 1;
        }
        else
        {
            I2C2CONbits.ACKDT = 1;
            I2C2CONbits.ACKEN = 1;
        }
        while ( I2C2CON & 0x1F );               // Ligne très importante !
    }
    */
    
    // Version sur librairie
    
    if(I2CReceiverEnable(i2cBus, TRUE) == I2C_RECEIVE_OVERFLOW)
    {
        // Erreur : I2C receive overflow
        // En cas d'erreur, on retourne 0, ce qui n'est pas idéal
        return status;
    }
    else
    { 
        while( !I2CReceivedDataIsAvailable(i2cBus) );

        status = I2CGetByte(i2cBus);
        
        I2CAcknowledgeByte(i2cBus, ackNack);       // ACK ou NAK selon que les lectures vont continuer ou non
        
        //while ( !I2CAckHasCompleted (i2cBus) );
        while ( I2C2CON & 0x1F );                                   // Ne pas oublier de changer selon le port utilisé
    }
    
    return status;
    
}


