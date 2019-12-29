#pragma once

#include <BLEServer.h>

class BleServerCb : public BLEServerCallbacks
{
public:
    BleServerCb();
    virtual ~BleServerCb();
    void onConnect(BLEServer* pServer);
    void onDisconnect(BLEServer* pServer);
private:
    unsigned int clientsConnected;
};
