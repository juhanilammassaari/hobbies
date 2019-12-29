#include "Ble.h"
#include "BleServerCb.h"

constexpr auto SERVICE_UUID = ("017353b6-9303-4d9a-b4a2-470971bfe049");
constexpr auto CHARACTERISTIC_UUID = ("71fcc424-f36d-44c3-a8cc-8d94d2bb6fcb");
constexpr auto CHARACTERISTIC_DEFAULT_VALUE = ("");
Ble::Ble()
{
}

Ble::~Ble()
{
}

void Ble::Setup() 
{
    BLEDevice::init("Gingerbread house");
    this->pServer = BLEDevice::createServer();
    this->pService = pServer->createService(SERVICE_UUID);
    BLECharacteristic* pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

    pCharacteristic->setValue(CHARACTERISTIC_DEFAULT_VALUE);
    
    this->pService->start();

    this->pAdvertising = BLEDevice::getAdvertising();
    this->pAdvertising->addServiceUUID(SERVICE_UUID);
    this->pAdvertising->setScanResponse(true);
    this->pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    this->pAdvertising->setMinPreferred(0x12);

    pServer->setCallbacks(new BleServerCb());

    this->pLedCharacteristic = new BleCharacteristicsLed(pCharacteristic);
    

    BLEDevice::startAdvertising();
}

BleCharacteristicsLed* Ble::getLedCharacteristic()
{
    return this->pLedCharacteristic;
}