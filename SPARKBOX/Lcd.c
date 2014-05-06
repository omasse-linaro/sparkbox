
 
#include <plib.h> 
#include <0_SPARKBOX.h>
#include "GenericTypeDefs.h"
#include "Lcd.h"


void LCD_STROBE(void)
{
    Delay10us(4);
    LCD_EN = 1;
    Delay10us(4);
    LCD_EN = 0;
    Delay10us(4);
}

/* Ecriture d'un octet en mode 4 bits */
void lcd_write(unsigned char c)
{
    static unsigned int masque;
    static unsigned int pe;

    masque = c & 0xF0;
    pe = LATE;
    LATE =   (pe & 0x0F) | masque;
    LCD_STROBE();
    masque = (( c << 4 ) & 0xF0);
    pe = LATE;
    LATE =   (pe & 0x0F) | masque;
    LCD_STROBE();
    Delay10us(4);
}

/* 	Efface le LCD et reviens en position 0 the LCD  */
void lcd_clear(void)
{
    LCD_RS = 0;
    lcd_write(0x01);
    DelayMs(2);
}

/*  Retour position 0  */
void lcd_home(void)
{
    LCD_RS = 0;
    lcd_write(0x02);
    DelayMs(2);
}

/* Ecriture d'une chaine de caractères sur LCD */
void lcd_puts(const char * s)
{
    LCD_RS = 1;	
    while(*s)
	{
		lcd_write(*s++);
	}
}

/*  Ecriture d'une chaine de caractères sur LCD sur une ligne */
void lcd_puts_line(unsigned char line, const char * s)
{
    lcd_clear_line(line);

    LCD_RS = 1;
    while(*s)
	{
        lcd_write(*s++);
	}
}

/* Efface la Ligne et retourne au départ */
void lcd_clear_line(unsigned char line)
{
    unsigned char i;
	
    if ( line < LCD_NB_LINE )
    {
        lcd_goto(adr_line[line]);
		
        LCD_RS = 1;	
        for ( i = 0; i < LCD_NB_CHAR; i++ )
		{
            lcd_write(0x20);
		}
			
        lcd_goto(adr_line[line]);
    }
}

/* Vas à la position spécifiée */
void lcd_goto(unsigned char pos)
{
    LCD_RS = 0;	
    lcd_write(0x80+pos);
}

/* initialisation LCD - mode 4 bit  */
void lcd_init(void)
{
    LCD_RS_TRIS = 0;
    LCD_EN_TRIS = 0;
		
    TRISEbits.TRISE4 = 0;
    TRISEbits.TRISE5 = 0;
    TRISEbits.TRISE6 = 0;
    TRISEbits.TRISE7 = 0;
	
    LATEbits.LATE4 = 0;
    LATEbits.LATE5 = 0;
    LATEbits.LATE6 = 0;
    LATEbits.LATE7 = 0;

    LCD_RS = 0;                         
    DelayMs(15);                       
    PORTE =  (PORTE & 0x0F) | 0x30;     
    LCD_STROBE();
	
    DelayMs(5);
    LCD_STROBE();
	
    Delay10us(10);
    LCD_STROBE();
	
    DelayMs(5);
    PORTE = (PORTE & 0x0F) | 0x20;
    LCD_STROBE();
	
    Delay10us(4);
	
    lcd_write(0x2C);	
    lcd_write(0x08);	
    lcd_write(0x0C);	
    lcd_write(0x06);	
	
    lcd_clear();
}
