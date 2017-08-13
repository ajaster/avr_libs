#ifndef _SPIH
#define _SPIH

#include "avr.h"

/* SD card */
#define SPIDDR      DDRB
#define SPIPORT     PORTB
#define SMOSI       PB5
#define SMISO       PB6
#define SSCK        PB7
#define SSS         PB4
#define PORTON(PB)  SPIPORT |=  (1 << (PB))

void SPIinit(void);
byte SPIsend(byte tx);


#endif //_SPIH
