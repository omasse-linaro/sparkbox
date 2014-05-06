#include "Analogique.h"
#include "0_ADTEK.h"
#include <time.h>
#include <math.h>   // Uniquement pour la racine
#include "divers.h"

STRUCT_ANALOG 	Analog[NB_ANALOGIQUE];

#if defined(ADT07)
    #if defined (V0)
        STRUCT_CALIB 	Calibration[NB_ANALOGIQUE];
    #elif defined (V1)

    #else
        #error "Définir la version de carte ADT07"
    #endif
#endif

void Send_SPI3A(unsigned char val);

 /*************************************************************************************************
 *
 *      Init
 *
 **************************************************************************************************/
 

void analogiqueInit(void)
{
    unsigned char i;
    unsigned char temp;
    
    // Partie convertisseurs ADC processeur
    
    //AD1PCFG = 0xC400;                       // Configuration des entrées analogiques
    AD1CON1 = 0x20F4;                       // Configuration de l'horloge et du trigger. // 0010 0000 1111 0100
                                            //Entier 16 bits, Mode auto convert (démarre sur compteur à 0 et s'arrête en générant une IT),
    #if defined(ADT05)
        AD1CON2 = 0x040C;                   // Configuration des références : AVDD et AVSS,
    #elif defined(ADT07)
        AD1CON2 = 0x240C;                   // Référence externe vref+	//0010 0100 0000 1100
     #elif defined(ADT18)
        AD1CON2 = 0x240C;                   // Référence externe vref+	//0010 0100 0000 1100 
    #else
        #error "Definir une carte"
    #endif
                                            //Scan des entrées sélectionnées
                                            //Interruption à la 3e conversion */
                                            
    AD1CON3 = 0x000F;                       // Horloge la plus lente, environ 150Hz
    AD1CHS = 0x0000;                        // Configuration des canaux
    
    #if ( defined (ADT07) && defined (V0) ) || defined (ADT05)
        AD1PCFG = 0xC400;                       // Configuration des entrées analogiques 	// 1100 0100 0000 0000
        AD1CSSL = 0xC400;                       // Canaux à scanner     10, 14, 15
    #elif ( defined (ADT07) && defined (V1) )
        AD1PCFG = 0x0400;                       // Configuration des entrées analogiques	// 0000 0100 0000 0000
        AD1CSSL = 0x0400;                       // Canal à scanner     10
    #elif defined(ADT18)
        //AD1PCFG = 0x0040;                       // Configuration des entrées analogiques	// 0000 0000 0100 0000
		
		AD1PCFG = 0xFFBF;                       // Configuration des entrées analogiques	// 0000 0000 0100 0000
        AD1CSSL = 0x0040;                       // Canal à scanner     6
    #else
        #error "Configuration incorrecte"
    #endif                                       
    IFS1CLR = 2;                            // Effacement des interruptions
                                            // Configure ADC interrupt priority bits (AD1IP<2:0>) here, if
                                            // required. (default priority level is 4)
                                            
    //IPC6bits.AD1IP = 0b11;		            // IT priorité 3
	//IPC6bits.AD1IS = 0b01;		            // IT sous-priorité 1
                                            
    //IEC1SET = 2;                          // Autorise les interruptions
    AD1CON1SET = 0x8000;                    // Mise ON de l'ADC
    AD1CON1SET = 0x0004;                    // Démarre l'échantillonnage
    
    #if ( defined (ADT07) && defined (V0) )
        for (i=0; i < 2; i++)
        {
            mcp390x[i].v_low 	= Regul.Mcp[i].v_low;        
            mcp390x[i].v_fscale = Regul.Mcp[i].v_fscale;     
            mcp390x[i].vref 	= Regul.Mcp[i].vref;        
            mcp390x[i].r_top 	= Regul.Mcp[i].r_top;
            Analog[i+1].Etat	= CAPTEUR_DEMARRAGE;	
        }
    #endif
    
	// MCP3901 uniquement sur ADT07 et V1
    #if ( defined (ADT07) && defined (V1) )   
	    SPI1ACONbits.ON = 0;             // spi désactivé
		SPI1ACONbits.FRMEN = 0;          // frame spi disable   
	    
	    SPI1ACONbits.CKE = 0;
	    SPI1ACONbits.CKP = 1;
	    SPI1ACONbits.MSTEN = 1;          // master mode
	    SPI1ABRG = 0x20;
	    //SPI1ABRG = 0x80;
	    
	    SPI1ACONbits.ON = 1;             // spi activé
	    
	    // Sur V1 : 
	    //reset : B15
	    // CS : B14
	    
	    // CS
	    AD_CS_TRIS = 0;
	    AD_CS = 1;
	    
	    // Reset
	    AD_RESET_TRIS = 0;
	    AD_RESET = 0;      // Reset
	    
	    Delay10us(1);
	    
	    // Reset
	    AD_RESET = 1;      // Normal
	    Delay10us(1);
	    
	    // Séquence d'init
	    
	    // Reset ADC
	    // CS
	    AD_CS = 0;
	    SPI1ABUF = 0x16;                        // Config2 write
	    while ( SPI1ASTATbits.SPITBE == 0 );
	    Delay10us(1);
	    
	    SPI1ABUF = 0xC1;                        // Config2 reset des deux adc et permet surtout l'écriture continue des paramètres au coup suivant et horloge externe
 
	    while ( SPI1ASTATbits.SPITBE == 0 );
	    Delay10us(5);
	    // CS
	    AD_CS = 1;
	    
	    Delay10us(1);
	    // CS
	    AD_CS = 0;
	      
	    SPI1ABUF = 0x0E;                        // Phase write
	    while ( SPI1ASTATbits.SPITBE == 0 );
	    Delay10us(1);
	    SPI1ABUF = 0x00;                        // Phase
	    while ( SPI1ASTATbits.SPITBE == 0 );
	    Delay10us(1);
        
        // Gain PT1000
        // 4 pour gamme normale
        // 2 pour gamme étendue
        // bit 0 : 0 = gamme normale, 1 : gamme étendue
        if ( Regul.Calib_Mcp.opt[0] & 1 )
            temp = 1;
        else
            temp = 2;
        
        if ( Regul.Calib_Mcp.opt[1] & 1 )
            temp |= 0x20;
        else
            temp |= 0x40;
            
        SPI1ABUF = temp;
            
	    //SPI1ABUF = 0x00;                        // Gain
        //SPI1ABUF = 0x21;                        // Gain * 2       gamme étendue    
	    //SPI1ABUF = 0x42;                        // Gain * 4       ADT07 normale
	    //SPI1ABUF = 0x63;                        // Gain * 8
        
	    while ( SPI1ASTATbits.SPITBE == 0 );
	    Delay10us(1);
	    SPI1ABUF = 0xF0;                        // Status/Comm    1111  0000 devrait être 1110 0000 E0   autorisation de la lecture continue
	    while ( SPI1ASTATbits.SPITBE == 0 );
	    Delay10us(1);
	    SPI1ABUF = 0x10;                        // Config1
	    //SPI1ABUF = 0x1C;
	    while ( SPI1ASTATbits.SPITBE == 0 );
	    Delay10us(1);
	    SPI1ABUF = 0x0C;                        // Config2              autorisation conversion
	    while ( SPI1ASTATbits.SPITBE == 0 );
	    Delay10us(5);
	    
	    // CS
	    AD_CS = 1;
	    
        for (i=0; i < 2; i++)
        {
            Analog[i+1].Etat	= CAPTEUR_DEMARRAGE;
               
            Regul.Calib_Mcp.valid[0] = 0;
            Regul.Calib_Mcp.valid[1] = 0;
        }
    #endif
    // MCP3903 uniquement sur ADT18---------------------------------------------
    #if defined (ADT18)   
    	// Attention, sur l'ADT18 le SPI est partagé avec le SSTVF016 . Il faut que les paramétres du SPI soit identiques et <= 10Mhz pour le MCP
	    SPI3ACONbits.ON = 0;             // spi désactivé
		SPI3ACONbits.FRMEN = 0;          // frame spi disable   	    
	    SPI3ACONbits.CKE = 0;
	    SPI3ACONbits.CKP = 1;
	    SPI3ACONbits.MSTEN = 1;          // master mode
	    SPI3ABRG = 3;	// BRG=3 = 10Mhz Clock = (PeripheralClock/(2*(BRG+1)))
	    SPI3ACONbits.ON = 1;             // spi activé
	    
	    // CS
	    AD_CS_TRIS = 0;
	    AD_CS = 1;
	    
	    // Reset
	    AD_RESET_TRIS = 0;
	    AD_RESET = 0;      // Reset
	    Delay10us(1);
	    
	    // Reset
	    AD_RESET = 1;      // Normal
	    Delay10us(1);
	    
	    // Séquence d'init MCP3903

		/*
		// CONFIG (RESET ADC)	    
	    AD_CS = 0;                     
	    Send_SPI3A(0x14); 	// Config write
	    Send_SPI3A(0xFC); 	// 1111 1100       
	    Send_SPI3A(0x0F);	// 0000 1111                       
 		Send_SPI3A(0xD1); 	// 1101 0001                        
 		
	    // PHASE
	    AD_CS = 1;
	    Delay10us(1);
	    AD_CS = 0;
	    Send_SPI3A(0x0E);	// Phase write
	   	Send_SPI3A(0x00);                       
        Send_SPI3A(0x00);                       
	   	Send_SPI3A(0x00);
		*/

		// CONFIG (RESET ADC)	    
	    AD_CS = 0;                     
	    Send_SPI3A(0x54); 	// Config write
	    Send_SPI3A(0xFC); 	// 1111 1100       
	    Send_SPI3A(0x0F);	// 0000 1111                       
 		Send_SPI3A(0xD1); 	// 1101 0001                        
 		AD_CS = 1;
	    Delay10us(1);
		
	    // PHASE
	    AD_CS = 0;
	    Send_SPI3A(0x4E);	// Phase write
	   	Send_SPI3A(0x00);                       
        Send_SPI3A(0x00);                       
	   	Send_SPI3A(0x00);  		
	   	AD_CS = 1;
	    Delay10us(1);
		
		/*
        // Gain PT1000: 4 pour gamme normale, 2 pour gamme étendue | bit 0 : 0 = gamme normale, 1 : gamme étendue
        if ( Regul.Calib_Mcp.opt[0] & 1 )	temp = 1;
        else					            temp = 2;
        if ( Regul.Calib_Mcp.opt[1] & 1 )
            temp |= 0x20;					//SPI3ABUF = 0x00;                        // Gain
        else								//SPI3ABUF = 0x21;                        // Gain * 2       gamme étendue    
            temp |= 0x40;					//SPI3ABUF = 0x42;                        // Gain * 4       ADT07 normale
            								//SPI3ABUF = 0x63;                        // Gain * 8
        Send_SPI3A(temp);
	    Send_SPI3A(temp);
		Send_SPI3A(temp);
		// Status/Comm          autorisation de la lecture continue
	    Send_SPI3A(0xC0);	//1100 0000
	    Send_SPI3A(0x40);	//0100 0000
	    Send_SPI3A(0x00);   //0000 0000                     
	    //CONFIG
	    Send_SPI3A(0x00);	//0000 0000
	    Send_SPI3A(0x0F);	//0000 1111
	    Send_SPI3A(0xD0);	//1101 0000
		*/

		// Gain PT1000: 4 pour gamme normale, 2 pour gamme étendue | bit 0 : 0 = gamme normale, 1 : gamme étendue
        if ( Regul.Calib_Mcp.opt[0] & 1 )	temp = 1;
        else					            temp = 2;
        if ( Regul.Calib_Mcp.opt[1] & 1 )
            temp |= 0x20;					//SPI3ABUF = 0x00;                        // Gain
        else								//SPI3ABUF = 0x21;                        // Gain * 2       gamme étendue    
            temp |= 0x40;					//SPI3ABUF = 0x42;                        // Gain * 4       ADT07 normale
            								//SPI3ABUF = 0x63;                        // Gain * 8
		AD_CS = 0;
		Send_SPI3A(0x50);
		/*
        Send_SPI3A(temp);
	    Send_SPI3A(temp);
		Send_SPI3A(temp);
		*/
		Send_SPI3A(0x22);		// Gain * 4
		Send_SPI3A(0x22);		// Gain * 4
		Send_SPI3A(0x22);		// Gain * 4
		
		AD_CS = 1;
	    Delay10us(1);
		
		// Status/Comm          autorisation de la lecture continue
		AD_CS = 0;
		Send_SPI3A(0x52);
	    Send_SPI3A(0xC0);	//1100 0000
	    Send_SPI3A(0x40);	//0100 0000
	    Send_SPI3A(0x00);   //0000 0000
		AD_CS = 1;
	    Delay10us(1);
		
	    //CONFIG
		AD_CS = 0;
		Send_SPI3A(0x54);
	    //Send_SPI3A(0x00);	//0000 0000
	    //Send_SPI3A(0x0F);	//0000 1111
	    //Send_SPI3A(0xD0);	//1101 0000

		Send_SPI3A(0x00);	//0000 0000
	    Send_SPI3A(0x00);
	    Send_SPI3A(0x01);
		
	    AD_CS = 1;
	    Delay10us(1);
		
		
		// Relecture CONFIG, pour test !
		AD_CS = 0;
		Send_SPI3A(0x55);
	    //Send_SPI3A(0x00);	//0000 0000
	    //Send_SPI3A(0x0F);	//0000 1111
	    //Send_SPI3A(0xD0);	//1101 0000

		Send_SPI3A(0x00);	// Valeurs sans importance
	    Send_SPI3A(0x01);
	    Send_SPI3A(0x02);
		Send_SPI3A(0x03);
		
	    AD_CS = 1;
	    Delay10us(1);
		
	    
        for (i=0; i < 6; i++)
        {
            Analog[i+1].Etat	= CAPTEUR_DEMARRAGE;
               
            Regul.Calib_Mcp.valid[0] = 0;
            Regul.Calib_Mcp.valid[1] = 0;
        }
    #endif
}




/*********************************************************************************************************************************
*
*   Résolution de l'équation du second degré a x² + b x + c = 0
*   
*   Calcul du discriminant      dicriminant = b² - 4ac
*
*   Pas de solution si discriminant négatif
*   Solution unique si discriminant nul : solution = -b/(2a)
*   Deux solutions si discriminant positif :    solution_1 = ( -b - racine(discriminant) ) / ( 2a)
*                                               solution_2 = ( -b + racine(discriminant) ) / ( 2a)
*
*   Version spécifique à la résolution PT1000
*       R = R0 ( 1 + alpha * T + beta * T² )
*           R0 = 1000
*           alpha = 3.9083e-3
*           beta = -5.7750e-7
*           T en degrés Celcius
*           Précise de -50°C à +320°C
*           La solution est solution_2
*       Equation simplifiée : R0 beta T² + R0 alpha T + (R0 - R) = 0
*
**********************************************************************************************************************************/

float pt1000toTemp(float res_PT1000)
{
    // define écrits comme cela ne passent pas en compilation !
    //#define a   -5.7750e-4
    //#define b   3.9083
    //#define R0  1000
    
    float data;
    
    // Calcul du discriminant
    //data = b * b - 4 * a * (R0 - res_PT1000);
    data = 15.27480889 + 2.31e-3 * (1000 - res_PT1000);
    
    // Protection si erreur en amont dans la valeur transmise
    if (data >= 0)
        data = sqrt(data);
    
    // Calcul de la solution valide
    //data = ( -b + data ) / ( 2 * a );
    data = ( 3.9083 - data ) / ( 1.155e-3 );
    
    return data;
}

/*********************************************************************************************************************************
*
*       Conversion de la valeur ADC en résistance
*       Mise à jour des 3 paramètres à partir de 3 points fixes si demandé
*
*       Résolution du système de 3 équations à 3 inconnues
*       On nomme T résistance de la PT1000, R la résistance de source équivalente et G le gain, T_x et A_x représentent les 3 mesures
*       
*       On considère que l'on a ADC = G * (Vref * RT/(RT + RS) - Offset)
*
*       En développant ADC = G * Vref * RT/(RT + RS) - G * Offset
*
*       On va simplifier l'écriture en A = G * T / ( T + R ) - Offset       ****** Formule de base **********
*
*       On élimine l'offset par différence
*
*       A3 - A1 = G * [ T3/(R + T3) - T1/(R + T1) ] = G[T3(R+T1)-T1(R+T3)]/[(R+T1)(R+T3)]
*
*       A2 - A1 = G * [ T2/(R + T2) - T1/(R + T1) ] = G[T2(R+T1)-T1(R+T2)]/[(R+T1)(R+T2)]
*
*       On élimine G par division
*
*       (A3-A1)/(A2-A1) = [T3(R+T1)-T1(R+T3)]/[(R+T1)(R+T3)] / [T2(R+T1)-T1(R+T2)]/[(R+T1)(R+T2)]
*                       = (T3-T1)(R+T2)/(T2-T1)(R+T3)
*
*       On simplifie l'écriture
*
*       A31/A21 = T31(R+T2)/[ T21(R+T3)]
*
*       On en tire
*
*       R = (T21*T3*A31-T31*T2*A21)/(A21*T31-A31*T21)      ***** Calcul de la résistance source *********
*
*       On avait
*
*       A31 = G [ T3/(R+T3) - T1/(R+T1) }
*
*       On en tire
*
*       G = A31*(R+T3)(R+T1)/[T3(R+T1)-T1(R+T3)]            ***** Calcul du gain **********
*
*       De la formule de base, on tire
*
*       Offset = G*T/(R+T) - A                              ***** Calcul de l'offset *********
*
*       T = R*(A + Offset) / [G - Offset - A]               ***** Calcul de la résistance mesurée ********
*
**********************************************************************************************************************************/

float adcToRes(short adc, unsigned char voie, BOOL update)
{
    // 3 valeurs fixes qui caractérisent l'étage de conversion
    static float gain[2];
    static float offset[2];
    static float res_source[2];
    
    // valeur de résistance calculée
    static float pt1000;
    
    
    if ( !Regul.Calib_Mcp.valid[voie] || update )
    {
        float T1, T2, T3;
        float A1, A2, A3;
        
        float numerateur;
        float denominateur;
        
        // Rappel : toutes les résistances d'étalonnages sont données en x10
        T1 = ((float) Regul.Calib_Mcp.res[0] ) /10;
        T2 = ((float) Regul.Calib_Mcp.res[1] ) /10;
        T3 = ((float) Regul.Calib_Mcp.res[2] ) /10;
        
        A1 = Regul.Calib_Mcp.Channel[voie].adc[0];
        A2 = Regul.Calib_Mcp.Channel[voie].adc[1];
        A3 = Regul.Calib_Mcp.Channel[voie].adc[2];
        
        // résistance source
        numerateur = (T2-T1)*T3*(A3-A1)-(T3-T1)*T2*(A2-A1);
        denominateur = (A2-A1)*(T3-T1)-(A3-A1)*(T2-T1);
        
        if ( denominateur != 0 )
            res_source[voie] = numerateur / denominateur;
         
        // gain
        numerateur = (A3-A1)*(res_source[voie]+T3)*(res_source[voie]+T1);
        denominateur = T3*(res_source[voie]+T1)-T1*(res_source[voie]+T3);
        
        if ( denominateur != 0 )
            gain[voie] = numerateur / denominateur;
        
        // Offset
        denominateur = res_source[voie] + T2;
        
        if ( denominateur != 0 )
            offset[voie] = ( ( gain[voie] * T2 ) / denominateur )  - A2;
        
        Regul.Calib_Mcp.valid[voie] = 0x01;
    }
    
    // calcul de la valeur ohmique
    pt1000 = res_source[voie]*(adc + offset[voie]) / (gain[voie] -offset[voie] - adc);
    return pt1000;
}





void analogiqueTask(void)
{ 
    static unsigned last_cpt1s;
    volatile unsigned char temp;
    unsigned char i;
    
    // Traitement des ADC processeur
    unsigned char cpt_analog;
    
    static unsigned int lastTime;
    int time;
    
    static int readAdc[3] = {0};
    
    static int lowPassMcp[6];
    int tempFilter;
    
    unsigned char nbAdcPic;
    
    // En fait, il faudrait tester que l'échantillonnage soit bien fini. Si on lit trop vite en relançant le suivant, on lit toujours la même valeur
    //if ( last_cpt1s < cpt1s )
    
    time = TickGet();
    if ( ( time - lastTime ) >= ( TICK_SECOND / 10 ) )             // Lecture à 100Hz pour faciliter le filtrage
	{
        lastTime = time;
        
        readAdc[0] = ADC1BUF0;
	    #if ( defined (ADT07) && defined (V0) ) || defined (ADT05)
	        readAdc[1] = ADC1BUF1;
	        readAdc[2] = ADC1BUF2;
	        nbAdcPic = 3;
	    # else  // 	ADT07 V1 et ADT18
	        nbAdcPic = 1;
	    #endif
    
        for ( i = 0; i < nbAdcPic; i++ )
        {
            // Filtrage passe-bas
            tempFilter = readAdc[i];
            tempFilter -= Analog[i].adc;            // x(n) - y(n-1)
            //tempFilter *= K_Filtre;               // en Q1.15, mais peut importe finalement
            tempFilter *= 0x400;                   // k = 0x400 / 2^15 soit 1024 / 32768 soit 1/32
            tempFilter >>= 15;                      // pour repasser au format d'origine, mais peu importe en fait
            tempFilter += Analog[i].adc;            // y(n-1) + k [x(n) - y(n-1)]           et k = 1 /(fs * tau)        fs = 100, donc tau = k / fs,  et fc = 1/(2 * pi * tau) = fs * k / ( 2* pi ) = 0.5Hz
            Analog[i].adc = tempFilter;
        }
        
        // Relance l'échantillonnage suivant
        AD1CON1SET = 0x0004;	// 0000 0000 0000 0100
        
	    // Partie spécifique ADT07 V1 avec MCP3901 ---------------------------------------------------------------------------------------------------------------
	    // ATTENTION : EN CONTINUOUS READ, le nombre d'octets lus pour chaque ADC dans une boucle dépend de la résolution sélectionnée !!!
	    #if ( defined (ADT07) && defined (V1) )
		    SPI1ABRG = 0x20;
		    
		    AD_CS = 0;
		    last_cpt1s = cpt1s;
		         
		    SPI1ABUF = 0x01;
		    while ( SPI1ASTATbits.SPITBE == 0 );
		    Delay10us(1);
		        
		    SPI1ASTATCLR = 0x40;      // Clear Overflow Flag Bit
		
		    temp = SPI1ABUF;
		        
		    for ( i = 0; i < 5; i++ )       // On lit une fois de plus pour tenir compte du retard
		    {
		        SPI1ABUF = 0xFF;
		        temp = SPI1ABUF;
		        while ( SPI1ASTATbits.SPITBE == 0 );
		        Delay10us(1);
		            
		        switch ( i )
		        {
		            case 1 :
		                mcp390x[0].adc.field.msb = temp;
		                break;
		                    
		            case 2 :
		                mcp390x[0].adc.field.lsb = temp;
		                break;
		                    
		            case 3 :
		                mcp390x[1].adc.field.msb = temp;
		                break;
		                    
		            case 4 :
		                mcp390x[1].adc.field.lsb = temp;
		                break;
		                    
		            default :
		                break;
		        }
		            
		    }
		        
		    Delay10us(5);
		    AD_CS = 1;
	            
	        for (i = 0; i < 2; i++ )
		    { 
	            // Filtrage passe-bas
	            tempFilter = mcp390x[i].adc.value;
	            tempFilter -= lowPassMcp[i];            // x(n) - y(n-1)
	            //tempFilter *= K_Filtre;               // en Q1.15, mais peut importe finalement
	            tempFilter *= 0x400;                   // k = 0x400 / 2^15 soit 1024 / 32768 soit 1/32
	            tempFilter >>= 15;                      // pour repasser au format d'origine, mais peu importe en fait
	            tempFilter += lowPassMcp[i];            // y(n-1) + k [x(n) - y(n-1)]           et k = 1 /(fs * tau)        fs = 100, donc tau = k / fs,  et fc = 1/(2 * pi * tau) = fs * k / ( 2* pi ) = 0.5Hz
	            lowPassMcp[i] = tempFilter;
	        }
	    #endif

	    // Partie spécifique ADT18 avec MCP3903 ---------------------------------------------------------------------------------------------------------------
	    // ATTENTION : EN CONTINUOUS READ, le nombre d'octets lus pour chaque ADC dans une boucle dépend de la résolution sélectionnée !!!
	    #if defined (ADT18)
		  //  On suppose le SPI bien configuré
		    AD_CS = 0;
		    last_cpt1s = cpt1s;
		       
		    //SPI3ABUF = 0x01;
		    Send_SPI3A(0x41); 
			//SPI3ABUF = 0x41;while ( SPI3ASTATbits.SPITBE == 0 );Delay10us(1);
		        
		    SPI3ASTATCLR = 0x40;      // Clear Overflow Flag Bit
		
		    temp = SPI3ABUF;
		        
		    for ( i = 0; i < 13; i++ )       // On lit une fois de plus pour tenir compte du retard
		    {
			    
			    	while ( SPI3ASTATbits.SPITBE == 0 ); 
					SPI3ABUF = 0xFF;
					while ( !SPI3ASTATbits.SPIRBF); 
 					temp = SPI3ABUF;
		        //SPI3ABUF = 0xFF;
		        //temp = SPI3ABUF;
		        //while ( SPI3ASTATbits.SPITBE == 0 );
		        //Delay10us(1);
		            
		        switch ( i )
		        {
		            case 1 :
		                mcp390x[0].adc.field.msb = temp;
		                break;		                    
		            case 2 :
		                mcp390x[0].adc.field.lsb = temp;
		                break;	                    
		            case 3 :
		                mcp390x[1].adc.field.msb = temp;
		                break;	                    
		            case 4 :
		                mcp390x[1].adc.field.lsb = temp;
		                break;	                
		            case 5 :
		                mcp390x[2].adc.field.msb = temp;
		                break;	                    
		            case 6 :
		                mcp390x[2].adc.field.lsb = temp;
		                break;    
		            case 7 :
		                mcp390x[3].adc.field.msb = temp;
		                break;              
		            case 8 :
		                mcp390x[3].adc.field.lsb = temp;
		                break;  
		            case 9 :
		                mcp390x[4].adc.field.msb = temp;
		                break;	                    
		            case 10 :
		                mcp390x[4].adc.field.lsb = temp;
		                break;    
		            case 11 :
		                mcp390x[5].adc.field.msb = temp;
		                break;              
		            case 12 :
		                mcp390x[5].adc.field.lsb = temp;
		                break;          
		                    
		            default :
		                break;
		        }       
		    }
		    AD_CS = 1;
	          
	        // Filtrage passe-bas   
	        for (i = 0; i < 6; i++ )
		    { 
	            tempFilter = mcp390x[i].adc.value;
	            tempFilter -= lowPassMcp[i];            // x(n) - y(n-1)
	            //tempFilter *= K_Filtre;               // en Q1.15, mais peut importe finalement
	            tempFilter *= 0x400;                   // k = 0x400 / 2^15 soit 1024 / 32768 soit 1/32
	            tempFilter >>= 15;                      // pour repasser au format d'origine, mais peu importe en fait
	            tempFilter += lowPassMcp[i];            // y(n-1) + k [x(n) - y(n-1)]           et k = 1 /(fs * tau)        fs = 100, donc tau = k / fs,  et fc = 1/(2 * pi * tau) = fs * k / ( 2* pi ) = 0.5Hz
	            lowPassMcp[i] = tempFilter;
	        }
	    #endif

 
    }
         
    // Traitement lent
    if ( last_cpt1s < cpt1s )
    {
        // 1 -- On traite le premier capteur Analogique (solarimètre)
        Analog[0].Etat = CAPTEUR_OK;
        Analog[0].temperature = Analog[0].adc / 5; 		

        // 2 -- On traite les 2 entrées analogiques dédiées PT1000 sur convertisseur analogique traditionnel
        // Ou les 6 entrées PT1000 sur ADT18
        
    #if ( defined (ADT07) && defined (V0) ) || defined (ADT05)
        for (cpt_analog = 1; cpt_analog < NB_ANALOGIQUE; cpt_analog++)
        {     
            // ETAT CAPTEUR
             if (Analog[cpt_analog].adc == 0)		// Valeur au démarrage
            {
                Analog[cpt_analog].Etat = CAPTEUR_DEMARRAGE;
            }
            else if (Analog[cpt_analog].adc < 13) 	// Probablement un CC
            {
                Analog[cpt_analog].Etat = CAPTEUR_ERREUR;
            }
            else if (Analog[cpt_analog].adc > 1020)	// Capteur non connecté
            {
                Analog[cpt_analog].Etat = CAPTEUR_ABSENT;
            }
            else	// OK
            {
                Analog[cpt_analog].Etat = CAPTEUR_OK;
                
                Analog[cpt_analog].temperature = ( ( Analog[cpt_analog].adc * Regul.Calib[cpt_analog].delta ) / 1023 ) +  Regul.Calib[cpt_analog].offset ;
            }  		
        }
    #endif

    #if ( defined (ADT07) && defined (V1) )
        for (i = 0; i < 2; i++ )
	    {
            //mcp390x[i].res_PT1000 = adcToRes( mcp390x[i].adc.value, i, FALSE );
            mcp390x[i].res_PT1000 = adcToRes( lowPassMcp[i], i, FALSE );
                
            mcp390x[i].temperature = pt1000toTemp( mcp390x[i].res_PT1000 );
                
            //Analog[i+1].adc = mcp390x[i].adc.value;
            Analog[i+1].adc = lowPassMcp[i];
                
            //Analog[i+1].temperature = (signed short) (mcp390x[i].temperature * 100);          // Overflow possible !
            // On teste donc avant le cast
            if ( mcp390x[i].temperature < 327.6 )
                Analog[i+1].temperature = (signed short) (mcp390x[i].temperature * 100);
            else
                Analog[i+1].temperature = 32767;
                
            // On teste si le capteur est en court circuit
            if (mcp390x[i].adc.value == -32768)
            {
            	Analog[i+1].Etat	= CAPTEUR_ERREUR;
            }
            // On teste si le capteur est absent
            else if (mcp390x[i].adc.value == 32767)
            {
            	Analog[i+1].Etat	= CAPTEUR_ABSENT;
            }
            // Capteur valide !
            else
            {
            	Analog[i+1].Etat	= CAPTEUR_OK;
            }	
        }                
	#endif
	
	#if defined (ADT018) // 6 Voies
        for (i = 0; i < 6; i++ )
	    {
            //mcp390x[i].res_PT1000 = adcToRes( mcp390x[i].adc.value, i, FALSE );
            mcp390x[i].res_PT1000 = adcToRes( lowPassMcp[i], i, FALSE );
                
            mcp390x[i].temperature = pt1000toTemp( mcp390x[i].res_PT1000 );
                
            //Analog[i+1].adc = mcp390x[i].adc.value;
            Analog[i+1].adc = lowPassMcp[i];
                
            //Analog[i+1].temperature = (signed short) (mcp390x[i].temperature * 100);          // Overflow possible !
            // On teste donc avant le cast
            if ( mcp390x[i].temperature < 327.6 )
                Analog[i+1].temperature = (signed short) (mcp390x[i].temperature * 100);
            else
                Analog[i+1].temperature = 32767;
                
            // On teste si le capteur est en court circuit
            if (mcp390x[i].adc.value == -32768)
            {
            	Analog[i+1].Etat	= CAPTEUR_ERREUR;
            }
            // On teste si le capteur est absent
            else if (mcp390x[i].adc.value == 32767)
            {
            	Analog[i+1].Etat	= CAPTEUR_ABSENT;
            }
            // Capteur valide !
            else
            {
            	Analog[i+1].Etat	= CAPTEUR_OK;
            }	
        }                
	#endif
    }
}



/******************************************************************************************************
*
*       Fonctions spécifiques potentiomètres numériques
*
*
*******************************************************************************************************/

#if ( defined (ADT07) && defined (V0) )
    unsigned char WriteWiperPot( unsigned char pot, unsigned char value )
    {
        // On se limite aux composants sur 8 bits, de 0 à 128
        unsigned char memory_address;
        unsigned char low_byte;
         
        memory_address = ( ( pot & 0x02 ) << 1 ) | ( pot & 0x02 ) | ( pot & 0x01 );        // adresses valides : 0, 1, 6, 7
        
        StartI2C1();	
        IdleI2C1();
        
        MasterWriteI2C1 ( FIXED_ADDRESS | 0 );
        IdleI2C1();
        
        if( I2C1STATbits.ACKSTAT )      // 0 si pas de ACK
            return 0;
               
        //MasterWriteI2C1( memory_address << 4 | bit_d8 );
        MasterWriteI2C1( memory_address << 4 );
        IdleI2C1();
        
        if( I2C1STATbits.ACKSTAT )      // 0 si pas de ACK
            return 0;
        
        //MasterWriteI2C1( low_byte );
        MasterWriteI2C1( value );
        IdleI2C1();
        
        if( I2C1STATbits.ACKSTAT )      // 0 si pas de ACK
            return 0;
        
        StopI2C1();	
        IdleI2C1();
        
        return 1; 
    }


    unsigned char ReadWiperPot( unsigned short pot, unsigned char * value )
    {
        unsigned char memory_address;
        unsigned short read_byte;
        unsigned char status = 1;       // 0 si erreur
        
        memory_address = ( ( pot & 0x02 ) << 1 ) | ( pot & 0x02 ) | ( pot & 0x01 );        // adresses valides : 0, 1, 6, 7
        
        unsigned char read[2];


        StartI2C1();	
        IdleI2C1();
        
        MasterWriteI2C1( FIXED_ADDRESS | 0 );
        IdleI2C1();
        
        if( I2C1STATbits.ACKSTAT )      // 0 si pas de ACK
            status = 0;
        
        MasterWriteI2C1( memory_address << 4 | 0x0C );
        IdleI2C1();
        
        if( I2C1STATbits.ACKSTAT )      // 0 si pas de ACK
            status = 0;
        
        RestartI2C1();	
        IdleI2C1();
        
        MasterWriteI2C1( FIXED_ADDRESS | 1 ); //transmit read command
        IdleI2C1();	
        
        if ( MastergetsI2C1(2, read, 1000) )        // 0 si pas d'erreur, sinon, nombre d'octets non lus
            status = 0;
        
        StopI2C1();	//Send the Stop condition
        IdleI2C1();	//Wait to complete
        
        *value = read[1];
        return status;
    }

    void IncWiperPot( unsigned char pot )
    {
        unsigned char adresse;
        
        adresse = ( ( pot & 0x02 ) << 1 ) | ( pot & 0x02 ) | ( pot & 0x01 );        // adresses valides : 0, 1, 6, 7

    }

    void DecWiperPot( unsigned char pot )
    {
        unsigned char adresse;
        
        adresse = ( ( pot & 0x02 ) << 1 ) | ( pot & 0x02 ) | ( pot & 0x01 );        // adresses valides : 0, 1, 6, 7

    }

    // reg : 0 à 1, registre
    void WriteDataPot( unsigned char reg, unsigned char value )
    {
        unsigned char adresse;
        
        if ( reg == 0 )
            adresse = 0x04;
        else
            adresse = 0x0A;      
    }

    unsigned short ReadDataPot( unsigned char reg )
    {

    }
#endif


void Send_SPI3A(unsigned char val)
{
	SPI3ABUF = val;
	while ( SPI3ASTATbits.SPITBE == 0 ); 
	Delay10us(1);
/*
	while ( SPI3ASTATbits.SPITBE == 0 ); 
	SPI3ABUF = val;
	while ( !SPI3ASTATbits.SPIRBF); 
*/
}

