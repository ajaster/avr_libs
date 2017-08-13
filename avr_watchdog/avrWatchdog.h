/*!
 * \file
 * \brief Watchdog defines
 */

#ifndef _avrWatchdog
#define _avrWatchdog

#include <avr/wdt.h>

#define resetWatchdog() wdt_reset() //!< Reset watchdog
#define watchdogOFF() wdt_disable() //!< Disable watchdog

void watchdogON(char x);

#endif //_avrWatchdog
