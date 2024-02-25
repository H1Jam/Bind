#ifndef __CRC16_H
#define __CRC16_H

#include <stdint.h>
#include <stddef.h>

#define CRC16_INIT 0x1D0F
/**
 * Calculates the CRC-16 checksum for the given buffer.
 *
 * @param buffer The input buffer containing the data to calculate the checksum for.
 * @param len The length of the input buffer.
 * @return The calculated CRC-16 checksum.
 */
uint16_t crc16(uint8_t const *buffer, size_t len);

#endif /* __CRC16_H */
