/* *************************************************************** */
/* Nom Fichier : CAN.c                                             */
/* Fonction : Programme d'emission et reception de trames sur bus  */
/*            CAN avec bibliotheque INFINEON AP292201              */
/* Auteur   : Pascal Berthou                                       */
/* Date     : 1/12/04                                              */
/* *************************************************************** */

#include <c167.h>
#include <gnutrap.h>
#include <can_16x.h>


/** Constantes d initialisation du bus CAN **/

#define CAN_BAUDRATE 1000 // Baud rate 1 Mbit/s
#define CAN_IE 0          // CAN interrupts enabled

#define CAN_XTD_BIT     0               /* uses 11 bit ID */
#define CAN_ID          0x002           /* 11-bit identifier of MO2 */
#define CAN_DIR_BIT     0               /* reception=0, transmission=1 */
#define CAN_DLC         0               /* data length = 0 bytes */
#define CAN_TXIE_BIT    0               /* gen. no transmit interrupts */
#define CAN_RXIE_BIT    0               /* gen. no receive interrupts */ 

#define CANID29(id) ((((unsigned long)(id) >> 21) & 0x000000ff) | (((unsigned long)(id) >> 5 ) & 0x0000ff00) | (((unsigned long)(id) << 11) & 0x00ff0000) | (((unsigned long)(id) << 27 )))

#define CANID11(id) (CANID29((unsigned long)(id) << 18))
#define CAN_setid(ch,val) id_ptr_16x(ch) = val;

/*!
  \brief : Initialise le module CAN
*/
void CAN_init()
{
  ADCON=0x0021;
  // Initialisation du module CAN
 

  // Initialisation des messages objets
 
}

/*!
   \brief : Verifie si un message est disponible et le retourne un pointeur dessus le cas echeant
   \param : channel [in]: numero du message objet, p [out] : pointe sur la donnee
   \return : la longeur du message (>0), 0 si pas de message, -1 si erreur
*/ 
int CAN_receive(int channel, char *p)
{

  // Verification du numero de MO
 
  // Verifie si le channel est en reception

  // Verifie si le MO contient un message recu
 
  // Chargement de la nouvelle donnee

  // Calcul de la longueur
}

/*!
  \brief : Envoi un message sur un channel donne
  \param : channel [in]: numero du message objet, p [in] : pointe sur la donnee, size [in] : longueur du message
  \return : 1 transmission effectuee, -1 si erreur
*/
int CAN_send(int channel, char *p, int size)
{
  return(1);
}

/*!
  \brief : Positionne la donnee a emettre pour une transmission automatique
  \param : channel [in]: numero du message objet, p [in] : pointe sur la donnee, size [in] : longueur du message
  \return : 1 positionnement effectue, -1 si erreur
*/
int CAN_setremote(int channel, char *p, int size)
{
  // idem Sent mais n'emmet pas la donnee
}

/*!
  \brief : envoi d'une deùande de transmission automatique
  \param : channel [in]: numero du message objet
  \return : 1 demande effectuee, -1 si erreur
*/
int CAN_reqremote(int channel)
{
  // L'unite doit etre positionee en reception
  // un message "vide" doit etre emis comme requete
}


  

  
