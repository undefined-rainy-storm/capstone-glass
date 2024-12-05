#ifndef BLUE_CONNECTION_H
#define BLUE_CONNECTION_H

#include <BLEServer.h>
#include "BLE2902.h"
#include "BLECharacteristic.h"

class BlueConnection : public BLEServerCallbacks {
public:
  BlueConnection(void);
  bool connected = false;
  void onConnect(BLEServer* pServer);
  void onDisconnect(BLEServer* pServer);
  BLECharacteristic* inputKeyboard;
  BLECharacteristic* outputKeyboard;
  BLECharacteristic* inputMediaKeys;
};

#endif
