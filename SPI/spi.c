/*
###############################################
This is SPI library by yota9
SPI mode 0
Main settings: no interrupt, high byte forward,
	             master,   prescaler = 64/2 = 32;
*/
#include "spi.h"

static inline void setPorts(void){
     SPIDDR |=  (1 << SMOSI) | (1 << SSCK) | (1 << SSS);
     SPIDDR &= ~(1 << SMISO);
     PORTON(SSS);
     PORTON(SMISO);
     DDR(SRAMPORT) |= (1 << SCS);
     SRAMON(SCS);
}

void SPIinit(void){
     setPorts();
     SPCR = 0b01010010; //main settings
     SPSR = 0b00000001; //SPEED * 2;
}

byte SPIsend(byte tx){
  SPDR = tx;
  while(!(SPSR & (1 << 7)));
  return SPDR;
}
