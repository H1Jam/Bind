#ifndef BINDOVERUDP_H
#define BINDOVERUDP_H
#if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_RASPBERRY_PI_PICO_2W) || defined(ARDUINO_ARCH_ESP8266)
#if __has_include("BindUserConfig.h")
#include "BindUserConfig.h"
#endif
#ifndef BIND_DISABLE_WIFI
#include "Bind.h"
#include <Arduino.h>
#include <Stream.h>
#if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_RASPBERRY_PI_PICO_2W)
// This takes too much memory on boards with limited memory, so we let the user include it if needed
//#include <WiFi.h> // For ESP32 and RP2040 with WiFi support
#include <AsyncUDP.h> // Both ESP32 and RP2040 support AsyncUDP
#elif defined(ARDUINO_ARCH_ESP8266)
// This takes too much memory on boards with limited memory, so we let the user include it if needed
//#include <ESP8266WiFi.h>
#include <BindUtil/BindAsyncUDP.h> // ESP8266 uses ESPAsyncUDP
#endif

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
    UDPStream() : canvasIP(IPAddress(0, 0, 0, 0)), sendPackets(false), _bind(nullptr) {}
    bool begin(const char* bindname, Bind &bind);
    bool begin(Bind &bind, const char* bindname);
    size_t write(const uint8_t *buffer, size_t size) override;
    int available() override { return 0; }
    int read() override { return 0; }
    int peek() override { return 0; }
    void flush() override {}
    size_t write(uint8_t) override { return 0; }
};
#endif // BIND_DISABLE_WIFI
#endif // defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_RP2040)
#endif // BINDOVERUDP_H
