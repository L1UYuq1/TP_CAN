// ----------------------------------------------------------------------------- 
// Nom Fichier : can.c                                             
// Fonction : Programme d'émission et réception de trames CAN sur bus CAN
//            avec bibliotheque INFINEON AP292201              
// Auteur   : Pascal Berthou  & Agnan de Bonneval		
// Date     : janvier 2010                                           
// -----------------------------------------------------------------------------


// -------------------AVANT TOUTE CHOSE, VOUS DEVEZ IMPERATIVEMENT : -----------
//  1) INDIQUER VOS 
// 	- NOMS
// 	- Numéro de COMPTE
//		- DATE                                            
//	 2) RENOMMER ce fichier en :  can.c
//  3) L'ADAPTER selon les besoins de la manipulation.                                     
// -----------------------------------------------------------------------------


// Ces includes seront à déplacer ou supprimer selon la structuration en fichier
// choisie pour les programmes d'application
#include <c167.h>
#include <gnutrap.h>
#include <can_16x.h>
#include "commc167.h"



// ----Petit lexique
//   		- MO : Message OBJET
//

// ---- Constantes GENERIQUES pour l'initialisation du bus CAN -------
#define CAN_BAUDRATE 	500	// Baud rate (vitesse du bus) : 500 Kbps
#define CAN_IE 			0		// Interruptions CAN inactives

// ---- Constantes GENERIQUES (potentiellement) pour initialisation des MO -----
#define CAN_XTD_BIT		0     // Taille des identifiants CAN : sur 11 bits
#define CAN_TXIE_BIT   	0		// Génération d'interruptions d'EMISSION   : NON 
#define CAN_RXIE_BIT   	0		// Génération d'interruptions de RECEPTION : NON

// ---- Constantes spécialisees pour chaque Message Objet particulier ----------
#define M01_CAN_ID		0x002 // Valeur de l'IDENTIFIFANT CAN choisi pour
				      // Message Objet particulier (ex. : ici, MO n°1)
#define M01_CAN_DIR_BIT		1  // "DIRECTION" du M0 : 
										//		- RECEPTION : 0		EMISSION : 1		
#define M01_CAN_DLC			1  // Nombre d'octets de DONNES dans la trame CAN
					   // (DLC : Data Lenght Code)



// ---- Les fonctions de la bibliotheque a developper -------------------------- 
//     		(0) CAN_init  		: initialisation du module CAN et des MO
//     		(1) CAN_send  		: EMISSION  d'une trame de DONNEES 
//     		(2) CAN_receive	: RECEPTION d'une trame de DONNEES
//     		(3) CAN_reqremote	: EMISSION  d'une trame de REQUETTE 
//     		(4) CAN_setremote	: "RECEPTION"  d'une trame de REQUETTE 
//					  ET  "RENVOI" d'une trame de DONNEES
// -----------------------------------------------------------------------------



// ------ La fonction  CAN_init() ----------------------------------------------
//
//  Initialise le module CAN et les MO: vitesse, ..., parametres des M0, ...   		        
//  Remarque : pour la partie definition des MO, cette fonction depend du role 
//  de chaque noeud CAN (elle donc specialisee pour chaque noeud) -> il vaut 
//  mieux ne pas l'inclure dans la bibliotheque         
// -----------------------------------------------------------------------------

void CAN_init()
{
	// Initialisation du module CAN
 	init_can_16x(CAN_BAUDRATE,0,0,0);
	// Initialisation des Messages Objets 
	def_mo_16x(1,0,0x111,1,2,0,0);
    def_mo_16x(2,0,0x555,0,2,0,0);
	// - ces initialisations sont SPECIFIQUES a l'abonne considere
	// - iL vaut mieux les placer dans le code de chaque abonne

 
}


// ------ La fonction  CAN_send(int NumMO, char *p, int size) ------------------  
//  
// Emettre une trame CAN de DONNEES via un MO : Charge une donnée a émettre   
// puis envoie une trame de DONNEES. 
//  - paramètres :	NumMO [in]: numéro du message objet utilisé, 
//		    	p     [in]: pointe sur la donnée à envoyer,
//		    	size  [in]: longueur du message (nbr d'octets de données) 
//  - valeur rendue :   1 si la transmission a été effectuée, 
//		       	-1 si erreur 
// -----------------------------------------------------------------------------




int CAN_send(int NumMO, char *p, int size)
{

        /* Define message object: MO-number, xtd, id, dir, dlc, TXIE, RXIE 
/* incan16x.c */


ld_modata_16x(NumMO, p);
        /* load data bytes of a message object (1..14) */
/* rdm1516x.c */

send_mo_16x(NumMO);

return 1024 ;
}

// ------ La fonction  CAN_receive(int NumMO, char *p) -------------------------  
//  
// Recevoir une trame CAN de DONNEES via un MO : VERIFIE si une trame de DONNEES  
// est arrivée, et si oui, retourne un pointeur sur les DONNEES recues. 
// Attention cete fonc// ------ La fonction  CAN_receive(int NumMO, char *p) -------------------------  
//  
// Recevoir une trame CAN de DONNEES via un MO : VERIFIE si une trame de DONNEES  
// est arrivée, et si oui, retourne un pointeur sur les DONNEES recues. 
// Attention cete fonction est non blocante
//   - paramètres :	NumMO [in] :  numéro du message objet utilisé, 
// 		     	p     [out]:  pointe sur la donnée recue
//   - valeur rendue :  la longeur du message (longueur qui est >0), 
// 			0 si pas de message, 
// 		       	-1 si erreur 
// -----------------------------------------------------------------------------



int CAN_receive(int NumMO, char *p)
{ 
	while(check_mo_16x(NumMO)==0);
	rd_modata_16x(NumMO, p);
	
return 1024 ;
}


// ----------------------------------------------------------------------------

int main()
{
int data;
		char message_recu[16];

	CAN_init();
	init_ASC0_384();
	//CAN_send(1,"Z",1);
	puts_console("coucou\n");

while(1)
{
    data= CAN_receive(2,message_recu);
	
	message_recu[2]=0;
	printf_entier_console("val:%s\n",message_recu);
}
return 0 ;

}