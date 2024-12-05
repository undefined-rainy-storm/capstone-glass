#ifndef BLUE_CONTROLLER
#define BLUE_CONTROLLER

#include "BLEHIDDevice.h"
#include "BLECharacteristic.h"
#include "BleConnection.h"
#include "HIDTypes.h"

class BlueController {
private:
  BleConnection* connection;
  BLEHIDDevice* hid;
  BLECharacteristic* inputKeyboard;
  BLECharacteristic* outputKeyboard;
  BLECharacteristic* inputMediaKeys;
  static void taskServer(void* pvParameter);
public:
  BlueController(std::string deviceName = "Glass", uint8_t batteryLevel = 100);
  void setDeviceName(std::string device_name);
  void setProductId(uint16_t id);
  void begin(void);
  void end(void);
  bool isConnected(void);
  void setBatteryLevel(uint8_t level);
  uint8_t batteryLevel;
  std::string deviceName;
  uint16_t product_id;
};

#endif