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

#define VALID_MOTEUR_1       (1 << 2)
#define SENS_MOTEUR_1_1      (1 << 0)
#define SENS_MOTEUR_1_2      (1 << 1)
#define VALID_MOTEUR_2       (1 << 7)
#define SENS_MOTEUR_2_1      (1 << 5)
#define SENS_MOTEUR_2_2      (1 << 6)
#define PWM_TIMER            (F_CPU/16)

uint16_t RCMot;
uint16_t RCser;
/*Fixage de l'ovrflow*/
OCR = 0;

/****************************    Setup    ********************************/

uint8_t setup( void ){

  init_pins();

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

/* Une Interruption toutes les 1ms */
ISR( TIMER0_OVF_vect ){
  static uint8_t cpwm = 0;
  if ( cpwm == 0 )
    /*Mot & servo à 1*/;
  if ( ( cpwm % 10 ) == RCMot )
    /*Mot à 0*/;
  if ( cpwm == RCSer )
    /*Ser à 0*/;
  if ( cpwm == /*overflow*/ /2 )
    /*Mot à 1*/;
  cpwm++;
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

