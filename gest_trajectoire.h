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

etape *lancer_etape( etape );
etape *creer_etape( position , position);
etape *ajouter_etape( trajectoire , etape );
trajectoire *charger_trajectoire( void );


#endif /*_GEST_TRAJECTOIRE_H_*/
