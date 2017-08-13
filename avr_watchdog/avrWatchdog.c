/*!
 * \file
 * \brief AVR watchdog functions
 */

/*!
 * \brief Enable watchdog
 * \param[in] x 0..9, watchdog time
 */
void watchdogON(char x)
{
    wdt_enable((x));
}

#if mcu == attiny441
//! Disable watchdog on startup
void get_mcusr(void) \
    __attribute__((naked)) \
    __attribute__((section(".init3")));
void get_mcusr(void)
{
    MCUSR = 0;
    wdt_disable();
}
#endif
