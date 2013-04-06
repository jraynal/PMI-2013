/****************************** Includes *********************************/

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/**************************** Declarations *******************************/

#define F_CPU         16000000UL
#define MAXT1         65535 /* 2¹⁶ */
#define MAXT02        255   /* 2⁸ */
#define CURSOR_PWM    20000 //MAXT1-1//1 khz : (MAXT1 - (MAXT1 / 100) - 40 )
#define PRESC         0x03
#define DIX_POURCENTS ((MAXT1 - CURSOR_PWM) / 10)
#define C1 1<<5
#define C2 1<<4
#define C3 1<<2

volatile uint16_t cpt = 0;
volatile uint8_t  j   = 0;


/************************ fonctions temporaires **************************/

void init_pwm( void ){
  //OCR1A = CURSOR_PWM + CURSOR_PWM / 10000;
  TCNT1 = CURSOR_PWM;

  /* Parmètre les clocks */
  TCCR1A = 0x01;
  TCCR1B = PRESC;

  /*Autorise les interuption des clocks*/
  TIMSK1 |= 1<<TOIE1 | 1<<OCIE1A ;
  sei();
}

uint8_t init_pins( void ){
  /* Pins de validation et de sens des moteurs en Output High */
  DDRC  |= 1<<0 | 1<<1;
  PORTC |= 1<<0 | 1<<1;
  
}

void delay(uint16_t ms){
  int i,j;
  uint32_t ticks = F_CPU / 1000;
  for (i =0 ; i<ms ; i++ )
    {
      for (j=0;j<ticks;j++){}
    }
}

ISR( TIMER1_COMPA_vect ){

  PORTC &= ~1<<0;
}



ISR( TIMER1_OVF_vect ){

  TCCR1B = 0x00 ;
  TCNT1 = CURSOR_PWM;
  PORTC |= 1<<0;

  if (cpt == 0)
    PORTC |= 1<<1;
  if (cpt == 1){//(DIX_POURCENTS - j)){
    PORTC &= ~1<<1;
    j++;
  }
  cpt ++;
  
  if (cpt == 2){
   cpt = 0;
   j   = 0;
  }
  
  TCCR1B |= PRESC;
}


/****************************    Setup    ********************************/

void setup( void ){
  init_pwm();
  init_pins();

  PORTC |= 1<<1;

}

/***************************     loop     ********************************/

void loop( void ){

  /* delay(50); */

  /* PORTC |= C2;  */
  /* PORTC &= ~C3; */

  /* delay(50); */

  /* PORTC |= C1; */
  /* PORTC &= ~C2; */

  /* delay(50); */

  /* PORTC |= C3;  */
  /* PORTC &= ~C1; */

  /* delay(50); */

  /* PORTC |= C2 | C1; */
  /* PORTC &= ~C3; */

  /* delay(50); */

  /* PORTC |=  C3; */
  /* PORTC &= ~C1; */
  
}

/***************************     Main     ********************************/

int main( void ){

  setup();
  while(1){
    loop();
  }
  PORTC = C2;
  return 0;
}

