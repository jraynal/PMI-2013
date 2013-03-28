/****************************** Includes *********************************/

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/**************************** Declarations *******************************/

#define VM1       (1 << 2)
#define SM11      (1 << 0)
#define SM12      (1 << 1)
#define F_CPU     16000000UL
#define PWM_TIMER            (F_CPU / 2)//16 / 32) /*31 250 hz*/

volatile uint8_t RCMotD;
volatile uint8_t RCMotG;
volatile uint16_t RCser ;
volatile uint8_t MavtD;
volatile uint8_t MavtG;


/************************ fonctions temporaires **************************/

void init_motcc( void ){
  /*Initiation registre timer (TCCRX): 0100 0100*/
  /* Les moteurs ne doivent pas tourner */
  RCMotG = 255;

  /* Moteur Gauche */
  OCR0A  = RCMotG ;

  /* Parmètre les clocks */

  TCCR0A = 0x40;
  TCCR0B = 0x03;

  /*Autorise les interuption des clocks*/
  TIMSK0 = 0x01;//0x03;
  sei();
}

uint8_t init_pins( void ){
  /* Pins de validation et de sens des moteurs en Output High */
  DDRC  = SM11;
  PORTC = 0x05;

  DDRC |= 1<<5;
}

void delay(int tick){
  int i;
  for (i = 0 ; i < tick ; i++);

}

/****************************    Setup    ********************************/

void setup( void ){
  init_pins();
  //  init_motcc();
}

/***************************     loop     ********************************/

void loop( void ){
  /* int i; */
  /* for ( i = 0 ; i < 256 ; i++ ){ */
  /*   delay(5000); */
  /*   OCR0A = 200; */
  /* } */
  
  PORTC |= 1<<5;
  /* delay(500); */
  /* PORTC &= 0<<5; */
  /* delay(500); */
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

/* ISR( TIMER0_COMPA_vect ){ */
/*   /\** */
/*    *  On coupe tout: */
/*    *  Validation à 1 */
/*    *  Sens 1 à 1 */
/*    *  Sens 2 à 1 */
/*    **\/ */
/*     PORTC = 0x00; */
/* } */



/* ISR( TIMER0_OVF_vect ){ */
/*   static uint8_t cpt = 0;  */
/*   /\** */
/*    *  On alimente dans le sens de marche */
/*    *  Validation 1 */
/*    *  Sens 1 à 1 ou 0 */
/*    *  Sens 2 à 1 ou 0 */
/*    **\/ */
/*     PORTC = 1<<0; */
/*     if (cpt == 10) */
/*       PORTC = 0x00; */
/*     if (cpt == 20) */
/*       cpt=0; */
/* } */

