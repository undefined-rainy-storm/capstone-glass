#include "blue_connection.h"

BlueConnection::BlueConnection(void) {
}

void BlueConnection::onConnect(BLEServer* server)
{
  this->connected = true;
  // Allow notifications for characteristics
  BLE2902* desc = (BLE2902*)this->inputKeyboard->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
  desc->setNotifications(true);
  
  // desc = (BLE2902*)this->inputMouse->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
  // desc->setNotifications(true);
}

void BlueConnection::onDisconnect(BLEServer* server)
{
  this->connected = false;
  // Disallow notifications for characteristics
  BLE2902* desc = (BLE2902*)this->inputKeyboard->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
  desc->setNotifications(false);

  server->getAdvertising()->start();
  
  //desc = (BLE2902*)this->inputMouse->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
  //desc->setNotifications(false);  
}
