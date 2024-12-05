#include <Arduino.h>
#include "esp_task_wdt.h"
#include "config.h"

#include "blue.h"
#include "cam.h"
#include "display.h"

void setup() {
  Serial.begin(SERIAL_SPEED);
  esp_task_wdt_init(10, true); // 10 second timeout
  esp_task_wdt_add(NULL);
  Serial.println("Initalizing Started");
  
  Serial.printf("Free heap: %d\n", ESP.getFreeHeap());
  Serial.printf("Free PSRAM: %d\n", ESP.getFreePsram());

  initBlue();
  initCamera();
  initDisplay();

  esp_task_wdt_reset();

  Serial.println("Initalizing Done");
}

void loop() {
  esp_task_wdt_reset();

  Serial.println("Loop Invoked");

  loopBlue();
  loopCamera();
  loopDisplay();
  Serial.printf("Free heap: %d\n", ESP.getFreeHeap());
  Serial.printf("Free PSRAM: %d\n", ESP.getFreePsram());

  Serial.println(".");
  delay(1000);
}
