#include <Arduino.h>
#include "display.h"

DisplayController::DisplayController() :
  i2cBus(0),
  display(SCREEN_WIDTH, SCREEN_HEIGHT, &i2cBus, OLED_RESET)
{}

DisplayController *DisplayController::getInstance() {
  static DisplayController instance;
  return &instance;
}

DisplayController *displayController = DisplayController::getInstance();

void initDisplay() {
  displayController->i2cBus.begin(I2C_SDA, I2C_SCL, I2C_FREQ);

  Serial.println("Initialize display");

  if (!displayController->display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.printf("SSD1306 OLED display failed to initalize.\nCheck that display SDA is connected to pin %d and SCL connected to pin %d\n", I2C_SDA, I2C_SCL);
    while (true);
  }
  displayController->display.clearDisplay();
  displayController->display.setCursor(0, 0);
  displayController->display.setTextSize(2);
  displayController->display.setTextColor(SSD1306_WHITE);
  displayController->display.print("Hello\nWorld!");
  displayController->display.display();
}

void loopDisplay() {}
