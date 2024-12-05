#ifndef BLUE_CONTROLLER_H
#define BLUE_CONTROLLER_H

#include "blue_connection.h"

#define DEVICE_NAME         "ESP32-CAM"
#define SERVICE_UUID        (uint16_t) 0x1812
#define CHARACTERISTIC_UUID (uint16_t) 0x2A4D

class BlueController {
private:
  BlueConnection *connection;
  BLECharacteristic *characteristic;
  // static void taskServer(void *params);
  static void taskServer(BlueController *controller);
public:
  BlueController(std::string deviceName);
  std::string deviceName;
  bool isConnected();
  void begin();
  void end();
  BLECharacteristic *getCharacteristic();
};

#endif
