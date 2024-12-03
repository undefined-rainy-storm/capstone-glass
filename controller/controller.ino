#include <Arduino.h>
#include "config.h"
#include "blue.h"
#include "cam.h"
#include "display.h"

void setup() {
  Serial.begin(SERIAL_SPEED);
  Serial.println("Starting ESP32-CAM BLE Server");
  
  initBLE();
  initCamera();
  initDisplay();
}

void loop() {
  loopBLE();
  loopCamera();
  loopDisplay();
}
