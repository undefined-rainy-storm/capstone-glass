#include <Arduino.h>
#include "blue.h"
#include "blue_controller.h"

BlueController *blueController;

void initBlue() {
  blueController = new BlueController(DEVICE_NAME);
  blueController->begin();
}

void loopBlue() {
  /*if (blueController->isConnected()) {
    blueController->getCharacteristic()->setValue("Hello World");
    blueController->getCharacteristic()->notify();
  }*/
}
