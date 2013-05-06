#ifndef _GEST_TRAJECTOIRE_H_
#define _GEST_TRAJECTOIRE_H_
#include "couche_hardware.h"

typedef struct etape_ etape;
typedef struct objectif_ objectif;
typedef struct trajectoire_ trajectoire;
typedef struct position_ position;

char avance( uint8_t ,  sens );
char tourne( uint8_t ,  sens );

void lancer_etape( etape* );
void lancer_trajectoire( trajectoire* );
etape *creer_etape( objectif*);
void ajouter_etape( etape* , etape* );
trajectoire *charger_trajectoire( void );


#endif /*_GEST_TRAJECTOIRE_H_*/
