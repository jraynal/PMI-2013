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
/*                    le 28/03/2013        17:40                         */
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

#define VM1       (1 << 2)
#define SM11      (1 << 0)
#define SM12      (1 << 1)
#define VM2       (1 << 7)
#define SM21      (1 << 5)
#define SM22      (1 << 6)
#define F_CPU     16000000
#define CURSOR_PWM 180
#define PRESCALER 0x02

volatile uint16_t RCMotD;
volatile uint16_t RCMotG;
volatile uint16_t RCser ;
volatile uint8_t MavtD;
volatile uint8_t MavtG;


/************************ fonctions temporaires **************************/

void init_motcc( void ){
  /*Initiation registre timer (TCCRX): 0100 0100*/
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
  DDRC  = 0xE7;

  /* Pins d'entrées des codeurs et autres capteur en Pull Up */
  DDRD  = 0x0;
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
  init_motcc();
  departStrat();
  return 0;
}

/***************************     loop     ********************************/

void loop( void ){
  //RCMotG = PWM_TIMER/1000;
  //RCMotD = PWM_TIMER/1000;
}

/***************************     Main     ********************************/

int main( void ){

  setup();
  while(1){
    loop();
  }
  return 0;
}


/* fonctions temporaires */

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

