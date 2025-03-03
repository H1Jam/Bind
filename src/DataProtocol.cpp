#include "DataProtocol.h"
#include "Arduino.h"
#include "crc16.h"
//#define DEBUG_MSG
uint16_t crcCalc;
uint16_t crcRcv;

unsigned long mLastDigitTimeStamp = 0;
void printArray(uint8_t const *buffer, size_t len);

uint16_t DataParser::update(uint8_t inp)
{
  #ifdef DEBUG_MSG
  Serial.print(inp, HEX);
  #endif
  size_t res = slPacker.decode(inp);
  if (res > 0)
  {
    if (checkCRC(slPacker.buf, res))
    {
      return res;
    }
  }
  return 0;
}

size_t DataParser::sendFrame(uint8_t *destBuffer, uint8_t const *buffer, size_t len)
{
  if (len < 1)
    return 0;
  if (len > MAX_DATA_LENGHT)
    return 0;
  destBuffer[0] = toAndroid & 0xFF;
  destBuffer[1] = VERSIONID & 0xFF;
  memcpy(destBuffer + 2, buffer, len);
  uint16_t crcTmp = crc16(destBuffer, len + 2);
  destBuffer[len + 2] = crcTmp & 0xFF;
  destBuffer[len + 3] = (crcTmp >> 8) & 0xFF;
  return SLPacker::encode(destBuffer, len + 4);
}

size_t DataParser::sendFrame(uint8_t *destBuffer, uint8_t const *buffer, size_t len, Stream *stream)
{
  size_t size = sendFrame(destBuffer, buffer, len);
  if (size > 0)
  {
    stream->write(destBuffer, size);
  }
  return size;
}

bool isTimedOut()
{
  if ((millis() - mLastDigitTimeStamp) > 100)
  {
    mLastDigitTimeStamp = millis();
    return true;
  }
  mLastDigitTimeStamp = millis();
  return false;
}

// Header[3]+Len[1]+Payload[Len]+CRC16[2]
bool checkCRC(uint8_t const *buffer, size_t len)
{
  printArray(buffer, len);
  crcCalc = crc16(buffer, len - 2);
  memcpy(&crcRcv, buffer + len - 2, 2);
  if (crcCalc == crcRcv)
  {
    return true;
  }
  else
  {
#ifdef DEBUG_MSG
    Serial.print("\nBad CRC! CALC =");
    Serial.print(crcCalc);
    Serial.print(", Rcv =");
    Serial.println(crcRcv);
    // printArray(buffer, len);
#endif
    return false;
  }
}

// Legacy
// int sendFrame(uint8_t *destBuffer, uint8_t const *buffer, size_t len)
// {
//   if (len < 1)
//     return 0;
//   if (len > MAX_DATA_LENGHT)
//     return 0;
//   memcpy(destBuffer, dataHeader, 3);
//   destBuffer[3] = (len + 4) & 0xFF;
//   destBuffer[4] = toAndroid & 0xFF;
//   destBuffer[5] = VERSIONID & 0xFF;
//   // Todo: add a protocol version Id here. 1 byte!
//   memcpy(destBuffer + 6, buffer, len);
//   uint16_t crcTmp = crc16(buffer, len);
//   destBuffer[6 + len] = crcTmp & 0xFF;
//   destBuffer[6 + len + 1] = (crcTmp >> 8) & 0xFF;
//   return len + 8;
// }

void printArray(uint8_t const *buffer, size_t len)
{
#ifdef DEBUG_MSG
  Serial.print("\n------------\n[");
  for (int i = 0; i < (len); i++)
  {
    Serial.print(buffer[i]);
    Serial.print(", ");
  }
  Serial.print("]\n------------\n");
#endif
}
