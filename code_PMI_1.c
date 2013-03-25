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
#include <AVR/io.h>
#include <AVR/interupt.h>
#include <AVR/sleep.h>

/**************************** Declarations *******************************/

#define VM1       (1 << 2)
#define SM11      (1 << 0)
#define SM12      (1 << 1)
#define VM2       (1 << 7)
#define SM21      (1 << 5)
#define SM22      (1 << 6)
#define PWM_TIMER            (F_CPU / 16 / 32) /*31 250 hz*/

volatile uint16_t RCMotD;
volatile uint16_t RCMotG;
volatile uint16_t RCser ;

/****************************    Setup    ********************************/

uint8_t setup( void ){

  init_pins();
  init_motcc();

  return 0;
}

/***************************     loop     ********************************/

void loop( void ){
  departStrat();

}

/***************************     Main     ********************************/

void main( void ){

  setup();

  while(1){
    loop();
  }
}


/* fonctions temporaires */

/* Interruption moteurs cc */
ISR( TIMER0_OCR_vect ){
  /**
   *  On coupe tout:
   *  Validation à 1
   *  Sens 1 à 1
   *  Sens 2 à 1
   **/
  PORTC |= VM1 | SM11 | SM 12;
}

ISR( TIMER0_OVF_vect ){
  /**
   *  On alimente dans le sens de marche
   *  Validation 1
   *  Sens 1 à 1 ou 0
   *  Sens 2 à 1 ou 0
   **/

  if (MavtD)
    PORTC |= _BV(0);
  else
    PORTC |= _BV(1);
}

ISR( TIMER2_OCR_vect ){
}

ISR( TIMER2_OVF_vect ){
}

uint8_t init_motcc( void ){

  /* Les moteurs ne doivent pas tourner */
  RCMotG = 0;
  RCMotD = 0;

  /* Moteur Gauche */
  TCNT0 = PWM_TIMER;
  OCR0  = RCMotG ;

  /* Moteur Droit  */
  TCNT2 = PWM_TIMER;
  OCR2  = RCMotD ;

}

uint8_t init_pins( void ){
  /* Pins de validation et de sens des moteurs en Output High */
  DDRC  = 0xE7;

  /* Pins d'entrées des codeurs et autres capteur en Pull Up */
  DDRD  = 0x0;
  PORTD = 0x30;
  DDRB  = 0x0;
  PORTB = 0x0F;

  /* Enable OC1 as output. */
  DDROC = _BV (OC1);

  /* Enable timer 1 overflow interrupt. */
  TIMSK = _BV (TOIE1);
  sei ();


}

uint8_t departStrat( void ){
  /* Retrait de la tirette */
  while( PINA && 1 << 0 ); 
  return 1;
}

