#include "gest_trajectoire.h"


static uint8_t triangle_de_vitesse( uint16_t tps ){
  uint16_t j = 0;
  uint16_t demi = (tps / 2);
  /*Accélération*/
  while(( RCMotG == 255 ) || (j != demi)){
    /* rajouter tempo */
    RCMotD = (RCMotG++);
    j++;
  }
  tps = tps - demi;
  while( tps > j ){
    /* rajouter tempo*/
    tps--;
  }
  /*Décélération*/
  while((RCMotG == 0) || (j != 0)){
    /* rajouter tempo */
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
  case(GAUCHE):
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

/************************* Structures ***********************************/

struct position_{
  uint16_t x;
  uint16_t y;
  position *suivante;
};

struct ojectif_{
  position *actuelle;
};

struct etape_{
  objectif *obj;
  etape *suivante;
};

struct trajectoire_{
  etape *première;
  etape *dernière;
};

/*****************************  Position  ******************************/

static position *creer_position( uint16_t x , uint16_t y ){
  positition bpos;
  bpos.x=x;
  bpos.y=y;
  bpos.suivante=NULL;
  positition *pos = &bpos;
  return pos;
}

/*****************************  Objectif  ******************************/

static objectif *creer_objectif(){
  objectif bobj;
  objectif *obj = &bobj;
  return obj;
}

static objectif *ajouter_position( objectif *obj, positition *pos){
  position * courant = obj->actuelle;
  if (obj->actuelle == NULL)
    obj->actuelle=pos;
  else
    {
      while(courant->suivante != NULL)
	courant = courant->suivante;
      courant->suivante=pos;
    }
  return obj;
}

/*****************************   Etapes   ******************************/

static etape *creer_etape( objectif *obj ){
  etape betp;
  betp.obj=obj;
  betp.suivante=NULL;
  etape *etp = &betp;
  return etp;
}

/***************************** Trajectoire *******************************/
/* Les étapes de la strat sont codées en dur, on ne rajoute que l'évitement */
etape *ajouter_etape( trajectoire t , etape e ){
  
}


/* charge en rélité la stratégie codée en elle*/
trajectoire *charger_trajectoire( void ){

}

/*************************** Lancement **********************************/

void lancer_etape( etape e ){
  
}

void lancer_trajectoire( trajectoire tr){

}

