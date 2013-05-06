#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_


/**************************** Declarations *******************************/

#define CORRECT		8

#define VM1       (1 << 2)  /* PORTC */
#define S11      (1 << 0)
#define S12      (1 << 1)
#define VM2       (1 << 7)
#define S21      (1 << 5)
#define S22      (1 << 6)
#define MSK_MOTEURS (VM1 | VM2 | SM11 | SM12 | SM21 | SM22)

/* Masque des servos */
#define SERVO1	4
#define SERVO2	5
//#define SERVO3	6
//#define SERVO4	7


/* Masque des actionneurs */
#define POMPE	4
#define CHOIX	1
#define SYNCHR	0

/* GP2 */
#define REF_GP2	500

#define VMAX 100
#define VM 1        //vitesse moyenne en m.s⁻¹
#define TP_180 5000 //temps pour un tour complet en ms

/********************* Variables Globales **************************/

extern volatile unsigned char RCMotD;
extern volatile unsigned char RCMotG;
extern volatile unsigned char MavtD;
extern volatile unsigned char MavtG;
extern volatile unsigned char ComptD;
extern volatile unsigned char ComptG;
//extern volatile unsigned char VitD;
//extern volatile unsigned char VitG;

extern unsigned char temps_max,compt;
extern volatile unsigned char asserv;
extern volatile unsigned int compt_01s;
extern volatile unsigned char compt1,compt2;



typedef enum sens_{
  ARRET,
  AVANCE,
  RECULE,
  DROITE,
  GAUCHE
} sens;

typedef enum cote_{
  ROUGE,
  BLEU
} cote;

#endif
