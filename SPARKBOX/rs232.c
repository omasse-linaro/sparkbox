/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 * Nom:			RS232.C
 * Fonction :	Gestion des 2 entrées RS232 Téléinfo
 *
 *  SARL ADTEK
 **********************************************************************************************************
 * Author | Jean Arhainx  |  Date  19/03/2014   |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or
 * send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *********************************************************************************************************/
#include "rs232.h"
#include "0_SPARKBOX.h"
#include "HardwareProfile.h"

unsigned int int_status_rs;


	// Téléinfo 1 
	volatile unsigned char Tele1rxbuffer[2][RS232_BUFFER_SIZE];                   // 2 buffer en flip flop
	volatile unsigned char Tele1rxready[2];                                       // nombre d'octets dans le buffer
	volatile unsigned char Tele1rxcurrent;                                        // buffer en cours de lecture, on écrit l'autre
	
	// Téléinfo 2 
	volatile unsigned char Tele2rxbuffer[2][RS232_BUFFER_SIZE];                   // 2 buffer en flip flop
	volatile unsigned char Tele2rxready[2];                                       // nombre d'octets dans le buffer
	volatile unsigned char Tele2rxcurrent;                                        // buffer en cours de lecture, on écrit l'autre

//				ADT22
// Tele1		U1B	
// Tele2		U3B

// 1200 bauds, 7 bits, parité paire, 1 stop
// Pic : pas de mode 7 bits
// On configure donc en 8 bits sans parité, 1 stop

void Initialisation_Rs232(void)
{	
    unsigned char i;
    unsigned char j;
    
    // Initialisation UART 1B 
	UARTConfigure ( UART1B, UART_ENABLE_PINS_TX_RX_ONLY );
	UARTSetFifoMode ( UART1B, UART_INTERRUPT_ON_RX_NOT_EMPTY );
    UARTSetLineControl ( UART1B, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1 );
    UARTSetDataRate ( UART1B, GetPeripheralClock(), 1200 );
    UARTEnable ( UART1B, UART_ENABLE_FLAGS ( UART_PERIPHERAL | UART_RX ) );

	IPC12bits.U1BIP = 0b11;		// IT priority level 3
	IPC12bits.U1BIS = 0b00;		// IT sub-priority level 0
    	
  	INTClearFlag ( INT_U1BRX );
	INTClearFlag ( INT_U1BE );  
  	
  	INTEnable(INT_U1BRX , INT_ENABLED);
    
    for ( i = 0; i < 2; i++)
    {
        for ( j = 0; j < RS232_BUFFER_SIZE; j++ )
        {
            Tele1rxbuffer[i][Tele1rxready[j++]] = 0;
		}
    }
    
	// Initialisation UART 3B
	UARTConfigure ( UART3B, UART_ENABLE_PINS_TX_RX_ONLY );
	UARTSetFifoMode ( UART3B, UART_INTERRUPT_ON_RX_NOT_EMPTY );
	UARTSetLineControl ( UART3B, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1 );
	UARTSetDataRate ( UART3B, GetPeripheralClock(), 1200 );
	UARTEnable ( UART3B, UART_ENABLE_FLAGS ( UART_PERIPHERAL | UART_RX ) );

	IPC12bits.U3BIP = 0b11;		// IT priority level 3
	IPC12bits.U3BIS = 0b00;		// IT sub-priority level 0

	INTClearFlag ( INT_U3BRX );
	INTClearFlag ( INT_U3BE );
	  	
	INTEnable(INT_U3BRX , INT_ENABLED);
    
    for ( i = 0; i < 2; i++)
    {
        for ( j = 0; j < RS232_BUFFER_SIZE; j++ )
        {
            Tele2rxbuffer[i][Tele2rxready[j++]] = 0;
		}
    }
}

/******************************************************************************
 * Function:        Tele1IsReadReady
 * Retourne le nombre d'octets disponibles dans le buffer en cours d'écriture !
 ******************************************************************************/
unsigned char Tele1IsReadReady(void)
{
	if ( IFS2bits.U1BEIF == 1 ) // INT ERROR
	{
		INTClearFlag( INT_U1BE ); // Effacement interruption
	}
	return Tele1rxready[Tele1rxcurrent^1];
}

/******************************************************************************
 * Function:        U3AIsReadReady
 * Retourne le nombre d'octets disponibles dans le buffer en cours d'écriture !
 ******************************************************************************/
unsigned char Tele2IsReadReady(void)
{
	return Tele2rxready[Tele2rxcurrent^1];
}

/******************************************************************************
 * Function:        UartIsReadReady
 * Retourne le nombre d'octets disponibles dans le buffer en cours d'écriture !
 ******************************************************************************/
unsigned char UartIsReadReady( unsigned char sel)
{
    unsigned char nbCar;
    
    switch ( sel )
    {
        case 0 :
            nbCar = Tele1IsReadReady();
            break;
            
        case 1 :
             nbCar = Tele2IsReadReady();
            break;
            
        default :
            nbCar = 0;
            break;
    }
    
    return nbCar;
}
 

/*********************************************************************
 * Function:        Tele1Read
 * Permutte les buffer puis
 * lit le nombre d'octets spécifié à concurence de Tele1rxready
 ********************************************************************/
unsigned char Tele1Read ( char * fromrs, unsigned char maxsize )
{
	unsigned char i;
    
	int_status_rs = INTDisableInterrupts();
 	Tele1rxcurrent ^= 1;                                   // Inversion des buffers
	INTRestoreInterrupts ( int_status_rs );
    
	if ( maxsize > Tele1rxready[Tele1rxcurrent] ) maxsize = Tele1rxready[Tele1rxcurrent];
	for ( i = 0; i < maxsize; i++ )
	{
		*fromrs++ = Tele1rxbuffer[Tele1rxcurrent][i];
	}	
	Tele1rxready[Tele1rxcurrent] = 0;
	return maxsize;	
}

/*********************************************************************
 * Function:        U3ARead
 * Permutte les buffer puis
 * lit le nombre d'octets spécifié à concurence de U3Arxready
 ********************************************************************/
unsigned char Tele2Read ( char * fromrs, unsigned char maxsize )
{
	unsigned char i;
    
	int_status_rs = INTDisableInterrupts();
 	Tele2rxcurrent ^= 1;                                   // Inversion des buffers
	INTRestoreInterrupts ( int_status_rs );
    
	if ( maxsize > Tele2rxready[Tele2rxcurrent] ) maxsize = Tele2rxready[Tele2rxcurrent];
	for ( i = 0; i < maxsize; i++ )
	{
		*fromrs++ = Tele2rxbuffer[Tele2rxcurrent][i];
	}	
	Tele2rxready[Tele2rxcurrent] = 0;
	return maxsize;	
}

/*********************************************************************
 * Function:        UartRead
 * Permutte les buffer puis
 * lit le nombre d'octets spécifié à concurence de Uxxrxready
 ********************************************************************/
unsigned char UartRead ( unsigned char sel, char * fromrs, unsigned char maxsize )
{

    switch ( sel )
    {
        case 0 :
            maxsize = Tele1Read ( fromrs, maxsize );
            break;
            
        case 1 :
            maxsize = Tele2Read ( fromrs, maxsize );
            break;
            
        default :
            maxsize = 0;
            break;
    }
    
    return maxsize;
 
}

 /*********************************************************************
 * Function:        _Tele1Interrupt
 * Réception uart 1B
 ********************************************************************/
void __ISR(_UART_1B_VECTOR, ipl3) __U1BInterrupt(void)
{
    unsigned char temp;
	// Réception
	if ( IFS2bits.U1BRXIF == 1 ) // INT RX
    {
		if ( Tele1rxready[Tele1rxcurrent^1] < RS232_BUFFER_SIZE ) // Si le buffer est disponible
		{
			Tele1rxbuffer[Tele1rxcurrent^1][Tele1rxready[Tele1rxcurrent^1]] = ( U1BRXREG & 0x7F );              // ajout du caractère reçu au buffer en cours d'écriture et on jette la parité
			Tele1rxready[Tele1rxcurrent^1]++;
		}
        else
        {
            temp = U1BRXREG;            // On purge en cas de débordement
            Nop();
        }
        INTClearFlag ( INT_U1BRX ); // Effacement interruption, cette ligne doit être après la lecture
	}
	// Erreur
	if ( IFS2bits.U1BEIF == 1 ) // INT ERROR
	{
		INTClearFlag(INT_U1BE); // Effacement interruption
	}
}

	 /*********************************************************************
	 * Function:        _U3BInterrupt
	 * Réception uart 3B
	 ********************************************************************/
	void __ISR(_UART_3B_VECTOR, ipl3) __U3AInterrupt(void)
	{
	    unsigned char temp;
		// Réception
		if ( IFS2bits.U3BRXIF == 1 ) // INT RX
	    {
			if ( Tele2rxready[Tele2rxcurrent^1] < RS232_BUFFER_SIZE ) // Si le buffer est disponible
			{
				Tele2rxbuffer[Tele2rxcurrent^1][Tele2rxready[Tele2rxcurrent^1]] = ( U3BRXREG & 0x7F );              // ajout du caractère reçu au buffer en cours d'écriture et on jette la parité
				Tele2rxready[Tele2rxcurrent^1]++;
			}
	        else
	        {
	            temp = U3BRXREG;            // On purge en cas de débordement
	            Nop();
	        }
	        INTClearFlag ( INT_U3BRX ); // Effacement interruption, cette ligne doit être après la lecture
		}
		// Erreur
		if ( IFS2bits.U3BEIF == 1 ) // INT ERROR
		{
			INTClearFlag(INT_U3BE); // Effacement interruption
		}
	}