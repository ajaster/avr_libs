/*
################################
This is SPI SRAM 23k256 library
made by yota9
*/

#include "sram.h"

void sram_init(byte mode)
{
    SRAMOFF(SCS);
    SPIsend(WRITESTSRAM);
    SPIsend(mode);
    SRAMON(SCS);
}

byte read_st_sram(void)
{
    byte ans;

    SRAMOFF(SCS);
    ans = SPIsend(READSTSRAM);
    SRAMON(SCS);

    return ans;
}

void write_sram_byte(byte data, unsigned int addr)
{
    SRAMOFF(SCS);
    SPIsend(WRITESRAM);
    SPIsend(addr >> 8);
    SPIsend(addr);
    SPIsend(data);
    SRAMON(SCS);
}

byte read_sram_byte(unsigned int addr)
{
    byte ans;

    SRAMOFF(SCS);
    SPIsend(READSRAM);
    SPIsend(addr >> 8);
    SPIsend(addr);
    ans = SPIsend(0xFF);
    SRAMON(SCS);

    return ans;
}
