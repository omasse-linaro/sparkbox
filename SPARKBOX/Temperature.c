/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 * Nom:			TEMPERATURE.C
 * Fonction :	Gestion des températures
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
#include "temperature.h"            						
#include "0_SPARKBOX.h"

#define 		NB_ECHANTILLONS_FILTRE_MEDIAN 	10 					// 10 Echantillons pour commencer !		
#define 		NB_FILTRES_MEDIAN 			 	NB_MAX_CAPTEURS + 1	// +1 pour le COP
#define 		INDEX_FILTRE_MEDIAN_COP			NB_MAX_CAPTEURS		// Index du COP

// GESTION FILTRE MEDIAN SUR LES CAPTEURS
			
short 			Filtre_Capteur[NB_FILTRES_MEDIAN][NB_ECHANTILLONS_FILTRE_MEDIAN];  	// Gestion Filtre médian
unsigned char 	Filtre_Nb[NB_FILTRES_MEDIAN];										// Nb echantillons
unsigned char 	Filtre_Ptr[NB_FILTRES_MEDIAN];										// Pointeur echantillons
short 			Filtre_Temp[NB_ECHANTILLONS_FILTRE_MEDIAN];							// tableau temporaire pour le tri

unsigned char 	fi;
unsigned char 	fj;
unsigned char 	Valeur_Mediane;
unsigned short	elementInsere;

//********************************************************************************************************************
//INITIALISATION DU FILTRE MEDIAN
void Init_Filtre_Median(void)
{	
	for (fi = 0; fi < NB_FILTRES_MEDIAN; fi++)
	{
		for (fj = 0; fj < NB_ECHANTILLONS_FILTRE_MEDIAN; fj++)
		{	
			Filtre_Capteur[fi][fj] = 0;
		}	
		Filtre_Nb[fi]=0;
		Filtre_Ptr[fi]=0;
 	}
 	Valeur_Mediane = (unsigned char) (NB_ECHANTILLONS_FILTRE_MEDIAN / 2);
}

//**********************************************************************************************************************
// GESTION DU FILTRE MEDIAN
short Filtre_Median(unsigned char No_Capteur, short valeur)
{
	
	if (Filtre_Ptr[No_Capteur] >= NB_ECHANTILLONS_FILTRE_MEDIAN)
	{
		 Filtre_Ptr[No_Capteur] = 0;
	}
	
	Filtre_Capteur[No_Capteur][Filtre_Ptr[No_Capteur]]=valeur;
	Filtre_Ptr[No_Capteur]++;
	
	// Si on n'a pas assez d'échantillons, on envoi la valeur d'origine
	if (Filtre_Nb[No_Capteur] <  NB_ECHANTILLONS_FILTRE_MEDIAN)
	{
		Filtre_Nb[No_Capteur]++;
		return (valeur);
	}
	else
	{
		// On a les "NB_ECHANTILLONS_FILTRE_MEDIAN" stockées, on vas retourner la valeur médiane
		// Recopie des valeurs dans un tableau temporaire
		for (fj = 0; fj < NB_ECHANTILLONS_FILTRE_MEDIAN; fj++)
		{	
			Filtre_Temp[fj] = Filtre_Capteur[No_Capteur][fj];
		}	
		// Tri par insertion du tableau temporaire
		for (fi = 1; fi < NB_ECHANTILLONS_FILTRE_MEDIAN; fi++) 
		{
        	// Stockage de la valeur en i 
        	elementInsere = Filtre_Temp[fi];
        	// Décale les éléments situés avant Filtre_Temp[fi] vers la droite jusqu'à trouver la position d'insertion 
        	for (fj = fi; fj > 0 && Filtre_Temp[fj - 1] > elementInsere; fj--) 
	        {
            	Filtre_Temp[fj] = Filtre_Temp[fj - 1];
        	}
        	// Insertion de la valeur stockée à la place vacante 
        	Filtre_Temp[fj] = elementInsere;
    	}
		return(Filtre_Temp[Valeur_Mediane]); 
	}	
}

//**********************************************************************************************************************
//  HectoTempToStr
void HectoTempToStr(short HectoTemp,unsigned char* out)
{
	static unsigned short 	short_trav;
	static unsigned short 	short_div;
	static unsigned char	i_out;
	
	// ajout pour éviter de convertir 10080 en 10,80 !  18/04/2013
	unsigned char start = 0;		// correction !!!
	
	
	short_trav = 0;
	i_out = 1;
	
	
	
	if (HectoTemp < 0)
	{
		out[0] = 0x2D; // signe -
		short_trav = HectoTemp * -1;
	}
	else
	{
		out[0] = 0x20; // Espace
		short_trav = HectoTemp;
	}

	short_div = short_trav / 10000;
	if (short_div != 0 )
	{
		out[i_out] = 0x30 + short_div;
		short_trav = short_trav - (short_div * 10000);
		i_out++;
		start = 1;			// correction !!!!
	}

    short_div = short_trav / 1000;
	if (short_div != 0 || start)			// correction !!!
	{
		out[i_out] = 0x30 + short_div;
		short_trav = short_trav - (short_div * 1000);
		i_out++;
	}
	
	short_div = short_trav / 100;
	out[i_out] = 0x30 + short_div;
	short_trav = short_trav - (short_div * 100);
	i_out++;	
	
	// Insertion du point
	out[i_out] = 0x2C; // ,  2c=,   2E=.
	i_out++;
	
	short_div = short_trav / 10;

	out[i_out] = 0x30 + short_div;
	short_div = short_trav - (short_div * 10);
	i_out++;
	
	out[i_out] = 0x30 + short_div;
	short_trav = short_trav - (short_div * 10);
	i_out++;
	
	out[i_out] = 0x00;
	return;
}

//-----------------------------------------------------------------------------------------------------------------
// StringToHectoTemp
BOOL StringToHectoTemp(BYTE* str, short* stemp)
{
	unsigned char cpth,minus,virgule,saisi;
	short th,th1,th2;

	th = 0;
	cpth = 0;
	minus = 0;
	virgule = 0;
	th1 = 0;
	th2 = 0;
	saisi=0;
 	
	if (strlen(str) > 6)
	{
		return FALSE;
	}
	for (cpth = 0; cpth < strlen(str); cpth++)
	{
		if (str[cpth] == 0x2D) //-
		{
			minus++;
		}
		else if ((str[cpth] == 0x2E) || (str[cpth] == 0x2C)) //. ou ,
		{
			if (saisi == 1)
			{
				th = th + th1*100;
			}
			else if (saisi == 2)
			{
				th = th + th1*1000;
				th = th + th2*100;
			}
			virgule++;	
			th1 = 0;
			th2 = 0;
			saisi = 0;
		}	
		else if ((str[cpth] >= 0x30) && (str[cpth] <= 0x39))
		{
		  saisi++;		
		  if (th1 == 0)
		  {
		  	th1 = str[cpth] - 0x30;
		  	if (saisi == 2) saisi--; // Pour éliminer les zéros non significatifs
		  }
		  else
		  {
		  	th2 = str[cpth] - 0x30;
		  }
		}
	}
	
	if (virgule > 0)
	{	
		// On traite les chiffres après la virgule
		th = th + th1*10;
		th = th + th2;
	}
	else
	{	// Si il n'y a pas de virgule, on traite les unités et dizaines
		if (saisi == 1)
		{
			th = th + th1*100;
		}
		else if (saisi == 2)
		{
			th = th + th1*1000;
			th = th + th2*100;
		}
	}

	if (minus > 0)
	{
		th = th * -1;
	}
	if ((virgule > 1) || (minus > 1)) // On n'accepte pas 2 virgules ou 2 -
	{
		return FALSE;
	}
	
	if ((th > T_HECTO_MIN ) && (th < T_HECTO_MAX)) 
	{
		*stemp = th;
		return TRUE;
	}
	else
	{
		return FALSE;
	}	
}

//-----------------------------------------------------------------------------------------------------------------
// Temptostr
unsigned char *Temptostr(unsigned char id)
{
	static unsigned char out[10];
	if (Sparkbox.Capteur[id].Etat == CAPTEUR_OK)
    {
		strcpy(out,Sparkbox.Capteur[id].Temperature_s);
	}
	else if (Sparkbox.Capteur[id].Etat == CAPTEUR_ERREUR)
	{
		strcpy(out,"err..");   
	}
	else if (Sparkbox.Capteur[id].Etat == CAPTEUR_DEMARRAGE)
	{
		strcpy(out,"start");   
	}
	else if (Sparkbox.Capteur[id].Etat == CAPTEUR_ABSENT)
	{
		strcpy(out,"abs..");   
	}
	else if (Sparkbox.Capteur[id].Etat == CAPTEUR_AUCUN)
	{
		strcpy(out,"     ");   
	}
	else // ne doit pas arriver
	{
		strcpy(out,"99.99");
	}
	return(out);
}


