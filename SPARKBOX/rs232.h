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
#ifndef RS232_H
	#define RS232_H	
	#include <Compiler.h>
	
	#define RS232_BUFFER_SIZE 	64	
	
	void Initialisation_Rs232 ( void );
    
    unsigned char U1BIsReadReady(void);
    unsigned char U3AIsReadReady(void);
    unsigned char UartIsReadReady( unsigned char sel);
    
	unsigned char U1BRead ( char * fromrs, unsigned char maxsize );
    unsigned char U3ARead ( char * fromrs, unsigned char maxsize );
    unsigned char UartRead ( unsigned char sel, char * fromrs, unsigned char maxsize );
    

#endif 

