#include "blue_connection.h"

BlueConnection::BlueConnection(void) {
}

void BlueConnection::onConnect(BLEServer* server)
{
  this->connected = true;
}

void BlueConnection::onDisconnect(BLEServer* server)
{
  this->connected = false;
}
