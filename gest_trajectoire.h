#ifndef _GEST_TRAJECTOIRE_H_
#define _GEST_TRAJECTOIRE_H_
#include <stdio.h>
#include "definitions.h"

typedef struct etape_ etape;
typedef struct objectif_ objectif;
typedef struct trajectoire_ trajectoire;
typedef struct position_ position;

char avance( uint8_t ,  sens );
char tourne( uint8_t ,  sens );

void lancer_etape( etape );
void lancer_trajectoire( trajectoire );
etape *creer_etape( position , position);
etape *ajouter_etape( trajectoire , etape );
trajectoire *charger_trajectoire( void );

static etape *creer_etape( objectif *obj );
static objectif *ajouter_position( objectif *obj, positition *pos);
static objectif *creer_objectif( void );
static position *creer_position( uint16_t x , uint16_t y );


#endif /*_GEST_TRAJECTOIRE_H_*/
