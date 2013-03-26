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
/*                    le 21/03/2013        18:40                         */
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
#include <avr/sleep.h>

/**************************** Declarations *******************************/

#define VM1       (1 << 2)
#define SM11      (1 << 0)
#define SM12      (1 << 1)
#define VM2       (1 << 7)
#define SM21      (1 << 5)
#define SM22      (1 << 6)
#define F_CPU     16000000
#define PWM_TIMER            (F_CPU / 16 / 32) /*31 250 hz*/

volatile uint16_t RCMotD;
volatile uint16_t RCMotG;
volatile uint16_t RCser ;
volatile uint8_t MavtD;
volatile uint8_t MavtG;


/************************ fonctions temporaires **************************/

void init_motcc( void ){
  /*Initiation registre timer (TCCRX): 0100 0100*/
  /* Les moteurs ne doivent pas tourner */
  RCMotG = PWM_TIMER*2;
  RCMotD = PWM_TIMER*2;

  /* Moteur Gauche */
  OCR0A  = RCMotG ;
  TCCR0A = 0x41;
  TCCR0B = 0x0D;
  /* Moteur Droit  */
  OCR2A  = RCMotD ;
  TCCR2A = 0x41 ;
  TCCR2B = 0x0D ;

  /*Autorise les interuption des clocks*/
  TIMSK0 |= 0x03 ;
  TIMSK2 |= 0x03 ;
  sei();
}

uint8_t init_pins( void ){
  /* Pins de validation et de sens des moteurs en Output High */
  DDRC  = 0xE7;

  /* Pins d'entrées des codeurs et autres capteur en Pull Up */
  //  DDRD  = 0x0;
  //PORTD = 0x30;
  //DDRB  = 0x0;
  //PORTB = 0x0F;
}

uint8_t departStrat( void ){
  /* Retrait de la tirette */
  /* while( PINA && 1 << 0 ); */
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
  RCMotG = PWM_TIMER * 2;
  RCMotD = PWM_TIMER * 2;
  MavtD=1;
  MavtG=1;
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
ISR( TIMER0_COMPA_vect ){
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
  if (MavtD)
    PORTC &= ~SM11;
  else
    PORTC &= ~SM12;
}

ISR( TIMER2_COMPA_vect ){
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
  if (MavtG)
    PORTC &= ~SM21;
  else
    PORTC &= ~SM22;
}

