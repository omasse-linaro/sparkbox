#ifndef _PAC_H
    #define _PAC_H          
   
   // Prototypes fonctions publiques
   void Commande_PAC_ON(void);
   void Commande_PAC_OFF(void);
   void Commande_CIRCULATEUR1_ON(void);
   void Commande_CIRCULATEUR1_OFF(void);
   unsigned char Relais(unsigned char no_relais, unsigned char etat_relais);
   unsigned char Etat_Relais(unsigned char no_relais);
   unsigned char Etat_Pac(void);
   unsigned char Etat_Releve(void);
   unsigned char Etat_Releve_Ptec(void);
  

#endif

