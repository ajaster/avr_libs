/*!
 * \file
 * \brief File attaches to all sources when MCU is AVR
 */

/*
 * By Vladislav Khmelevsky
 */

#ifndef _avrHeader
#define _avrHeader

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define delay_ms _delay_ms
#define delay_us _delay_us

typedef unsigned char byte;
typedef unsigned char bool;

#define ISODD(x) ((x) & 1)      //!< Check if number is ODD
#define SHIFT(x) (1 << (x))     //!< Shift bit to x posytion

#define PIN(REG)  (*(&REG - 2)) //!< Address Of Data Direction Register Of Port REG
#define DDR(REG)  (*(&REG - 1)) //!< Address Of Input Register Of Port REG
#define PORT(REG) (REG)         //!< Port REG
#define PINISON(REG, IO) (PIN(REG) & (1 << (IO))) //!< Check if PIN IO on PORT REG is ON

#define ON(REG, IO)   ((REG) |= (1 << (IO))) //!< Turn bit IO in REG to 1
#define OFF(REG, IO)  ((REG) &= ~(1 << (IO))) //!< Turn bit IO in REG to 0
#define ONOFF(REG, IO, STATE) ((STATE) ? ON((REG), (IO)) : OFF((REG), (IO))) //!< Turn bit IO On or Off by state
#define ISON(REG, IO) ((REG) & (1 << (IO))) //!< Check bit IO in REG is 1

#endif //_avrHeader
