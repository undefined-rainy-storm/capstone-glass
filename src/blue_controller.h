#ifndef BLUE_CONTROLLER_H
#define BLUE_CONTROLLER_H

#include "blue_connection.h"

#define DEVICE_NAME         "ESP32-CAM"
#define SERVICE_UUID        "10f96d87-446f-49e7-8bdf-9828d3804acc"
#define CHARACTERISTIC_UUID "5be13433-d1d2-44bf-99b8-047c9c62b9eb"

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
