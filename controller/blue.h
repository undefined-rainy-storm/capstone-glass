#ifndef BLUE_H
#define BLUE_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "esp_camera.h"

#define DEVICE_NAME         "ESP32-CAM"
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

#define MTU_SIZE 512

#define DELAY_TRANSMISSION 10
#define DELAY_BETWEEN_CHUNK 10

class BlueController {
private:
  BlueController();
  BlueController(const BlueController &other) = delete;
  BlueController &operator=(const BlueController &other) = delete;
public:
  static BlueController *getInstance();
  BLEServer *pServer;
  BLECharacteristic *pCharacteristic;
  bool deviceConnected;
  void sendFrame(uint8_t* frame_buffer, size_t frame_length);
};

void initBLE();
void loopBLE();

#endif
