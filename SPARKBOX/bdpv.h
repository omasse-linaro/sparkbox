#ifndef __BDPV_H
	#define __BDPV_H
	
	// ETATS UTILISES PENDANT LA TRANSMISSION TCP
	#define BDPV_DONE	0
	#define BDPV_START  1
	#define BDPV_SOCKET_OBTAINED 2
	#define BDPV_ATTENTE_REPONSE 3
	#define BDPV_DISCONNECT 4
	
	extern unsigned int probleme_envoi_bdpv;
	extern STRUCT_SOCKET_BD_CURL Bdpv_Socket;
	
	void Initialise_Bdpv(void);
	void Envoi_Donnees_Bdpv(unsigned char * capteur);
	void Process_Bdpv(void);
	void Process_Jour_Bdpv(void);
	
#endif


