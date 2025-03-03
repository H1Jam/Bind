#ifndef __DATAPROTOCOL_H
#define __DATAPROTOCOL_H
#include <stdint.h>
#include <string.h>
#include "Stream.h"
#include "SLPacker.hpp"

static uint8_t VERSIONID = 0;

enum DataDirection
{
  toAndroid,
  fromAndroid
};

bool checkCRC(uint8_t const *buffer, size_t len);
class DataParser
{
private:
  SLPacker slPacker;

public:
  static size_t sendFrame(uint8_t *destBuffer, uint8_t const *buffer, size_t len);
  static size_t sendFrame(uint8_t *destBuffer, uint8_t const *buffer, size_t len, Stream *stream);
  uint8_t *buf = slPacker.buf;
  uint16_t update(uint8_t inp);
};

#endif /* __DATAPROTOCOL_H */
