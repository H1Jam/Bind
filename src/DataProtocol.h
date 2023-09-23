#ifndef __DATAPROTOCOL_H
#define __DATAPROTOCOL_H
#include <stdint.h>
#include <string.h>
#include "Stream.h"
#include "SLPacker.hpp"
#define MAX_DATA_LENGHT 100

static uint8_t VERSIONID = 0;

uint8_t const dataHeader[3] = {199, 201, 176};
enum DataDirection
{
  toAndroid,
  fromAndroid
};

int sendFrame(uint8_t *destBuffer, uint8_t const *buffer, size_t len);
bool checkCRC(uint8_t const *buffer, size_t len);
class DataParser
{
private:
  SLPacker slPacker;
  uint8_t dataIn[3] = {0, 0, 0};
  int bufIndex = 0;
  int dataStep = 0;
  int dataLength = 0;

public:
  static size_t sendFrame(uint8_t *destBuffer, uint8_t const *buffer, size_t len);
  static size_t sendFrame(uint8_t *destBuffer, uint8_t const *buffer, size_t len, Stream *stream);
  uint8_t *buf = slPacker.buf;
  int update(uint8_t inp);
};

#endif /* __DATAPROTOCOL_H */
