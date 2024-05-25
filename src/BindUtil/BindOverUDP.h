#ifndef BINDOVERUDP_H
#define BINDOVERUDP_H

#include <Arduino.h>
#include <Stream.h>
#include <AsyncUDP.h>
#include "Bind.hpp"
#define UDP_DEBUG_MSG 0 // Set to 1 to enable debug messages

/*
  * This class is used to send and receive data over UDP to be used 
  * with the Bind class.
*/
class UDPStream : public Stream
{
private:
    bool sendPackets = false;
    static uint8_t discoveryMsg[];
    static uint8_t connectMsg[];
    static uint8_t stopMsg[];
    static uint8_t bindHeartbeat[];
    static uint16_t bindPort;
    IPAddress canvasIP = IPAddress(0, 0, 0, 0);
    void handleUDP(UDPStream& udpStream, AsyncUDPPacket& packet);
    Bind *_bind;
    AsyncUDP udp;
    uint32_t lastHeartbeat = 0;
    const char* bindname;
public:
    bool begin(const char* bindname, Bind &bind){
      this->_bind = &bind;
      this->bindname = bindname;
      if (this->udp.listen(this->bindPort)) {
        this->udp.onPacket([this](AsyncUDPPacket packet) {
           this->handleUDP(*this, packet);
        });
        return true;
      }
      return false;
    }

    size_t write(const uint8_t *buffer, size_t size) override
    {
      if (!this->sendPackets)
      {
        return 0;
      }

      if (this->sendPackets == true && this->lastHeartbeat + 5000 > millis())
      {
        this->udp.writeTo(buffer, size, this->canvasIP, this->bindPort);
        #if UDP_DEBUG_MSG
        Serial.print("TX: ");
        Serial.print(this->canvasIP);
        Serial.print(" - Hex[");
        for (int i = 0; i < size; i++)
        {
          Serial.print(buffer[i], HEX);
          Serial.print(" ");
        }
        Serial.println("]");
        #endif
        return size;
      }
      else
      {
        this->sendPackets = false;
        this->canvasIP = IPAddress(0, 0, 0, 0);
        return 0;
      }
    }

    int available() override { return 0; }
    int read() override { return 0; }
    int peek() override { return 0; }
    void flush() override {}
    size_t write(uint8_t) override { return 0; }
};

#endif // BINDOVERUDP_H
