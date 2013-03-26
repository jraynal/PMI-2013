/****************************** Includes *********************************/

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

/**************************** Declarations *******************************/

#define VM1       (1 << 2)
#define SM11      (1 << 0)
#define SM12      (1 << 1)
#define F_CPU     16000000UL
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

  /* Moteur Gauche */
  OCR0A  = RCMotG ;
  TCCR0A = 0x41;
  TCCR0B = 0x0D;

  /*Autorise les interuption des clocks*/
  TIMSK0 |= 0x03 ;
}

uint8_t init_pins( void ){
  /* Pins de validation et de sens des moteurs en Output High */
  DDRC  = VM1 | SM11 | SM12;
}

/****************************    Setup    ********************************/

void setup( void ){

  init_pins();
  init_motcc();
}

/***************************     loop     ********************************/

void loop( void ){
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
  if (MavtG)
    PORTC &= ~SM11;
  else
    PORTC &= ~SM12;
}
