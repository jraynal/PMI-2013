#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_


/**************************** Declarations *******************************/

#define VM1       (1 << 2)  /* PORTC */
#define SM11      (1 << 0)
#define SM12      (1 << 1)
#define VM2       (1 << 7)
#define SM21      (1 << 5)
#define SM22      (1 << 6)
#define MSK_MOTEURS (VM1 | VM2 | SM11 | SM12 | SM21 | SM22)

#define SERVO1    (1 << 0)  /* PORTD */
#define SERVO2    (1 << 1)
#define SERVO3    (1 << 2)
#define SERVO4    (1 << 3)
#define MSK_SERVOS (SERVO1 | SERVO2 | SERVO3 | SERVO4)

#define MAXT1         65535 /* 2¹⁶ */
#define MAXT02        255   /* 2⁸ */


#define CURSOR_PWM 180
#define PRESCALER 0x02

#define CURSOR_SERVO MAXT1 - 1536
#define PRESCALER_SERVO 0x04

#define VM 1        //vitesse moyenne en m.s⁻¹
#define TP_180 5000 //temps pour un tour complet en ms

extern volatile uint16_t RCMotD;
extern volatile uint16_t RCMotG;
extern volatile uint16_t RCser ;
extern volatile uint8_t MavtD;
extern volatile uint8_t MavtG;
extern volatile uint16_t cpts = 0;
extern volatile uint16_t pwm_bit_down = 0;

typedef enum sens_ {
  AVANT=0,
  ARRIERE,
  DROITE,
  GAUCHE
} sens;


#endif
