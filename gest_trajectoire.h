#ifndef _GEST_TRAJECTOIRE_H_
#define _GEST_TRAJECTOIRE_H_
#include <stdint.h>
#include "definitions.h"

typedef struct etape_ etape;
typedef struct trajectoire_ trajectoire;
typedef struct position_ position;

char avance( uint8_t ,  sens );
char tourne( uint8_t ,  sens );

void lancer_etape( etape );
void creer_etape( position , position)
void ajouter_etape( trajectoire );
void charger_trajectoire( void );


#endif /*_GEST_TRAJECTOIRE_H_*/
