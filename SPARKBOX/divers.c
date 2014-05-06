/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 * Nom:			divers.c
 * Fonction :	Procédures d'usage général
 *
 *  SARL ADTEK
 **********************************************************************************************************
 * Author | Jean Arhainx  |  Date  19/03/2014   |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or
 * send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *********************************************************************************************************/
#include "0_SPARKBOX.h"
#include "divers.h"

unsigned char	Piezzo = 1;	// Indique si le Buzzer est activé. Démarre à 1 pour permettre l'initialisation dans un piezzo off

void ctoa(char Value, BYTE* Buffer)
{
	BYTE i;
	WORD Digit;
	WORD Divisor;
	BOOL Printed = FALSE;
	
	if (Value < 0) 
	{
        *Buffer++ = '-';
	    Value = -Value;
    }
	if(Value)
	{
		for(i = 0, Divisor = 10000; i < 5u; i++)
		{
			Digit = Value/Divisor;
			if(Digit || Printed)
			{
				*Buffer++ = '0' + Digit;
				Value -= Digit*Divisor;
				Printed = TRUE;
			}
			Divisor /= 10;
		}
	}
	else
	{
		*Buffer++ = '0';
	}
	*Buffer = '\0';
}

unsigned char * No_Serie(void)
{
	static unsigned char out[18];
	BYTE i;		
	
	out[0]=0x00;

	for(i = 0; i < 6u; i++)
	{	
		out[i*2]	 = btohexa_high(AppConfig.MyMACAddr.v[i]);
		out[(i*2)+1] = btohexa_low(AppConfig.MyMACAddr.v[i]);
	}
	out[17]=0x00;	
	return(out);
}



// Compte_Cms
// On transforme l'adresse MAC en numéro de compte SMS qui ne contient que des minuscules
unsigned char * Compte_Cms(void)
{
	static unsigned char out[11];
	BYTE i;		
	
	out[0]=0x00;

	for(i = 1; i < 6u; i++)
	{	
		out[(i-1)*2]	 = btohexa_high(AppConfig.MyMACAddr.v[i]) +49;
		out[((i-1)*2)+1] = btohexa_low(AppConfig.MyMACAddr.v[i]) +49;
	}
	out[10]=0x00;	
	return(out);
}


//******************************************************************************************
// RELAIS : Lecture de l'état du relais (no_relais) 
//******************************************************************************************
unsigned char Etat_Relais(unsigned char no_relais)
{
	if 		(no_relais == 1){ return(RELAIS1); }
	else if (no_relais == 2){ return(RELAIS2); }
	else if (no_relais == 3){ return(RELAIS3); }
	else if (no_relais == 4){ return(RELAIS4); }
	else { return(RELAIS_OFF); }
}


//******************************************************************************************
// RELAIS : Modifie l'état du relais (no_relais) en (etat_relais)
//******************************************************************************************
unsigned char Relais(unsigned char no_relais, unsigned char etat_relais)
{
	if 		(no_relais == 1) { RELAIS1 = etat_relais; }
	else if (no_relais == 2) { RELAIS2 = etat_relais; }
	else if (no_relais == 3) { RELAIS3 = etat_relais; }
	else if (no_relais == 4) { RELAIS4 = etat_relais; }

}


/*****************************************************************************
  Function:
    void PadBuffer (DWORD value, BYTE * buffer)

  Summary:
    Pads a hour/minute/second value to include a leading zero

  Description:
    This function will check a time value to determine if it's a single
    digit value.  If so, it will insert a leading zero.

  Precondition:
    None

  Parameters:
    value - The time value
    buffer - The string to be updated

  Return Values:
    None
  ***************************************************************************/
void PadBuffer (DWORD value, BYTE * buffer)
{
    if (value < 10)
    {
        *(buffer + 1) = *buffer;
        *buffer = '0';
    }
}
// Attention longueur_totale doit être inférieur à la taille de la chaine
//void PadLeftZero (BYTE * buffer, unsigned char longueur_totale)
void PadLeftZero (BYTE buffer[], unsigned char longueur_totale)
{
	unsigned char idx;
	unsigned char len;
			
	len = strlen(buffer);
	while (strlen(buffer) < longueur_totale)
	{
		for (idx=len+1;idx>0;idx--)
		{
			buffer[idx]=buffer[idx-1];
		}	
		buffer[0]='0';
		len++;
	}		
}



// Initialisation des Relais pour le mode de commande manuelle.
// Attention, il faut exclure les relais qui sont attitrés (RELAIS1+2+3 pour PVTBox)
void Init_Relais_Manuel(void)
{
	unsigned char cpt;
	
	for (cpt = 0; cpt < NB_RELAIS; cpt++)
	{
		// Les relais 1 à 2 ne sont pas autorisé sur la sparkbox
		if (cpt <= 1)
		{
			Relais_Man[cpt].Pilotable	= NON;
		}
		else
		{
			Relais_Man[cpt].Pilotable	= OUI;
			if (Sparkbox.Ventilation  == (cpt + 1) ) Relais_Man[cpt].Pilotable	= NON;
		}

		Relais_Man[cpt].Relais 		= RELAIS_OFF;
		Relais_Man[cpt].Time		= 0;
	}
}

void Process_Relais_Manuel(void)
{
	static unsigned int cpt_loop = 10000; // Permet de faire la lecture qu'une fois sur 15000
	static unsigned char rel_no;

	// Une fois sur 15000 on traite la gestion des relais manuels. Inutile de le faire à chaque cycle
	if (cpt_loop >= 15000)
	{
		// Pour chaque Relais ...
		for (rel_no = 0; rel_no < NB_RELAIS; rel_no++)
		{
			// On regarde si le relais est pilotable manuellement
			if (Relais_Man[rel_no].Pilotable == OUI)
			{
				// Si le relais est activé ou demandé pour activation
				if (Relais_Man[rel_no].Relais == RELAIS_ON)
				{
					// Pas de programmation de temps, on active le relais en continu
					if (Relais_Man[rel_no].Time == 0)
					{
						Relais((rel_no+1),RELAIS_ON);
					}
					// Sinon, on regarde si il est temps de couper le relais.
					else if (Relais_Man[rel_no].Time < utc.utc_fr)
					{
						Relais((rel_no+1),RELAIS_OFF);
						Relais_Man[rel_no].Relais 	= RELAIS_OFF;
						Relais_Man[rel_no].Time 	= 0;
					}
					else
					{
						Relais((rel_no+1),RELAIS_ON);
					}
				}
				else
				{
					Relais((rel_no+1),RELAIS_OFF);
				}
			}
		}		
		cpt_loop = 0;
	}
	else
	{
		cpt_loop++;
	}
	

}


unsigned char SPICalcutateBRG(unsigned int pb_clk, unsigned int spi_clk)
{
    unsigned int brg;

    brg = pb_clk / (2 * spi_clk);

    if(pb_clk % (2 * spi_clk))
        brg++;

    if(brg > 0x100)
        brg = 0x100;

    if(brg)
        brg--;

    return (unsigned char) brg;
}

/*
** find the last occurrance of find in string
*/
char *strrstr(char *string, char *find)
{
	size_t stringlen, findlen;
	char *cp;

	findlen = strlen(find);
	stringlen = strlen(string);
	if (findlen > stringlen)
		return NULL;

	for (cp = string + stringlen - findlen; cp >= string; cp--)
		if (strncmp(cp, find, findlen) == 0)
			return cp;

	return NULL;
}

void lltoa( BYTE* Buffer, long long Value, unsigned char radix)
{
	BYTE i;
	long long Digit;
	long long  Divisor;
	BOOL Printed = FALSE;

	if(Value)
	{
		for(i = 0, Divisor = 1000000000000000000; i < 19; i++)
		{
			Digit = Value/Divisor;
			if(Digit || Printed)
			{
				*Buffer++ = '0' + Digit;
				Value -= Digit*Divisor;
				Printed = TRUE;
			}
			Divisor /= 10;
		}
	}
	else
	{
		*Buffer++ = '0';
	}

	*Buffer = '\0';
}


int strcasecmp(const unsigned char *s1, const unsigned char *s2)
{
  const unsigned char *c1 = s1, *c2 = s2;
  unsigned char ch;
  int d = 0;

  while ( 1 )
  {
    d = toupper(ch = *c1++) - toupper(*c2++);
    if ( d || !ch )  break;
  }
  return d;
}