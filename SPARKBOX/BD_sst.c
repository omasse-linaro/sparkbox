
// GESTION EEPROM 16 Mbits

#include <p32xxxx.h>
#include "0_SPARKBOX.h"
#include "SST25VF016.h"
#include "log.h"
#include "teleinfo.h"
#include "BD_sst.h"
#include <stdio.h>
#include <stdlib.h>


const DRV_SPI_INIT_DATA SPI_Init_Data = {SST25_SPI_CHANNEL, 3, 0, 0, 1, 1, 0};


// STRUCTURE BD
// FLASH 1fts, Adresse max 1FFFFF (2 097 151));
// 1 bloc = 4KByte = 4096 Octets 0 -> 0xFFF. 512 bloc au total
// Pour le stockage de variables, on utilise 1 Bloc au total car l'erase minimal est un bloc entier
// Adresse            Taille                            			Fonction
//          0           73 728      // Bloc 1 + 18  	50 ans d'index TELEINFO 1 (4 octets) journaliers 	// TELE 1
//	   73 728			 4 096		// Bloc 19 			Libre
//	   77 824			73 728		// Bloc 20 + 18		50 ans d'index TELEINFO 2 (4 octets) journaliers 	// TELE 2
//	  151 552			 4 096		// Bloc 38			Libre
// 	  155 648		    73 728		// Bloc 39 + 18	    50 ans d'index xxxx (4 octets) journaliers

//  Sauvegardes (1 seule donnée par bloc)
//  1 224 704 			 4 096		// Bloc 300			Coefficient GFCI


// Fin mémoire flash !!!
/// --------------------------------------------------------------------------------------------------------------------------------------

#define ADR_DB_TELE1	        	 0		// TELE1 	18432 Groupes de 32bits
#define ADR_DB_TELE1_MAX	 		73727

#define ADR_DB_TELE2	  	 		77824	// TELE2 	18432 Groupes de 32bits
#define ADR_DB_TELE2_MAX	 		151552

#define ADR_DB_xxxx					155648	// xxxx 	18432 Groupes de 32bits
#define ADR_DB_xxx_MAX				229376



//  Sauvegardes  (1 seule donnée par bloc)
#define ADR_DB_COEF_GFCI			1224704 // Coefficient GFCI


#define OFFSET_TS_DAY	 14975	// Timestamp en jour du 01/01/2011 à 0h0m0s  (OFFSET_TS/24) // 50 ans -> 2061

unsigned char	indtu_sav = 0;

// Initialisation BD SST
void BD_Init(void)
{
	SST25Init((DRV_SPI_INIT_DATA *)&SPI_Init_Data);

	// Lecture Coef_GFCI
	BD_Lecture_Coef_GFCI();
}

// Sauvegarde Journalière des index
void BD_Enregistre_Jour_Index(void)
{
	long horodatage;
	unsigned int offset;
	unsigned int adresse_horodatage32;
	unsigned char affiche[TAILLE_LIGNE_LOG];
	unsigned char decalage[15];

	// Sauvegarde des index
	horodatage = utc.utc / 86400;			// Calcul du nombre de jours
	offset = horodatage - OFFSET_TS_DAY;	// Offset en jours


	if (offset> 0)
	{
		// TELE1
		adresse_horodatage32 = ADR_DB_TELE1 + (offset * 4);
		if (adresse_horodatage32 < ADR_DB_TELE1_MAX)
		{
			SST25WriteEnable();
			if (SST25WriteArray( adresse_horodatage32,(BYTE *) &Compteur[0].calc_index, 4) == 0)
			{
				strcpy(affiche,"BD  : PROBLEME Ecriture TELE1 (Index=");
				ultoa(decalage,Compteur[0].calc_index,10); strcat(affiche,decalage); strcat(affiche,",@=");
				ultoa(decalage,adresse_horodatage32,10); strcat(affiche,decalage); strcat(affiche,")");
				Ajout_Ligne_Log(affiche);
			}
		}
		else
		{
			Ajout_Ligne_Log("BD  : Problème date ou écriture sur Flash (TELE1)");
		}

		// TELE2
		adresse_horodatage32 = ADR_DB_TELE2 + (offset * 4);
		if (adresse_horodatage32 < ADR_DB_TELE2_MAX)
		{
			SST25WriteEnable();
			if (SST25WriteArray( adresse_horodatage32,(BYTE *) &Compteur[1].calc_index, 4) == 0)
			{
				strcpy(affiche,"BD  : PROBLEME Ecriture TELE2 (Index=");
				ultoa(decalage,Compteur[1].calc_index,10); strcat(affiche,decalage); strcat(affiche,",@=");
				ultoa(decalage,adresse_horodatage32,10); strcat(affiche,decalage); strcat(affiche,")");
				Ajout_Ligne_Log(affiche);
			}
		}
		else
		{
			Ajout_Ligne_Log("BD  : Problème date ou écriture sur Flash (TELE2)");
		}
	}
}


// Lecture Coef_GFCI
void BD_Enregistre_Coef_GFCI(void)
{
	unsigned char affiche[TAILLE_LIGNE_LOG];

	SST25SectorErase(ADR_DB_COEF_GFCI);
	SST25WriteEnable();
	if (!SST25WriteArray(ADR_DB_COEF_GFCI ,(BYTE *) &Sparkbox.Coef_Gfci, sizeof(Sparkbox.Coef_Gfci)))
	{
		strcpy(affiche,"BD  : Problème ecriture COEF_GFCI ");
		Ajout_Ligne_Log(affiche);
	}
}

void BD_Lecture_Coef_GFCI(void)
{
	SST25ReadArray(ADR_DB_COEF_GFCI,(BYTE *) &Sparkbox.Coef_Gfci, sizeof(Sparkbox.Coef_Gfci));
	if ((Sparkbox.Coef_Gfci < 200 ) || (Sparkbox.Coef_Gfci > 800))
	{
		Sparkbox.Coef_Gfci = 450;
		BD_Enregistre_Coef_GFCI();
	}
}

/* BD_Lecture_Jour_Teleinfo(unsigned char no, time_t tlecture)
 * no = Numéro de Téléinfo (0 ou 1)
 * tlecture = timestamp en secondes
 * Retour
 * - 0xFFFFFFFF (4294967295)	= Zone vierge
 * - 0xFFFFFFFE	(4294967294)	= Numéro de téléinfo invalide !
 * - 0xFFFFFFF0	(4294967280)	= Adresse calculée télé 1 (0)  incorrecte
 * - 0xFFFFFFF1 (4294967281)	= Adresse calculée télé 2 (1)  incorrecte
 */
unsigned int BD_Lecture_Jour_Teleinfo(unsigned char no, time_t tlecture)
{
	long horodatage;
	unsigned int offset;
	unsigned int adresse_horodatage32;
	unsigned int l_result = 0;

	// On vérifie que no soit valide
	if ((no < 0 ) && (no > 1))
	{
		return 0xFFFFFFFE;
	}

	horodatage = tlecture / 86400;			// Calcul du nombre de jours
	offset = horodatage - OFFSET_TS_DAY;	// Offset en jours

	if (no == 0)	adresse_horodatage32 = ADR_DB_TELE1 + (offset *4);
	else			adresse_horodatage32 = ADR_DB_TELE2 + (offset *4);

	if ((no == 0) && (adresse_horodatage32 > ADR_DB_TELE1_MAX)) return(0xFFFFFFF0);
	if ((no == 1) && (adresse_horodatage32 > ADR_DB_TELE2_MAX)) return(0xFFFFFFF1);

	SST25ReadArray( adresse_horodatage32,(BYTE *) &l_result, 4);
	return(l_result); // Erreur ou pas de données.
}


// Pour test only et accés via get !
void BD_Erase_All(void)
{
	SST25WriteEnable();
	SST25ChipErase();
}

// On transforme L'index Teleinfo (9 caractères) en 32 bits
unsigned int IndexTo32b(unsigned char index[])
{
	return((unsigned int)atoi(index));
}

