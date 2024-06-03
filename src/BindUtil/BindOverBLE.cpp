#ifdef ARDUINO_ARCH_ESP32
#ifndef WIFI_ONLY_BIND
#include "BindOverBLE.h"
#define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

bool BleStream::begin(const char *deviceName, Bind &bind)
{
    this->rxCallbacks = new BleRXCallbacks(bind);
    BLEDevice::init(std::string(deviceName));
    BLEDevice::setMTU(64);
    this->pServer = BLEDevice::createServer();
    this->bleCallbacks = new BleCallbacks(this->deviceConnected);
    this->pServer->setCallbacks(this->bleCallbacks);
    BLEService *pService = pServer->createService(SERVICE_UUID);

    this->pTxCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID_TX,
        BLECharacteristic::PROPERTY_NOTIFY);

    this->pTxCharacteristic->addDescriptor(new BLE2902());

    BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID_RX,
        BLECharacteristic::PROPERTY_WRITE);

    pRxCharacteristic->setCallbacks(rxCallbacks);

    pService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);
    pAdvertising->setMaxPreferred(0x12);
    BLEDevice::startAdvertising();
    return true;
}

bool BleStream::begin(Bind &bind, const char *deviceName)
{
    return begin(deviceName, bind);
}

size_t BleStream::write(const uint8_t *buffer, size_t size) 
{
    if (!this->deviceConnected)
    {
        return 0;
    }
    this->pTxCharacteristic->setValue((uint8_t *)buffer, size);
    this->pTxCharacteristic->notify();
    delay(10);
    return size;
}

void BleRXCallbacks::onWrite(BLECharacteristic *pCharacteristic)
{
    size_t dataln = pCharacteristic->getLength();
    if (dataln > 0)
    {
        this->_bind->sync(pCharacteristic->getData(), dataln);
    }
}
#endif // WIFI_ONLY_BIND
#endif // ARDUINO_ARCH_ESP32
