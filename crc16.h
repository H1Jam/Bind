#ifndef __CRC16_H
#define __CRC16_H
#include <stdint.h>
#include <stddef.h>

#define CRC16_INIT  0x1D0F
uint16_t crc16(uint8_t const *buffer, size_t len);

#endif /* __CRC16_H */
