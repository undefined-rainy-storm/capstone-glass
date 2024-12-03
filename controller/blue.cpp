#include <Arduino.h>
#include "blue.h"


BlueController::BlueController() : 
  deviceConnected(false),
  pServer(nullptr),
  pCharacteristic(nullptr) {
}

BlueController *BlueController::getInstance() {
  static BlueController instance;
  return &instance;
}

BlueController *blueController = BlueController::getInstance();

void BlueController::sendFrame(uint8_t* frame_buffer, size_t frame_length) {
  if (!blueController->deviceConnected) return;

  // Send frame size first (4 bytes)
  uint8_t size_buffer[4];
  size_buffer[0] = (frame_length >> 24) & 0xFF;
  size_buffer[1] = (frame_length >> 16) & 0xFF;
  size_buffer[2] = (frame_length >> 8) & 0xFF;
  size_buffer[3] = frame_length & 0xFF;
  blueController->pCharacteristic->setValue(size_buffer, 4);
  blueController->pCharacteristic->notify();
  delay(DELAY_TRANSMISSION);

  // Send frame data in chunks
  size_t chunk_size = MTU_SIZE - 3; // Account for BLE overhead
  size_t sent = 0;
  
  while (sent < frame_length) {
    size_t remaining = frame_length - sent;
    size_t current_chunk_size = (remaining < chunk_size) ? remaining : chunk_size;
    
    blueController->pCharacteristic->setValue(&frame_buffer[sent], current_chunk_size);
    blueController->pCharacteristic->notify();
    
    sent += current_chunk_size;
    delay(DELAY_BETWEEN_CHUNK);
  }
}

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      blueController->deviceConnected = true;
      Serial.println("Device connected");
    }

    void onDisconnect(BLEServer* pServer) {
      blueController->deviceConnected = false;
      Serial.println("Device disconnected");
      // Restart advertising to allow new connections
      blueController->pServer->startAdvertising();
    }
};

void initBLE() {
  BLEDevice::init(DEVICE_NAME);
  
  blueController->pServer = BLEDevice::createServer();
  blueController->pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = blueController->pServer->createService(SERVICE_UUID);

  blueController->pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );

  blueController->pCharacteristic->addDescriptor(new BLE2902());

  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // functions that help with iPhone connections issue
  BLEDevice::startAdvertising();

  BLEDevice::setMTU(MTU_SIZE);
  
  Serial.println("BLE device ready");
}

void loopBLE() {
}
