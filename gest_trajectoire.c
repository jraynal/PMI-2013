#include "gest_trajectoire.h"

void delay(uint8_t ms){
  for(;100*ms>0;ms--);
}

static uint8_t triangle_de_vitesse( sens etat1, sens etat2, uint16_t tps ){
  uint16_t huitieme = tps/8;
  uint16_t compteur = 0;
  /* acceleration */
  while(compteur < huitieme){
    compteur++;
    tps--;
    MOTEUR_A(etat1,compteur);
    MOTEUR_B(etat2,compteur);
    delay(100);
  }
  /* vitesse constante */
  while(tps > huitieme){
    compteur++;
    tps--;
    MOTEUR_A(etat1,VMAX);
    MOTEUR_B(etat2,VMAX);
    delay(100);  
  }

  /* deceleration */
  while(tps > 0){
    compteur++;
    tps--;
    MOTEUR_A(etat1,tps);
    MOTEUR_B(etat2,tps);
    delay(100);
  }
  return 0;
}

char avance( uint8_t cm , sens ss ){
  uint16_t tps = (cm * 1000) / VM;
  switch(ss){
  case(AVANCE):
    triangle_de_vitesse( AVANCE, AVANCE, tps );
    break;
  case(RECULE):
    triangle_de_vitesse( RECULE, RECULE, tps );
    break;
  default:
    return 1;
  }
  return 0;
}

char tourne( uint8_t angle , sens ss){
  uint8_t tps = angle * TP_180 / 180;
  switch(ss){
  case(DROITE):
    triangle_de_vitesse( AVANCE, RECULE, tps );
    break;
  case(GAUCHE):
    triangle_de_vitesse( RECULE, AVANCE, tps );
    break;
  default:
    return 1;
  }
  return 0;
}

/************************* Structures ***********************************/

struct position_{
  uint16_t x;
  uint16_t y;
  position *suivante;
};

struct objectif_{
  position *actuelle;
};

struct etape_{
  objectif *obj;
  etape *suivante;
};

struct trajectoire_{
  etape *prem;
  etape *dern;
};

/*****************************  Position  ******************************/

static position *creer_position( uint16_t x , uint16_t y ){
  position bpos;
  bpos.x=x;
  bpos.y=y;
  bpos.suivante=NULL;
  position *pos = &bpos;
  return pos;
}

/*****************************  Objectif  ******************************/

static objectif *creer_objectif(){
  objectif bobj;
  objectif *obj = &bobj;
  return obj;
}

static objectif *ajouter_position( objectif *obj, position *pos){
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

etape *creer_etape( objectif *obj ){
  etape betp;
  betp.obj=obj;
  betp.suivante=NULL;
  etape *etp = &betp;
  return etp;
}

/***************************** Trajectoire *******************************/
/* Les étapes de la strat sont codées en dur, on ne rajoute que l'évitement */
etape *ajouter_etape( trajectoire t , etape e ){
  return &e;  
}


/* charge en rélité la stratégie codée en elle*/
trajectoire *charger_trajectoire( void ){
  trajectoire tr;
  return &tr;
}

/*************************** Lancement **********************************/

void lancer_etape( etape e ){
  
}

void lancer_trajectoire( trajectoire tr){

}

