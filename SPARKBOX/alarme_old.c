// ALARME.C
// Gestion des Alarmes
// 
#include <plib.h>
#include "0_ADTEK.h"
#include "alarme.h"
#include "log.h"
#include "rtc_i2c.h"
#include "Stat_Pv.h"
#include "divers.h"
#include "teleinfo.h"
#include "mail.h"


//      ALARME_NONE		0x00
// Permet de définir pour le relais et le buzzer qu'elle Alarme est activée
#define ALARME_1		0x01
#define ALARME_2		0x02
#define ALARME_3		0x04
#define ALARME_4		0x08
#define MASQUE_ALARME_1	0xFE
#define MASQUE_ALARME_2	0xFD
#define MASQUE_ALARME_3	0xFB
#define MASQUE_ALARME_4	0xF7

unsigned char 	Alarme_Production;		// Définit si une alarme a déjà eu lieu dans la journée
unsigned int  	cpt1s_Sans_Production;	// Définit la seconde (cpt1s) ou l'alarme 
unsigned char 	Alarme_Teleinfo;		// Définit si une alarme a déjà eu lieu dans la journée
unsigned int  	cpt1s_Sans_Teleinfo;	// Définit la seconde (cpt1s) ou l'alarme 
unsigned char	Alarme_dummy[20];		// Variable temporaire
unsigned int  	cpt1s_Sans_Opto1;		// Définit la seconde (cpt1s) de l'alarme opto1
unsigned char 	Alarme_Opto1;			// Définit si une alarme a déjà eu lieu dans la journée
unsigned int  	cpt1s_Sans_Opto2;		// Définit la seconde (cpt1s) de l'alarme opto2
unsigned char 	Alarme_Opto2;			// Définit si une alarme a déjà eu lieu dans la journée
unsigned char   Email_Alarme;			// Définit quelle alarme est déclenchée pour email
unsigned char   Sms_Alarme;				// Définit quelle alarme est déclenchée pour sms



void Init_Alarmes(void)
{ 
	Alarme_Production 		= 0;			// Raz d'une Alarme éventuelle
	cpt1s_Sans_Production 	= 0;			// Raz de la seconde de détection de perte de production
	Alarme_Teleinfo			= 0;			// Raz d'une Alarme éventuelle
	cpt1s_Sans_Teleinfo 	= 0;			// Raz de la seconde de détection de perte Teleinfo
	cpt1s_Sans_Opto1		= 0;
	Alarme_Opto1			= 0;
	cpt1s_Sans_Opto2		= 0;
	Alarme_Opto2			= 0;
	Relais_Alarme			= ALARME_NONE;	// Raz de l'alarme relais
	Buzzer_Alarme			= ALARME_NONE;	// Raz de l'alarme buzzer
	Email_Alarme			= ALARME_NONE;	// Raz de l'alarme buzzer
	Sms_Alarme				= ALARME_NONE;	// Raz de l'alarme buzzer
}

//******************************************************************************************
// PROCESS_ALARMES
void Process_Alarmes(void)
{
	// ALARME PRODUCTION ------------------------------------------------------------------------
	// On vérifie que l'on gère l'alarme de production, et qu'une alerte n'ai pas déjà été faite.
	if (Alarme.Prod_Alarme != ALARME_NONE)
	{
		// On teste si on est dans l'intervalle de gestion de l'alarme
		if ((utc.heure > Alarme.Prod_Hdeb) && (utc.heure < Alarme.Prod_Hfin))
		{
			// On regarde si la production est nulle
			if ((Regul.Capteur[T_PUISS].Temperature_s[0] == 0x00) || (Regul.Capteur[T_PUISS].Temperature_s[0] == 0x30))
			{
				// La production est nulle, on arme l'alarme
				if (cpt1s_Sans_Production == 0)
				{
					cpt1s_Sans_Production = cpt1s;
				}
				// La production est nulle, on vérifie que l'on ne soit pas au bout des 30 minutes
				else if ((cpt1s-cpt1s_Sans_Production) > (30*60)) // 30 minutes
				{
					// Mail
					if ((Alarme.Prod_Alarme & ALARME_MAIL)&& (Alarme_Production == 0) && (Mail.Envoi == 0) && (Alarme.Email_Gestion != 0))
					{
						strcpy(Mail.Sujet,"[PVBox]Alarme. Production photovoltaïque.");
						strcpy(Mail.Corp_Message,"Bonjour,\r\n\r\n");
						strcat(Mail.Corp_Message,"Alarme: ");
						strcat(Mail.Corp_Message,date_jh());
						strcat(Mail.Corp_Message,"\n\rL'installation photovoltaïque n'a pas produit pendant 30 minutes consécutives.\r\n");
						strcat(Mail.Corp_Message,"Veuillez vérifier la production ou les paramètres de PVBox.\r\n");
						strcat(Mail.Corp_Message,"compteur n°");
						strcat(Mail.Corp_Message,Compteur[0].adco);
						strcat(Mail.Corp_Message,", Index = ");
						strcat(Mail.Corp_Message,Compteur[0].base);
						strcat(Mail.Corp_Message,"\r\nProduction journalière :");
						ultoa(Alarme_dummy,Stat_Jour,10);
						strcat(Mail.Corp_Message,Alarme_dummy);
						strcat(Mail.Corp_Message,"Wh\r\n");
						strcat(Mail.Corp_Message,"Ce message ne sera envoyé qu'une seule fois par jour.\r\n");
						strcat(Mail.Corp_Message,"PVBox N° ");
						strcat(Mail.Corp_Message,No_Serie());
						strcat(Mail.Corp_Message,"\r\n\r\nPVBox.\r\n\r\(Ne pas répondre, message envoyé automatiquement par PVBox)");
						Mail.Envoi = 1; // Déclencher l'envoi du mail 
					}
					// SMS
					if ((Alarme.Prod_Alarme & ALARME_SMS) && (Alarme_Production == 0) && (Sms.Envoi == 0) && (Alarme.Sms_Gestion != 0))
					{
						strcpy(Sms.Sujet,"sms-aj25014-1:");
						strcat(Sms.Sujet,Compte_Cms());
						strcat(Sms.Sujet,":VIsUnb8M:+33582950924:+33");
						strcat(Sms.Sujet,&Alarme.Sms_Tel[1]);  // On enlève le 0 du numéro pour passer à une numérotation internationale
						strcpy(Sms.Corp_Message,"PVBox (");
						strcat(Sms.Corp_Message,date_jh());
						strcat(Sms.Corp_Message,").ALARME PRODUCTION! Production du jour = ");
						ultoa(Alarme_dummy,Stat_Jour,10);
						strcat(Sms.Corp_Message,Alarme_dummy);
						// Numéro de série PVBox
						strcat(Sms.Corp_Message,". (PVBox Numero ");
						strcat(Sms.Corp_Message,Compte_Cms());
						strcat(Sms.Corp_Message,")");
						Sms.Envoi = 1; // Déclencher l'envoi du mail 
					}
					// Relais
					if ((Alarme.Prod_Alarme & ALARME_RELAIS1) && (Alarme_Production == 0))
					{
						Relais_Alarme = Relais_Alarme | ALARME_1;
					}	
					// Buzzer
					if ((Alarme.Prod_Alarme & ALARME_BUZZER) && (Alarme_Production == 0))
					{
						Buzzer_Alarme = Buzzer_Alarme | ALARME_1;
					}
					if (Alarme_Production == 0)
					{
						Ajout_Ligne_Log("Alarme production déclenchée.");
					}	
					Alarme_Production = 1; // Pour empecher une autre alarme aujourd'hui
						
				}
			}
			else
			{
				// Raz de la gestion de l'alarme de production
				cpt1s_Sans_Production = 0;
				Relais_Alarme = Relais_Alarme & MASQUE_ALARME_1;
				Buzzer_Alarme = Buzzer_Alarme & MASQUE_ALARME_1;
				if (Alarme_Production == 1)
				{
					Ajout_Ligne_Log("Alarme production terminée.");
					Alarme_Production = 2;
				} 
			}
		} 
		else
		{	// Raz de la gestion de l'alarme de production
			cpt1s_Sans_Production 	= 0;
			Relais_Alarme = Relais_Alarme & MASQUE_ALARME_1;
			Buzzer_Alarme = Buzzer_Alarme & MASQUE_ALARME_1;
		}
	}
	// ALARME DEFAUT TELEINFO ---------------------------------------------------------------------------
	// On vérifie que l'on gère l'alarme de défaut téléinfo, et qu'une alerte n'ai pas déjà été faite.
	if (Alarme.Teleinfo_prod != ALARME_NONE)
	{
			// On regarde si la production est nulle
		if (Compteur[0].etat != CAPTEUR_OK)
		{
			// La production est nulle, on arme l'alarme
			if (cpt1s_Sans_Teleinfo == 0)
			{
				cpt1s_Sans_Teleinfo = cpt1s;
			}
			// Le Compteur Téléinfo est absent, on vérifie que l'on ne soit pas au bout des 30 minutes
			else if ((cpt1s-cpt1s_Sans_Teleinfo) > (30*60)) // 30 minutes
			{
				if ((Alarme.Teleinfo_prod & ALARME_MAIL) && (Alarme_Teleinfo == 0) && (Mail.Envoi == 0) && (Alarme.Email_Gestion != 0))
				{
					// Gestion de l'Alarme
					strcpy(Mail.Sujet,"[PVBox]Alarme! Perte compteur téléinfo de production");
					strcpy(Mail.Corp_Message,"Bonjour,\r\n\r\n");
					strcat(Mail.Corp_Message,"Alarme: ");
					strcat(Mail.Corp_Message,date_jh());
					strcat(Mail.Corp_Message,"\r\nL'installation photovoltaïque ne recoit pas d'informations en provenance du compteur électronique \r\n");
					strcat(Mail.Corp_Message,"de production.\r\n");
					strcat(Mail.Corp_Message,"Veuillez vérifier l'installation ou les paramètres de PVBox.\r\n");
					strcat(Mail.Corp_Message,"Ce message ne sera envoyé qu'une seule fois par jour.\r\n");
					strcat(Mail.Corp_Message,"PVBox N° ");
					strcat(Mail.Corp_Message,No_Serie());
					strcat(Mail.Corp_Message,"\r\n\r\nPVBox.\r\n\r\(Ne pas répondre, message envoyé automatiquement par PVBox)");
					Mail.Envoi = 1; // Déclencher l'envoi du mail 
				}
				// SMS
				if ((Alarme.Teleinfo_prod & ALARME_SMS) && (Alarme_Teleinfo == 0) && (Sms.Envoi == 0) && (Alarme.Sms_Gestion != 0))
				{
					strcpy(Sms.Sujet,"sms-aj25014-1:");
					strcat(Sms.Sujet,Compte_Cms());
					strcat(Sms.Sujet,":VIsUnb8M:+33582950924:+33");
					strcat(Sms.Sujet,&Alarme.Sms_Tel[1]);  // On enlève le 0 du numéro pour passer à une numérotation internationale
					strcpy(Sms.Corp_Message,"PVBox (");
					strcat(Sms.Corp_Message,date_jh());
					strcat(Sms.Corp_Message,").ALARME PERTE COMPTEUR TELEINFO! Production du jour = ");
					ultoa(Alarme_dummy,Stat_Jour,10);
					strcat(Sms.Corp_Message,Alarme_dummy);
					// Numéro de série PVBox
					strcat(Sms.Corp_Message,". (PVBox Numero ");
					strcat(Sms.Corp_Message,Compte_Cms());
					strcat(Sms.Corp_Message,")");
					Sms.Envoi = 1; // Déclencher l'envoi du mail 
				}
				if (Alarme.Teleinfo_prod & ALARME_RELAIS1)
				{
					Relais_Alarme = Relais_Alarme | ALARME_2;
				}		
				// Buzzer
				if (Alarme.Teleinfo_prod & ALARME_BUZZER)
				{
					Buzzer_Alarme = Buzzer_Alarme | ALARME_2;
				}
				if (Alarme_Teleinfo == 0)
				{
					Ajout_Ligne_Log("Alarme perte compteur téléinfo déclenchée.");	
				}
					
				Alarme_Teleinfo = 1; // Indique que l'alarme a été faite	
			}
		} 
		else
		{	// Raz de la gestion de l'alarme de production
			cpt1s_Sans_Teleinfo = 0;
			Relais_Alarme = Relais_Alarme & MASQUE_ALARME_2;
			Buzzer_Alarme = Buzzer_Alarme & MASQUE_ALARME_2;
			if (Alarme_Teleinfo == 1)
			{
				Ajout_Ligne_Log("Alarme perte compteur téléinfo terminée.");
				Alarme_Teleinfo = 2;
			} 
		}
	}
	
	// ALARME DEFAUT ENTREE OPTO 1---------------------------------------------------------------------------
	// On vérifie que l'on gère l'alarme sur déclenchement Opto, et qu'une alerte n'ai pas déjà été faite.
	if (Alarme.Opto_Numeros != ALARME_NONE)
	{
		if ((OPTO1 == 0)&&(Alarme.Opto_Numeros & ALARME_OPTO1)) 
		{
			// OPTO1 déclenché, on arme l'alarme
			if (cpt1s_Sans_Opto1 == 0)
			{
				cpt1s_Sans_Opto1 = cpt1s;
			}
			// On vérifie que l'on ne soit pas au bout des 30 minutes
			else if ((cpt1s-cpt1s_Sans_Opto1) > (1)) // 30 minutes
			{
				if ((Alarme.Opto_Alarme & ALARME_MAIL) && (Alarme_Opto1 == 0) && (Mail.Envoi == 0) && (Alarme.Email_Gestion != 0))
				{
					// Gestion de l'Alarme
					strcpy(Mail.Sujet,"[PVBox]Alarme! Opto 1 Enclenché");
					strcpy(Mail.Corp_Message,"Bonjour,\r\n\r\n");
					strcat(Mail.Corp_Message,"Alarme: ");
					strcat(Mail.Corp_Message,date_jh());
					strcat(Mail.Corp_Message,"\r\nL'opto 1 surveillé par PVBox a été déclenché \r\n");
					strcat(Mail.Corp_Message,"Veuillez vérifier l'installation ou les paramètres de PVBox.\r\n");
					strcat(Mail.Corp_Message,"Ce message ne sera envoyé qu'une seule fois par jour.\r\n");
					strcat(Mail.Corp_Message,"PVBox N° ");
					strcat(Mail.Corp_Message,No_Serie());
					strcat(Mail.Corp_Message,"\r\n\r\nPVBox.\r\n\r\(Ne pas répondre, message envoyé automatiquement par PVBox)");
					Mail.Envoi = 1; // Déclencher l'envoi du mail 
				}
				// SMS
				if ((Alarme.Opto_Alarme & ALARME_SMS) && (Alarme_Opto1 == 0) && (Sms.Envoi == 0) && (Alarme.Sms_Gestion != 0))
				{
					strcpy(Sms.Sujet,"sms-aj25014-1:");
					strcat(Sms.Sujet,Compte_Cms());
					strcat(Sms.Sujet,":VIsUnb8M:+33582950924:+33");
					strcat(Sms.Sujet,&Alarme.Sms_Tel[1]);  // On enlève le 0 du numéro pour passer à une numérotation internationale
					strcpy(Sms.Corp_Message,"PVBox (");
					strcat(Sms.Corp_Message,date_jh());
					strcat(Sms.Corp_Message,").ALARME Opto1 enclenché! Production du jour = ");
					ultoa(Alarme_dummy,Stat_Jour,10);
					strcat(Sms.Corp_Message,Alarme_dummy);
					// Numéro de série PVBox
					strcat(Sms.Corp_Message,". (PVBox Numero ");
					strcat(Sms.Corp_Message,Compte_Cms());
					strcat(Sms.Corp_Message,")");
					Sms.Envoi = 1; // Déclencher l'envoi du mail 
				}
				if (Alarme.Opto_Alarme & ALARME_RELAIS1)
				{
					Relais_Alarme = Relais_Alarme | ALARME_3;
				}		
				// Buzzer
				if (Alarme.Opto_Alarme & ALARME_BUZZER)
				{
					Buzzer_Alarme = Buzzer_Alarme | ALARME_3;
				}
				if (Alarme_Opto1 == 0)
				{
					Ajout_Ligne_Log("Alarme OPTO1 déclenchée.");	
				}
				Alarme_Opto1 = 1; // Indique que l'alarme a été faite	
			}
		} 
		else
		{	// Raz de la gestion de l'alarme de production
			cpt1s_Sans_Opto1 = 0;
			Relais_Alarme = Relais_Alarme & MASQUE_ALARME_3;
			Buzzer_Alarme = Buzzer_Alarme & MASQUE_ALARME_3;
			if (Alarme_Opto1 == 1)
			{
				Ajout_Ligne_Log("Alarme OPTO1 terminée.");
				Alarme_Opto1 = 2;
			} 
		}
	}
	
	// ALARME DEFAUT ENTREE OPTO 2---------------------------------------------------------------------------
	// On vérifie que l'on gère l'alarme sur déclenchement Opto, et qu'une alerte n'ai pas déjà été faite.
	if (Alarme.Opto_Numeros != ALARME_NONE)
	{
		if ((OPTO2 == 0)&&(Alarme.Opto_Numeros & ALARME_OPTO2)) 
		{
			// OPTO2 déclenché, on arme l'alarme
			if (cpt1s_Sans_Opto2 == 0)
			{
				cpt1s_Sans_Opto2 = cpt1s;
			}
			// On vérifie que l'on ne soit pas au bout des 30 minutes
			else if ((cpt1s-cpt1s_Sans_Opto2) > (1)) // 30 minutes
			{
				if ((Alarme.Opto_Alarme & ALARME_MAIL) && (Alarme_Opto2 == 0) && (Mail.Envoi == 0) && (Alarme.Email_Gestion != 0))
				{
					// Gestion de l'Alarme
					strcpy(Mail.Sujet,"[PVBox]Alarme! Opto 2 Enclenché");
					strcpy(Mail.Corp_Message,"Bonjour,\r\n\r\n");
					strcat(Mail.Corp_Message,"Alarme: ");
					strcat(Mail.Corp_Message,date_jh());
					strcat(Mail.Corp_Message,"\r\nL'opto 2 surveillé par PVBox a été déclenché \r\n");
					strcat(Mail.Corp_Message,"Veuillez vérifier l'installation ou les paramètres de PVBox.\r\n");
					strcat(Mail.Corp_Message,"Ce message ne sera envoyé qu'une seule fois par jour.\r\n");
					strcat(Mail.Corp_Message,"PVBox N° ");
					strcat(Mail.Corp_Message,No_Serie());
					strcat(Mail.Corp_Message,"\r\n\r\nPVBox.\r\n\r\(Ne pas répondre, message envoyé automatiquement par PVBox)");
					Mail.Envoi = 1; // Déclencher l'envoi du mail 
				}
				// SMS
				if ((Alarme.Opto_Alarme & ALARME_SMS) && (Alarme_Opto2 == 0) && (Sms.Envoi == 0) && (Alarme.Sms_Gestion != 0))
				{
					strcpy(Sms.Sujet,"sms-aj25014-1:");
					strcat(Sms.Sujet,Compte_Cms());
					strcat(Sms.Sujet,":VIsUnb8M:+33582950924:+33");
					strcat(Sms.Sujet,&Alarme.Sms_Tel[1]);  // On enlève le 0 du numéro pour passer à une numérotation internationale
					strcpy(Sms.Corp_Message,"PVBox (");
					strcat(Sms.Corp_Message,date_jh());
					strcat(Sms.Corp_Message,").ALARME Opto2 enclenché! Production du jour = ");
					ultoa(Alarme_dummy,Stat_Jour,10);
					strcat(Sms.Corp_Message,Alarme_dummy);
					// Numéro de série PVBox
					strcat(Sms.Corp_Message,". (PVBox Numero ");
					strcat(Sms.Corp_Message,Compte_Cms());
					strcat(Sms.Corp_Message,")");
					Sms.Envoi = 1; // Déclencher l'envoi du mail 
				}
				if (Alarme.Opto_Alarme & ALARME_RELAIS1)
				{
					Relais_Alarme = Relais_Alarme | ALARME_4;
				}		
				// Buzzer
				if (Alarme.Opto_Alarme & ALARME_BUZZER)
				{
					Buzzer_Alarme = Buzzer_Alarme | ALARME_4;
				}
				if (Alarme_Opto2 == 1)
				{
					Ajout_Ligne_Log("Alarme OPTO2 déclenchée.");	
				}	
				Alarme_Opto2 = 1; // Indique que l'alarme a été faite	
			}
		} 
		else
		{	// Raz de la gestion de l'alarme de production
			cpt1s_Sans_Opto2 = 0;
			Relais_Alarme = Relais_Alarme & MASQUE_ALARME_4;
			Buzzer_Alarme = Buzzer_Alarme & MASQUE_ALARME_4;
			if (Alarme_Opto2 == 1)
			{
				Ajout_Ligne_Log("Alarme OPTO2 terminée.");
				Alarme_Opto2 = 2;
			} 
		}
	}
	
	// GESTION DU RELAIS
	if (Relais_Alarme > 0) 
    {
    	Relais(1,RELAIS_ON);
    }
    else
    {
    	Relais(1,RELAIS_OFF);
    }
    
    // GESTION DU MAIL	
}



void Mail_Alarme(unsigned char message)
{
	strcpy(Mail.Sujet,"[PVBox]Alarme. Production photovoltaïque.");
	strcpy(Mail.Corp_Message,"Bonjour,\r\n\r\n");
	strcat(Mail.Corp_Message,"Alarme: ");
	strcat(Mail.Corp_Message,date_jh());
	strcat(Mail.Corp_Message,"\n\rL'installation photovoltaïque n'a pas produit pendant 30 minutes consécutives.\r\n");
	strcat(Mail.Corp_Message,"Veuillez vérifier la production ou les paramètres de PVBox.\r\n");
	strcat(Mail.Corp_Message,"compteur n°");
	strcat(Mail.Corp_Message,Compteur[0].adco);
	strcat(Mail.Corp_Message,", Index = ");
	strcat(Mail.Corp_Message,Compteur[0].base);
	strcat(Mail.Corp_Message,"\r\nProduction journalière :");
	ultoa(Alarme_dummy,Stat_Jour,10);
	strcat(Mail.Corp_Message,Alarme_dummy);
	strcat(Mail.Corp_Message,"Wh\r\n");
	strcat(Mail.Corp_Message,"Ce message ne sera envoyé qu'une seule fois par jour.\r\n");
	strcat(Mail.Corp_Message,"PVBox N° ");
	strcat(Mail.Corp_Message,No_Serie());
	strcat(Mail.Corp_Message,"\r\n\r\nPVBox.\r\n\r\(Ne pas répondre, message envoyé automatiquement par PVBox)");
	Mail.Envoi = 1; // Déclencher l'envoi du mail 
}

void Sms_Alarme(unsigned char message)
{
	strcpy(Sms.Sujet,"sms-aj25014-1:");
	strcat(Sms.Sujet,Compte_Cms());
	strcat(Sms.Sujet,":VIsUnb8M:+33582950924:+33");
	strcat(Sms.Sujet,&Alarme.Sms_Tel[1]);  // On enlève le 0 du numéro pour passer à une numérotation internationale
	strcpy(Sms.Corp_Message,"PVBox (");
	strcat(Sms.Corp_Message,date_jh());
	strcat(Sms.Corp_Message,").ALARME Opto2 enclenché! Production du jour = ");
	ultoa(Alarme_dummy,Stat_Jour,10);
	strcat(Sms.Corp_Message,Alarme_dummy);
	// Numéro de série PVBox
	strcat(Sms.Corp_Message,". (PVBox Numero ");
	strcat(Sms.Corp_Message,Compte_Cms());
	strcat(Sms.Corp_Message,")");
	Sms.Envoi = 1; // Déclencher l'envoi du mail 
}	


