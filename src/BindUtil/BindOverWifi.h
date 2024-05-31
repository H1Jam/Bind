#ifndef BINDOVERUDP_H
#define BINDOVERUDP_H
#ifdef ARDUINO_ARCH_ESP32
#ifndef BL_ONLY_BIND
#include "Bind.h"
#include <Arduino.h>
#include <Stream.h>
#include <AsyncUDP.h>

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
    bool begin(const char* bindname, Bind &bind);
    bool begin(Bind &bind, const char* bindname);
    size_t write(const uint8_t *buffer, size_t size) override;
    int available() override { return 0; }
    int read() override { return 0; }
    int peek() override { return 0; }
    void flush() override {}
    size_t write(uint8_t) override { return 0; }
};
#endif // BL_ONLY_BIND
#endif // ARDUINO_ARCH_ESP32
#endif // BINDOVERUDP_H
