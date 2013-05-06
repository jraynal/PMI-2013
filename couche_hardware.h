#ifndef _COUCHE_HARDWARE_H_
#define _COUCHE_HARDWARE_H_

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "definitions.h"

void timer2_enabled(void);
void timer2_disable(void);
void timer1_enabled(void);
void timer1_disable(void);
void timer0_enabled(void);
void timer0_disable(void);
void MOTEUR_A(sens etat,uint8_t vitesse);
void MOTEUR_B(sens etat,uint8_t vitesse);
void allumer_pompe(void);
void eteindre_pompe(void);
char cote_jeu(void);
void initPinsAndInterruptions(void);
void CAN_Init(void);
unsigned short CAN_conversion(char canal);



#endif /*_COUCHE_HARDWARE_H_*/
