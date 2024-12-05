#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define I2C_SDA 15
#define I2C_SCL 14
#define I2C_FREQ 100000

#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   64
#define OLED_RESET      -1
#define SCREEN_ADDRESS  0x3C

class DisplayController {
private:
  DisplayController();
  DisplayController(const DisplayController &other) = delete;
  DisplayController &operator=(const DisplayController &other) = delete;
public:
  static DisplayController *getInstance();
  Adafruit_SSD1306 display;
  TwoWire i2cBus;
};

void initDisplay();
void loopDisplay();

#endif