// PAC.C
// Interface mat�rielle , relais , ......
// 
#include <plib.h>
#include "0_ADTEK.h"
#include "teleinfo.h"
#include "pac.h"

// Prototypes de fonction priv�es
void 			Macro_PAC_ON(void);
void 			Macro_RELEVE_ON(void);
void 			Macro_RELEVE_OFF(void);
unsigned char 	Etat_Relais(unsigned char no_relais);
unsigned char 	Relais(unsigned char no_relais, unsigned char etat_relais);
// Variables
unsigned int 	cpt_court_cycle = 0;  	// Contient le compteur en secondes de derni�re action -> emp�che aussi le d�marrage de la pac apr�s allumage r�gul	

//******************************************************************************************
// COMMANDE_PAC_ON : Enclenchement du relais de pilotage de la PAC
// Si le d�lai "Regul.AntiCourtCycle" n'est pas �coul� depuis la derni�re commande,
// on refuse l'allumage de la PAC (protection anti court cycle)
//******************************************************************************************
void Commande_PAC_ON(void)
{	
	// PAS DE RELEVE  -------------------------------------------------------------
	if (Regul.Releve_Mode == RELEVE_AUCUN)
	{
		Macro_PAC_ON();
	}
	// RELEVE COMPLEMENT ------------------------------------------------------------
	else if (Regul.Releve_Mode == RELEVE_APPOINT)
	{
		// La temp�rature est sup�rieure au seuil de rel�ve, on n'utilise pas la rel�ve
		if (Regul.Capteur[T_EXT].Temperature > Regul.Releve_Seuil)
		{
			Macro_PAC_ON();
			Macro_RELEVE_OFF();
		}
		else // On Lance la PAC et on peux utiliser aussi le compl�ment
		{
			// Allumage PAC
			Macro_PAC_ON();
			// On v�rifie que nous sommes dans une p�riode tarifaire autoris�e
			if (Etat_Releve_Ptec() == 1)
			{
				Macro_RELEVE_ON();
			}	
			else
			{				
				Macro_RELEVE_OFF();	
			}
		}
	}
	// RELEVE REMPLACEMENT ------------------------------------------------------------
	else if (Regul.Releve_Mode == RELEVE_REMPLACEMENT)
	{
		// On v�rifie que nous sommes dans une p�riode tarifaire autoris�e
		if (Etat_Releve_Ptec() == 1)
		{
			// On s'assure que la PAC est �teinte (par exemple changememnt tarifaire alors que la PAC tournait )
			Commande_PAC_OFF();
			Macro_RELEVE_ON();
		}	
		else
		{
			Macro_PAC_ON();
			Macro_RELEVE_OFF();	
		}
	}
}

void Macro_PAC_ON(void)
{
	if (RELAIS2 != RELAIS_ON)
	{
		if ((cpt1s - cpt_court_cycle) >= Regul.Anti_Court_Cycle)
		{
			cpt_court_cycle = cpt1s;
			RELAIS2 = RELAIS_ON;
		}	
	}
}

void Macro_RELEVE_ON(void)
{
	if (Etat_Relais(Regul.Releve_Relais) != RELAIS_ON)
	{
		// APPPOINT
		if (Regul.Releve_Mode == RELEVE_APPOINT)
		{
			// On ne d�marrage l'appoint que si la pac tourne. On b�n�ficie ainsi de l'Anti court cycle.
			if (Etat_Pac() == RELAIS_ON)
			{
				Relais(Regul.Releve_Relais,RELAIS_ON);
			}	
		}
		// REMPLACEMENT  // En mode Remplacement la PAC ne tourne pas
		else
		{
			if (Etat_Pac() == RELAIS_OFF)
			{
				Relais(Regul.Releve_Relais,RELAIS_ON);
			}
		}
	}
}

void Macro_RELEVE_OFF(void)
{
	if (Etat_Relais(Regul.Releve_Relais) != RELAIS_OFF)
	{
		Relais(Regul.Releve_Relais,RELAIS_OFF);	
	}
}

//******************************************************************************************
// COMMANDE_PAC_OFF : Relachement du relais de pilotage de la PAC
// Si le d�lai "Regul.AntiCourtCycle" n'est pas �coul� depuis la derni�re commande,
// 	on refuse l'extinction de la PAC (protection anti court cycle)
// La fonction retourne 1 si on a pu relacher le relais, 0 sinon. 
//******************************************************************************************
void Commande_PAC_OFF(void)
{
	// On �teint la rel�ve 
	//Macro_RELEVE_OFF(); // Supprim� le 22 mars car la rel�ve peut �tre ON
	// On �teint la PAC
	if (RELAIS2 != RELAIS_OFF)
	{
		if ((cpt1s - cpt_court_cycle) >= Regul.Anti_Court_Cycle)
		{
			// On r�initialise l'anti court cycle
			cpt_court_cycle = cpt1s;
			// On �teint la PAC
			RELAIS2 = RELAIS_OFF;
		}
	}	
}


//******************************************************************************************
// COMMANDE_CIRCULATEUR1_ON : Mise en route de la pompe de chauffage N�1
//
void Commande_CIRCULATEUR1_ON(void)
{
	if (RELAIS1 != RELAIS_ON)
	{
		RELAIS1 = RELAIS_ON;
	}	
}

//******************************************************************************************
// COMMANDE_CIRCULATEUR1_OFF : Arr�t de la pompe de chauffage N�1
// Le circulateur ne peux pas �tre coup� si la PAC est en marche !
void Commande_CIRCULATEUR1_OFF(void)
{
	if ((Etat_Pac() == RELAIS_OFF) && (Etat_Releve() == RELAIS_OFF)) // On v�rifie que la PAC et la rel�ve ne soit pas allum�e
	{
		if (RELAIS1 != RELAIS_OFF)  
		{
			RELAIS1 = RELAIS_OFF;
		}	
	}	
}

//******************************************************************************************
// RELAIS : Lecture de l'�tat du relais (no_relais) 
//******************************************************************************************
unsigned char Etat_Relais(unsigned char no_relais)
{
	if 		(no_relais == 1){ return(RELAIS1); }
	else if (no_relais == 2){ return(RELAIS2); }
	else if (no_relais == 3){ return(RELAIS3); }
	else if (no_relais == 4){ return(RELAIS4); }
	else if (no_relais == 5){ return(RELAIS5); }
	else if (no_relais == 6){ return(RELAIS6); }
	else if (no_relais == 7){ return(RELAIS7); }
	else if (no_relais == 8){ return(RELAIS8); }
	else { return(RELAIS_OFF); }
}


//******************************************************************************************
// RELAIS : Modifie l'�tat du relais (no_relais) en (etat_relais)
//******************************************************************************************
unsigned char Relais(unsigned char no_relais, unsigned char etat_relais)
{
	if 		(no_relais == 1){ RELAIS1 = etat_relais; }
	else if (no_relais == 2){ RELAIS2 = etat_relais; }
	else if (no_relais == 3){ RELAIS3 = etat_relais; }
	else if (no_relais == 4){ RELAIS4 = etat_relais; }
	else if (no_relais == 5){ RELAIS5 = etat_relais; }
	else if (no_relais == 6){ RELAIS6 = etat_relais; }
	else if (no_relais == 7){ RELAIS7 = etat_relais; }
	else if (no_relais == 8){ RELAIS8 = etat_relais; }	 
}


//******************************************************************************************
// ETAT_PAC: Indique l'�tat de la releve
// Evite d'adresser directement le relais
// retourne RELAIS_ON ou RELAIS_OFF
unsigned char Etat_Pac(void)
{
	return(RELAIS2);
}


