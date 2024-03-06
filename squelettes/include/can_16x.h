/***
 * CAN library declaration include file
 *   to be used in program, linked with -lcan_16x
 *   with static library libcan_16x.a
 *   (instead of including of AP2922 *.c files in sources)
 *
 * Marek Peca, LAAS, 12/2004
 *
 * included reg. def. from:
 **/

/*********************************************************************
 * Program name:	"CANR_16X.H"                                 *
 * Task:		Include file                                 *
 *			belonging to Siemens ApNote AP2922           *
 *			"'C' CAN Driver Routines for the C166 family"*
 *                                                                   * 
 * Last modifications:	April 28nd 1997                              *
 * Version:		1.0                                          *
 * Authors:		Axel Wolf,  SCI Cupertino                    *
 *			Dr. Jens Barrenscheen, HL MC PD, Munich      *
 *********************************************************************/


#ifndef CR /* registers */

/* Define CAN module control registers */

#define 	CR	*(unsigned char*) 0xef00
#define 	SR	*(unsigned char*) 0xef01
#define 	IR	*(unsigned char*) 0xef02
#define 	BTR	*(unsigned int *) 0xef04
#define 	GMS	*(unsigned int *) 0xef06
#define 	UGML	*(unsigned int *) 0xef08
#define 	LGML	*(unsigned int *) 0xef0a
#define 	UMLM	*(unsigned int *) 0xef0c
#define 	LMLM	*(unsigned int *) 0xef0e

#endif /* registers */

/* ----------------------------------- externals, prototypes: ------ */
extern unsigned int *id_ptr_16x[16];    /* pointer to message id's (UAReg) */
extern unsigned char *db0_ptr_16x[16];  /* pointer to 'databyte 0's */
extern unsigned int *msgctrl_ptr_16x[16];       /* ptr to msg. contrl. regs */
extern unsigned char *msgconf_ptr_16x[16];      /* ptr to msg. conf. regs */
extern unsigned char dir_bit_16x[16];   /* DIR bits MO 1...15 */
extern unsigned char xtd_bit_16x[16];   /* XTD bits MO 1...15 */
extern unsigned char dlc_16x[16];       /* data byte lengths MO 1...15 */
                                                                               
/** function declarations **/

/* chkbo16x.c */
unsigned char check_busoff_16x(void);
        /* check for bus off situation and recover if necessary */
/* chkmo16x.c */
unsigned char check_mo_16x(unsigned char nr);
        /* check for new data in MO 'nr' (1..14) and if so, return 1 */
/* chm1516x.c */
unsigned char check_mo15_16x(void);
        /* check for new data or remote frame in MO 15 and if so, return 1 */
/* cisr16x1.c -- nothing */
/* defmo16x.c */
void def_mo_16x(unsigned char nr, unsigned char xtd, unsigned long id,
        unsigned char dir, unsigned char dlc, unsigned char txie,
        unsigned char rxie);
        /* Define message object: MO-number, xtd, id, dir, dlc, TXIE, RXIE */
/* incan16x.c */
void init_can_16x(unsigned int baud_rate, unsigned char eie,
        unsigned char sie, unsigned char ie);
        /* Initialization of CAN-Module: (baud_rate, eie, sie, ie) */
/* ldmod16x.c */
void ld_modata_16x(unsigned char nr, unsigned char *upl_data_ptr);
        /* load data bytes of a message object (1..14) */
/* rdm1516x.c */
void rd_mo15_16x(unsigned char *mo15_db_ptr,
        unsigned long *mo15_id_ptr, unsigned char *mo15_dlc_ptr);
        /* read dlc, identifier and data from MO 15 of C167 (Basic CAN) */
/* rdmod16x.c */
void rd_modata_16x(unsigned char nr, unsigned char *downl_data_ptr);
        /* read data bytes from message object 'nr' (1..14) */
/* sndmo16x.c */
void send_mo_16x(unsigned char nr);
        /* Transmit message object 'nr' (1..14) */


/** END **/
