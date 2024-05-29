#ifndef __ESP32BLE_H__
#define __ESP32BLE_H__
#ifdef ARDUINO_ARCH_ESP32

#include "Bind.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Arduino.h>
#include "Stream.h"

class BleCallbacks : public BLEServerCallbacks
{
private:
    bool *_deviceConnected;
public:
    // Get _deviceConnected pointer
    BleCallbacks(bool &deviceConnected) : _deviceConnected(&deviceConnected){}

    void onConnect(BLEServer *pServer)
    {
        *this->_deviceConnected = true;
    }

    void onDisconnect(BLEServer *pServer)
    {
        *this->_deviceConnected = false;
        delay(500);                  // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
    }
};

class BleRXCallbacks : public BLECharacteristicCallbacks
{
private:
    Bind *_bind;

public:
    BleRXCallbacks(Bind &bind)
    {
        this->_bind = &bind;
    }

    void onWrite(BLECharacteristic *pCharacteristic) override;
};

/**
 * @brief esp32 BLE stream class.
 *
 * @details This class is used to create a stream object that can be used to
 * send data over BLE.
 */
class BleStream : public Stream
{
private:
    BLEServer *pServer = NULL;
    BLECharacteristic *pTxCharacteristic;
    bool deviceConnected = false;
    bool oldDeviceConnected = false;
    BleRXCallbacks *rxCallbacks = NULL;
    BleCallbacks *bleCallbacks = NULL;

public:
    /**
     * @brief Initialize the BLE service.
     *
     * @details This function is used to initialize a BLE stream.
     * You can pass the returning object to bind.init function.
     *
     * @param bind The bind object.
     * @param bindname The name of the device.
     *
     * @return The BLE stream object.
     */
    bool begin(const char *bindname, Bind &bind);

    // Same as above but with different order of arguments
    bool begin(Bind &bind, const char *bindname);
    size_t write(const uint8_t *buffer, size_t size) override;
    int available() override { return 0; }
    int read() override { return 0; }
    int peek() override { return 0; }
    void flush() override {}
    size_t write(uint8_t) override { return 0; }
};

#endif // ARDUINO_ARCH_ESP32
#endif // __ESP32BLE_H__
