#include "blue_controller.h"

#include <BLEServer.h>
#include <BLEDevice.h>
#include <BLE2902.h>
#include "blue_connection.h"

BlueController::BlueController(std::string deviceName) : deviceName(deviceName) {
  this->connection = new BlueConnection();
}

//void BlueController::taskServer(void *params) {
void BlueController::taskServer(BlueController *controller) { 
  // Cast
  // BlueController *controller = (BlueController *)params;

  // Device
  BLEDevice::init(controller->deviceName);
  
  // Server
  BLEServer *server = BLEDevice::createServer();
  server->setCallbacks(controller->connection);

  // Service
  BLEService *service = server->createService(SERVICE_UUID);

  // Characteristic
  controller->characteristic = service->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_WRITE |
    BLECharacteristic::PROPERTY_NOTIFY
  );

  // Descriptor
  controller->characteristic->addDescriptor(new BLE2902());

  // Service
  service->start();

  // Advertise
  BLEAdvertising *advertising = server->getAdvertising();
  advertising->addServiceUUID(service->getUUID());
  advertising->setScanResponse(false);
  advertising->setMinPreferred(0x0);
  // return;
  // advertising->start();
  BLEDevice::startAdvertising();

  // vTaskDelay(portMAX_DELAY);
}

bool BlueController::isConnected() {
  return this->connection->connected;
}

void BlueController::begin() {
  // xTaskCreate(this->taskServer, "server", 20000, (void *)this, 5, NULL);
  this->taskServer(this);
}

void BlueController::end() {
  BLEDevice::deinit(true);
}

BLECharacteristic *BlueController::getCharacteristic() {
  return this->characteristic;
}
