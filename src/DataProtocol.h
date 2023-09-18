#ifndef __DATAPROTOCOL_H
#define __DATAPROTOCOL_H
#include <stdint.h>
#include <string.h>
#include "Stream.h"
#include "SLPacker.hpp"
#define MAX_DATA_LENGHT 100
#define RGB(r, g, b) ((int32_t)((uint8_t)(b)) | ((int32_t)(g) << 8) | (((int32_t)(uint8_t)(r)) << 16) | 0xFF000000)
#define RGBA(r, g, b, a) ((int32_t)((uint8_t)(b)) | ((int32_t)(g) << 8) | (((int32_t)(uint8_t)(r)) << 16) | ((int32_t)((uint8_t)(a)) << 24))

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
