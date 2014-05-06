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

#ifndef LCD_H
#define LCD_H

#define LCD_NB_LINE 2
#define LCD_NB_CHAR	16
	

static unsigned char adr_line[LCD_NB_LINE] = {0x00, 0x40};		// Adapter selon afficheur

void lcd_write(unsigned char);

/* Clear and home the LCD */

void lcd_clear(void);

void lcd_clear_line(unsigned char line);

void lcd_home(void);

/* write a string of characters to the LCD */

void lcd_puts(const char * s);

/* Go to the specified position */

void lcd_goto(unsigned char pos);

/* intialize the LCD - call before anything else */

void lcd_init(void);

void lcd_clear_line(unsigned char line);
void lcd_puts_line(unsigned char line, const char * s);

#endif
