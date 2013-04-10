#include "gest_trajectoire.h"


static uint8_t triangle_de_vitesse( uint16_t tps ){
  uint16_t j = 0;
  uint16_t demi = (tps / 2);
  /*Accélération*/
  while(( RCMotG == 255 ) || (j != demi)){
    RCMotD = (RCMotG++);
    j++;
  }
  tps = tps - demi;
  while( tps > j )
    tps--;
  /*Décélération*/
  while((RCMotG == 0) || (j != 0)){
    RCMotD = (RCMotG--);
    j--;
  }
  return 0;
}

char avance( uint8_t cm , sens ss ){
  uint16_t tps;
  switch(ss){
  case(AVANT):
      MavtD = (MavtG = 1);
      break;
  case(ARRIERE):
    MavtD = (MavtG = 0);
    break;
  default:
      return 1;
  }
  tps = (cm * 1000) / VM;
  triangle_de_vitesse( tps );
  return 0;
}

char tourne( uint8_t angle , sens ss){
  uint8_t tps;
  switch(ss){
  case(DROITE):
      MavtD = 0;
      MavtG = 1;
      break;
  case(ARRIERE):
      MavtD = 1;
      MavtG = 0;
      break;
  default:
      return 1;
  }
  tps = angle * TP_180 / 180 ;
  triangle_de_vitesse( tps );
  return 0;
}
struct position_{
  uint16_t x;
  uint16_t y;  
};

struct etape_{
  position p1;
  position p2;
  etape *suivante;
};

struct trajectoire_{
  etape *première;
  etape *dernière;
};

void lancer_etape( etape e ){

}

void creer_etape( position p1 , position p2){

}

void ajouter_etape( trajectoire t ){

}

void charger_trajectoire( void ){

}

static supprimer_etape( trajetoire t , etape e ){

}


