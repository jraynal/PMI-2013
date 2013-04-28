#include "couche_hardware.h"

/************************* Variables Globales ***************************/

volatile unsigned char RCMotD=100;
volatile unsigned char RCMotG=100;
volatile unsigned char MavtD=ARRET;
volatile unsigned char MavtG=ARRET;
volatile unsigned char ComptD=0;
volatile unsigned char ComptG=0;
//volatile unsigned char VitD=0;
//volatile unsigned char VitG=0;

unsigned char temps_max=100,compt=5;
volatile unsigned char asserv=1;
volatile unsigned int compt_01s=0;
volatile unsigned char compt1=0,compt2=0;





void initPinsAndInterruptions(){
  DDRC=~(3<<3);
  PORTC=0x00;

  GICR=(1<<INT0)|(1<<INT1);
  MCUCR=0x0a;
  DDRD=0xf0;
  PORTD=0x01;
	
  DDRB=0x10;
  PORTB=0x00;
	
  DDRA=0x00;
	
  sei();
  TIMSK=(1<<TOIE0)|(1<<TOIE1)|(1<<TOIE2);
  timer2_enabled();
  timer1_enabled();
  timer0_enabled();
  MOTEUR_A(AVANCE,20);
  MOTEUR_B(AVANCE,20);
  //allumer_pompe();
}

SIGNAL(TIMER1_OVF_vect){
  timer1_disable();
  if (temps_max<25){
    temps_max+=1;
  } else {
    temps_max=7;
  }
  timer1_enabled();
}

SIGNAL(INT0_vect){
  compt2++;
}

SIGNAL(INT1_vect){
  compt1++;
}

SIGNAL(TIMER0_OVF_vect){
  timer0_disable();
  timer0_enabled();

  compt++;
  if (compt==temps_max){
    PORTD&=~(0x0f<<SERVO1);
  } else {
    if (compt==200){
      compt=0;
      PORTD|=0x0f<<SERVO1;
    }
  }
  if (asserv==1){
    if (compt_01s==1000){
      compt_01s=0;
      if (compt1<30){
	if (RCMotG+CORRECT<199){
	  RCMotG+=CORRECT;
	}
      } else {
	if (compt1>30) {
	  if (RCMotG>10){
	    RCMotG-=CORRECT;
	  }
	}
      }

      compt1=0;
			
      if (compt2<30){
	if (RCMotD+CORRECT<199){
	  RCMotD+=CORRECT;
	}
      } else {
	if (compt2>30)
	  {
	    if (RCMotD>10){
	      RCMotD-=CORRECT;
	    }
	  }
      }
      compt2=0;
			
    } else {
      compt_01s++;
    }
  }
}

SIGNAL(TIMER2_OVF_vect)
{
  timer2_disable();
  timer2_enabled();
  if (MavtG)
    {
      ComptG++;
      if (ComptG==RCMotG)
	{
	  PORTC&=~(VM1);
	}
      else
	{
	  if (ComptG==200){
	    ComptG=0;
	    PORTC|=VM1;
	  }
	}
    }
  if (MavtD)
    {
      ComptD++;
      if (ComptD==RCMotD){
	PORTC&=~(VM2);
      } else {
	if (ComptD==200){
	  ComptD=0;
	  PORTC|=VM2;
	}
      }
    }
}

void timer1_enabled(void){
  TCNT1=65536-3906;
  TCCR1B=0x05;
}

void timer1_disable(void){
  TCCR1B=0x00;
}

void timer0_enabled(void){
  TCNT0=256-6;
  TCCR0=0x04;
}

void timer0_disable(void){
  TCCR0=0x00;
}

void timer2_enabled(void){
  TCNT2=256-10;
  TCCR2=0x03;
}

void timer2_disable(void){
  TCCR2=0x00;
}


void MOTEUR_A(uint8_t etat,uint8_t vitesse){
  MavtG=ARRET;
  PORTC&=~(VM1|S11|S12);
  //VitG=((vitesse/(2.2*2*3.14))*19*2)/10+1;
  RCMotG=vitesse;
  switch (etat){
  case AVANCE:	
    PORTC|=(VM1|S11);
    PORTC&=~(S12);
    break;
  case RECULE:
    PORTC|=(VM1|S12);
    PORTC&=~(S11);
    break;
  case ARRET:
    PORTC&=~(VM1|S11|S12);
    break;		
  }
  MavtG=etat;
  ComptG=0;
}

void MOTEUR_B(uint8_t etat,uint8_t vitesse){
  MavtD=ARRET;
  PORTC&=~(VM2|S21|S22);
  //VitD=((vitesse/(2.2*2*3.14))*19*2)/10+1;
  RCMotD=vitesse;
  switch (etat){
  case AVANCE:
    PORTC|=(VM2|S21);
    PORTC&=~(S22);
    break;
  case RECULE:	
    PORTC|=(VM2|S22);
    PORTC&=~(S21);
    break;
  case ARRET:
    PORTC&=~(VM2|S21|S22);
    break;
  }
  MavtD=etat;
  ComptD=0;
}

void allumer_pompe(void){
  PORTB|=(1<<POMPE);
}

void eteindre_pompe(void){
  PORTB&=~(1<<POMPE);
}

char cote_jeu(void){
  if (PINA&(1<<CHOIX)){
    return ROUGE;
  }
  else{
    return BLEU;
  }
}

void CAN_Init(void){  //tr
  ADMUX=0x00;  //frequence /8
  ADCSRA=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS2);	//validation du adc
}

unsigned short CAN_conversion(char canal){
  ADMUX=ADMUX&0xf0;
  ADMUX=ADMUX|canal;  //choix du canal
  ADCSRA=ADCSRA|(1<<ADSC);		//debut de la conversion
  while(((ADCSRA)&(1<<ADIF))==0)
    ;
  ADCSRA=ADCSRA|(1<<ADIF);
  return ADC;
}
