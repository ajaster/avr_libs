#ifndef _SRAMH
#define _SRAMH

#include "spi.h"

/* SRAM */
#define SRAMPORT    PORTA //!< SRAM port CS
#define SCS         PA0 //!< SRAM PIN
#define SRAMON(PA)  SRAMPORT |=  (1 << (PA)) //!< Disable SRAM
#define SRAMOFF(PA) SRAMPORT &= ~(1 << (PA)) //!< ENABLE SRAM
/* MODES */
#define BYTEOP      0b00000000 //!< Read/write operations limited to one byte mode
#define PAGEOP      0b10000000 //!< Read/write operations limited to 32 bytes (1024 pages) mode
#define SEQUOP      0b01000000 //!< Auto increment address mode
/* INSTRUNCTIONS */
#define READSRAM    0b11  //!< Read SRAM instruction
#define WRITESRAM   0b10  //!< Write SRAM instuction
#define WRITESTSRAM 0b1   //!< Write SRAM status register instruction
#define READSTSRAM  0b101 //!< Read SRAM status register instruction

/*!
 * \brief Initialize SRAM with mode value
 * \param[in] mode One of defined modes
 */
void sram_init(byte mode);

/*!
 * \brief Read SRAM status register
 * \return SRAM status register
 */
byte read_st_sram(void);

/*!
 * \brief Write data to SRAM on address addr
 * \param[in] data Data byte to write to SRAM
 * \param[in] addr SRAM Address to write data byte
 */
void write_sram_byte(byte data, unsigned int addr);

/*!
 * \brief Read byte from SRAM
 * \param[in] addr Address to read byte from SRAM
 * \return Readed byte
 */
byte read_sram_byte(unsigned int addr);

#endif //_SRAMH
