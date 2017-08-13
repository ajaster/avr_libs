/*!
 * \file
 * \brief Some defines for attiny441
 */

#include "avrHeader.h"
#include "mmcu.h"

#ifndef _t441
#define _t441

#if mcu == attiny441
/* UART0 registers */
#define UDR UDR0
#define UCSRA UCSR0A
#define UCSRB UCSR0B
#define UCSRC UCSR0C
#define UBRRH UBRR0H
#define UBRRL UBRR0L
/* UART0 Bits */
#define RXC RXC0
#define TXC TXC0
#define UDRE UDRE0
#define FE FE0
#define DOR DOR0
#define PE PE0
#define U2X U2X0
#define MPCM MPCM0
#define RXCIE RXCIE0
#define TXCIE TXCIE0
#define UDRIE UDRIE0
#define RXEN RXEN0
#define TXEN TXEN0
#define UCSZ2 UCSZ02
#define RXB8 RXB80
#define TXB8 TXB80
#define URSEL UMSEL01
#define UMSEL0  UMSEL00
#define UMP1 UMP01
#define UMP0 UMP00
#define USBS USBS0
#define UCSZ1 UCSZ01
#define UCSZ0 UCSZ00
#define UCPOL UCPOL0
#endif

#endif //_t441
