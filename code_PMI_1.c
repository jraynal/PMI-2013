//////////////////////////////////////////////////////////////////////////////
/*                                                                          */
/*           #########          ##       ###             ####               */
/*           ###     ##         ####    # ##              ##                */
/*           ###     ##         ## ##  #  ##              ##                */
/*           ########           ##   ##   ##              ##                */
/*           ###                ##        ##              ##                */
/*           ###                ##        ##              ##                */
/*           ###         ##     ##        ##      ##     ####               */
/*                                                                          */
//////////////////////////////////////////////////////////////////////////////


/******************************  Auteurs  ***********************************/
/*                                                                          */
/*                      JR -- petit coordinateur --                         */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/****************************************************************************/


/*************************** Dernière Modif *********************************/
/*                    le 21/02/2013        14:40                            */
/****************************************************************************/


/**************************** Commentaires **********************************/
/*                                                                          */
/****************************************************************************/


/****************************     TODO    ***********************************/
/*                                                                          */
/*                                                                          */
/*                         TOUT!!!!!!!!!!!!!!                               */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/****************************************************************************/

/******************************* Includes ***********************************/

#include <stdio.h>
#include <aversive.h>


/***************************** Declarations *********************************/

#define VALIDATION_MOTEUR_1  (1 << 2)
#define SENS_MOTEUR_1_1      (1 << 0)
#define SENS_MOTEUR_1_2      (1 << 1)
#define VALIDATION_MOTEUR_2  (1 << 7)
#define SENS_MOTEUR_2_1      (1 << 5)
#define SENS_MOTEUR_2_2      (1 << 6)
#define PWM_TIMER            (F_CPU/16)



/*****************************    Setup    **********************************/

char setup( void ){

  init_pins();

  return 0;
}

/****************************     loop     **********************************/

void loop( void ){



}

/****************************     Main     **********************************/

int main( void ){

  setup();

  while(1){
    loop();
  }

  return 0;
}


/* fonctions temporaires */

int setpwm( int uncertainport , const int masquebroche , int tempsHaut ){
  int i;
  for ( i = 0 ; i < 1000 ; i++ ){
    if ( i >= tempsHaut ){
      uncertainport &= ~masquebroche;
      break;
    } 
  }
  return 0;
} 

int init_pins( void ){
  /* Pins de validation et de sens des moteurs en Output High */
  DDRC  = 0xE7;

  /* Pins d'entrées des codeurs et autres capteur en Pull Up */
  DDRD  = 0x0;
  PORTD = 0x30;
  DDRB  = 0x0;
  PORTB = 0x0F;
}

int departStrat( void ){
  /* Retrait de la tirette */
  while( PINA && 1 << 0 ); 
  return 1;
}
