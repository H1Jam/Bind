#ifndef __ESP32BLE_H__
#define __ESP32BLE_H__
#ifdef ARDUINO_ARCH_ESP32

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Arduino.h>
#include "Stream.h"
#include "bind.h"

extern BLEServer *pServer;
extern BLECharacteristic *pTxCharacteristic;
extern bool deviceConnected;
extern bool oldDeviceConnected;

/**
 * @brief esp32 BLE stream class.
 * 
 * @details This class is used to create a stream object that can be used to
 * send data over BLE.
 * 
 * @param writeCallback The callback function that will be called when need to 
 * write data to the stream.
 * 
 * @return The stream object.
 */
class BleStream : public Stream
{
private:
    void (*_writeCallback)(uint8_t *, size_t);
public:
    BleStream(void (*writeCallback)(uint8_t *, size_t))
    {
        _writeCallback = writeCallback;

    }
    size_t write(const uint8_t *buffer, size_t size) override
    {
        _writeCallback((uint8_t *)buffer, size);
        return size;
    }
    int available() override { return 0; }
    int read() override { return 0; }
    int peek() override { return 0; }
    void flush() override {}
    size_t write(uint8_t) override { return 0; }
};

class BleCallbacks : public BLEServerCallbacks
{
    void onConnect(BLEServer *pServer)
    {
        deviceConnected = true;
    };

    void onDisconnect(BLEServer *pServer)
    {
        deviceConnected = false;
        delay(500);                  // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
    }
};

void sendData(uint8_t *data, size_t size);

class BleRXCallbacks : public BLECharacteristicCallbacks
{
private:
     Bind *_bind;
public:
    BleRXCallbacks(Bind &bind)
    {
        this->_bind = &bind;
    }

    void onWrite(BLECharacteristic *pCharacteristic)
    {
        uint8_t *data = pCharacteristic->getData();
        size_t dataln = pCharacteristic->getLength();
        if (dataln > 0)
        {
             this->_bind->sync(data, dataln);
        }
    }
};

/**
 * @brief Initialize the BLE service.
 * 
 * @details This function is used to initialize a BLE stream. 
 * You can pass the returning object to bind.init(...,...) function.
 * 
 * @param bind The bind object.
 * 
 * @return The BLE stream object.
 */
BleStream* ble_init(Bind &bind, std::string deviceName);

#endif // ARDUINO_ARCH_ESP32
#endif // __ESP32BLE_H__
