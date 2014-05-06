/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 *
 * Gestion du num�ro de version et du changelog
 *
 *  SARL ADTEK

 **********************************************************************************************************
 * Author | Jean Arhainx  |  Date  19/03/2014   |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or
 * send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *********************************************************************************************************/
#ifndef __VERSION_SPARKBOX
	#define __VERSION_SPARKBOX
	#define VERSION_SOFT		"0.2f"
#endif

/* TODO
 * Gestion BP
 * Autoriser annulation alarme via BP !


---------------- CHANGELOG -------------------------------------------------------------------------------------------------
 14/04/2014	:	0.2f
 * Ajout Coefficient GFCI pour calibrer la bobine de d�tection de courant de fuite (stock� en m�moire flash)
 * Ajout stockage index TELE1 + TELE2 dans la m�moire flash (1 fois par jour).
 * Acc�s via "page HISTORIQUE"
 * Correction bug affichage d�faut gfci
 * AMP_MAX >= AMP >= AMP_RED1 >= AMP_RED2
 * Correction bug sur LED Bouton (non clignotement pendant la charge)

07/04/2014	:	0.2e
 * Ajout capteurs non g�r�s sur Mynetmemo
 * Affichage des valeurs dans Mynetmemo

25/03/2014	:	0.2d
 * Correction bug cmd.html (�criture i2C)
 * Modification bug RAZ appui bouton au d�marrage
 * Affectations Mynetmemo effectu�es
 * GFCI, Compensation offset de l'ampli-op
 * Int�gration modif Olivier Masse -> Correction casse pour utlisation Linux/Windows

17/03/2014	:	0.2c
 * Elagage sections "ADTEK"

09/01/2013	:	0.2a
 * Projet fonctionnel sur la charge

16/12/2013	:	0.1a
* D�marrage projet


*/





