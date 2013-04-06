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
/*                    le 02/04/2013        09:20                         */
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
#include "gest_trajectoire.h"

/************************ fonctions temporaires **************************/

void init_pwm( void ){
  /* Les moteurs ne doivent pas tourner */
  RCMotG = 0;
  RCMotD = 0;

  /* On fixe le départ du compteur pour régler la fréquence*/
  TCNT0 = CURSOR_PWM;
  TCNT2 = CURSOR_PWM;
  TCNT1 = CURSOR_SERVO;

  /* Moteur Gauche */
  OCR0  = CURSOR_PWM+10 ;
  TCCR0 = PRESCALER;
  /* Moteur Droit  */
  OCR2  = CURSOR_PWM+10 ;
  TCCR2 = PRESCALER;

  /*Servos*/
  TCCR1B = PRESCALER_SERVO;

  /*Autorise les interuption des clocks*/
  TIMSK |= 0xCB ;
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
  avance(20,AVANT);
  avance(20,ARRIERE);
  tourne(180,DROITE);
  tourne(180,GAUCHE);
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

ISR( TIMER1_OVF_vect ){
  TCCR1B=0x00;
  cpts++;

  if ( cpts == pwm_bit_down )
    PORTD &= ~SERVO1 & ~SERVO2 & ~SERVO3 & ~SERVO4;
  if ( cpts == 200 ){
    cpts = 0;
    if (pwm_bit_down <= 20)
      pwm_bit_down++;
    else
      pwm_bit_down = 0;
    PORTD |= SERVO1 | SERVO2 | SERVO3 | SERVO4;
  }

  TCNT1 = CURSOR_SERVO;
  TCCR1B=PRESCALER_SERVO;
}
