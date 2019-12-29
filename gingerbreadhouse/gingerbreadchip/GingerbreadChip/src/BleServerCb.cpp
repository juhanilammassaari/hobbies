#include <HardwareSerial.h>
#include "BleServerCb.h"

BleServerCb::BleServerCb()
{
}

BleServerCb::~BleServerCb()
{
}

void BleServerCb::onConnect(BLEServer* pServer)
{
    Serial.print("Client connect");
    ++clientsConnected;
}

void BleServerCb::onDisconnect(BLEServer* pServer)
{
    Serial.print("Client disconnect");
    --clientsConnected;
}

