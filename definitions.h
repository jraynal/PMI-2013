#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_


/**************************** Declarations *******************************/

#define CORRECT		8

#define AVANCE	1
#define RECULE	2
#define ARRET	0

#define ROUGE	0
#define BLEU	1


#define VM1       (1 << 2)  /* PORTC */
#define S11      (1 << 0)
#define S12      (1 << 1)
#define VM2       (1 << 7)
#define S21      (1 << 5)
#define S22      (1 << 6)
#define MSK_MOTEURS (VM1 | VM2 | SM11 | SM12 | SM21 | SM22)

/* #define SERVO1    (1 << 0)  /\* PORTD *\/ */
/* #define SERVO2    (1 << 1) */
/* #define SERVO3    (1 << 2) */
/* #define SERVO4    (1 << 3) */
/* #define MSK_SERVOS (SERVO1 | SERVO2 | SERVO3 | SERVO4) */

#define SERVO1	4
#define SERVO2	5
//#define SERVO3	6
//#define SERVO4	7


#define POMPE	4
#define CHOIX	1
#define SYNCHR	0

#define REF_GP2	500


#define MAXT1         65535 /* 2¹⁶ */
#define MAXT02        255   /* 2⁸ */


#define CURSOR_PWM 180
#define PRESCALER 0x02

#define CURSOR_SERVO MAXT1 - 1536
#define PRESCALER_SERVO 0x04

#define VM 1        //vitesse moyenne en m.s⁻¹
#define TP_180 5000 //temps pour un tour complet en ms

typedef enum sens_ {
  AVANT=0,
  ARRIERE,
  DROITE,
  GAUCHE
} sens;


#endif
