/* Manip servomoteur */

/* -------------------- Cablage --------------------------- */
/* Commande moteur : Port 7.0  + Port 7:OFF                 */
/* Masse :           Masse                                  */
/* V. pot :          Entree Analogique 0                    */
/* -------------------------------------------------------- */


#include <c167.h>
#include <gnutrap.h>

int pw;

TRAP_noMD(0x3F,lecture_potard);
TRAP_noMD(0x23,affichage);

/*--------------------------------------------------------------*/
void affichage()
{
  char angle;

  angle=( char) (1850.0-0.32*pw);
  S0TBUF=angle;
  WAIT_UNTIL_BIT_SET(S0TBIR);
  CLR_SFRBIT(S0TBIR);
}

/*--------------------------------------------------------------*/
void init_UART()
{
  // 8 bits - no parity - 1 bit stop 
  S0CON=0x8011;
  S0BG=0x20;  /* 19200 bauds */
  /* emission*/
  SET_SFRBIT(P3.10);
  SET_SFRBIT(DP3.10);
}

/*--------------------------------------------------------------*/
void init_timer()
{// affichage toutes les 500 ms
  T3CON=0x0045;
  T4CON=0x0027;
  T3IC=0x48;
  T4=T3=26472;
}

/*--------------------------------------------------------------*/
#define LMAX 1023.0
int conversion(int lecture)
{
  float pwf;
  int pw;

  pwf= ( (19.4-1.8*lecture/LMAX)/20.0 )*6250.0;
  pw=(int) pwf;
  return pw;
}

/*--------------------------------------------------------------*/
void lecture_potard() /* entree 0 */
{
  int L;

  SET_SFRBIT(ADST);
  WAIT_UNTIL_BIT_SET(ADCIR);
  L=ADDAT & 0x3FF;
  CLR_SFRBIT(ADCIR);
  pw=conversion(L);
  PW0=pw;
}

/*--------------------------------------------------------------*/
void main()
{  
  ADCON=0x0000;
  PWMCON0=0x0111; 

  PWMCON1=0x0001;
  PWMIC=0x0048; 
  
  CLR_SFRBIT(P7.0);
  SET_SFRBIT(DP7.0);

  PP0=6250;
  pw=5780; /* 0 degres */
  PW0=pw;

  init_UART();
  init_timer();

  SET_SFRBIT(IEN);

  while(1);
}






