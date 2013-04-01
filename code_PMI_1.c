///////////////////////////////////////////////////////////////////////////
/*                                                                       */
/*           #########          ##       ###             ####            */
/*           ###     ##         ####    # ##              ##             */
/*           ###     ##         ## ##  #  ##              ##             */
/*           ########           ##   ##   ##              ##             */
/*           ###                ##        ##              ##             */
/*           ###                ##        ##              ##             */
/*           ###         ##     ##        ##      ##     ####            */
/*                                                                       */
///////////////////////////////////////////////////////////////////////////


/******************************  Auteurs  ********************************/
/*                                                                       */
/*                      JR -- petit coordinateur --                      */
/*                                                                       */
/*                                                                       */
/*                                                                       */
/*************************************************************************/

/************************** Dernière Modif *******************************/
/*                    le 30/03/2013        09:00                         */
/*************************************************************************/


/**************************** Commentaires *******************************/
/*                                                                       */
/*************************************************************************/


/****************************     TODO    ********************************/
/*            Interrutpion PWM                                           */
/*            Asservissement                                             */
/*            Mouvement servos                                           */
/*            Adaptation côté                                            */
/*                                                                       */
/*            Trajectoire                                                */
/*            Strategie                                                  */
/*                                                                       */
/*************************************************************************/

/****************************** Includes *********************************/

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>


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

#define CURSOR_PWM 180
#define PRESCALER 0x02

volatile uint16_t RCMotD;
volatile uint16_t RCMotG;
volatile uint16_t RCser ;
volatile uint8_t MavtD;
volatile uint8_t MavtG;


/************************ fonctions temporaires **************************/

void init_pwm( void ){
  /* Les moteurs ne doivent pas tourner */
  RCMotG = 0;
  RCMotD = 0;

  /* On fixe le départ du compteur pour régler la fréquence*/
  TCNT0 = CURSOR_PWM;
  TCNT2 = CURSOR_PWM;

  /* Moteur Gauche */
  OCR0  = CURSOR_PWM+10 ;
  TCCR0 = PRESCALER;
  /* Moteur Droit  */
  OCR2  = CURSOR_PWM+10 ;
  TCCR2 = PRESCALER;

  /*Autorise les interuption des clocks*/
  TIMSK |= 0xC3 ;
  sei();
}

uint8_t init_pins( void ){
  /* Pins de validation et de sens des moteurs en Output High */
  DDRC = MSK_MOTEURS;
  DDRD = MSK_SERVOS;

  /* Pins d'entrées des codeurs et autres capteur en Pull Up */
  PORTD = 0x30;
  DDRB  = 0x0;
  PORTB = 0x0F;
}

uint8_t departStrat( void ){
  /* Retrait de la tirette */
  //while( PINA && 1 << 0 ); 
  return 1;
}


/****************************    Setup    ********************************/

uint8_t setup( void ){
  init_pins();
  init_pwm();
  departStrat();
  return 0;
}

/***************************     loop     ********************************/

void loop( void ){
}

/***************************     Main     ********************************/

int main( void ){

  setup();
  while(1){
    loop();
  }
  return 0;
}

/* Interruption moteurs cc */
ISR( TIMER0_COMP_vect ){
  /**
   *  On coupe tout:
   *  Validation à 1
   *  Sens 1 à 1
   *  Sens 2 à 1
   **/
  PORTC |= VM1 | SM11 | SM12;
}

ISR( TIMER0_OVF_vect ){
  /**
   *  On alimente dans le sens de marche
   *  Validation 1
   *  Sens 1 à 1 ou 0
   *  Sens 2 à 1 ou 0
   **/
  TCCR0 = 0x00;
  TCNT0 = CURSOR_PWM;
  TCCR0 = PRESCALER;
  if (MavtD)
    PORTC &= ~SM11;
  else
    PORTC &= ~SM12;
}

ISR( TIMER2_COMP_vect ){
  /**
   *  On coupe tout:
   *  Validation à 1
   *  Sens 1 à 1
   *  Sens 2 à 1
   **/
  PORTC  |= VM2 | SM21 | SM22;
}

ISR( TIMER2_OVF_vect ){
  /**
   *  On alimente dans le sens de marche
   *  Validation 1
   *  Sens 1 à 1 ou 0
   *  Sens 2 à 1 ou 0
   **/

  TCCR2 = 0x00;
  TCNT2 = CURSOR_PWM;
  TCCR2 = PRESCALER;
  if (MavtG)
    PORTC &= ~SM21;
  else
    PORTC &= ~SM22;
}

