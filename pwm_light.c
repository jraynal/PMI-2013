#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>




int main( void ){
  DDRC  = 1 << 0 | 1 << 1;
  PORTC = 1 << 0 | 1 << 1;
  
  OCR0A = 190;
  TCNT0 = 127;

  TCCR0B = 1<<CS01;

  TIMSK0 = 1<<TOIE0 |1<<OCIE0A;
  sei();

  while(1);
}

ISR(TIMER0_COMPA_vect){
  PORTC &= ~ 1<<0;
}

ISR(TIMER0_OVF_vect){
  PORTC |= 1<<0;
}
