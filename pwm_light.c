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
#define CURSOR_PWM 180
#define PRESCALER0 0x02


volatile uint8_t RCMotD;
volatile uint8_t RCMotG;
volatile uint16_t RCser ;
volatile uint8_t MavtD;
volatile uint8_t MavtG;


/************************ fonctions temporaires **************************/

void init_motcc( void ){
  /*Initiation registre timer (TCCRX): 0100 0100*/
  /* Les moteurs ne doivent pas tourner */
  RCser = CURSOR_PWM+100;

  /* Moteur Gauche */
  OCR1A  = RCser ;
  TCNT1 = CURSOR_PWM;
  /* Parmètre les clocks */

  TCCR1A = 0x00;
  TCCR1B = PRESCALER0;

  /*Autorise les interuption des clocks*/
  TIMSK1 = 0x03;
  sei();
}

uint8_t init_pins( void ){
  /* Pins de validation et de sens des moteurs en Output High */
  DDRC  = SM11;
  PORTC = 0x05;
}

void delay(int tick){
  int i;
  for (i = 0 ; i < tick ; i++);
}

/****************************    Setup    ********************************/

void setup( void ){
  init_pins();
  init_motcc();
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


/* fonctions temporaires */

/*Interruption moteurs cc*/

ISR( TIMER1_COMPA_vect ){

  PORTC &= 1<<0;

}



ISR( TIMER1_OVF_vect ){
  TCCR1B = 0x00;

  TCNT1 = CURSOR_PWM;
  PORTC |= 1<<0;

  TCCR1B = PRESCALER0;
}

