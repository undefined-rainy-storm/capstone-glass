#include <Arduino.h>
#include <base64.h>
#include "blue.h"
#include "blue_controller.h"
#include "cam.h"
#include "defines.h"

BlueController *blueController;

void initBlue() {
  blueController = new BlueController(DEVICE_NAME);
  blueController->begin();
}

// BlueController & Camera Integrated
void loopBlueCamera() {
  if (blueController->isConnected()) {
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Camera capture failed");
      return;
    }
   String encodedStr = base64::encode(fb->buf, fb->len);
    const char* encodedData = encodedStr.c_str();
    size_t remainingLength = encodedStr.length();
    size_t offset = 0;

    while (remainingLength > 0) {
      size_t chunkSize = min(remainingLength, BLE_MTU_SIZE);
      
      blueController->getCharacteristic()->setValue(
        (uint8_t*)(encodedData + offset), 
        chunkSize
      );
      blueController->getCharacteristic()->notify();

      offset += chunkSize;
      remainingLength -= chunkSize;
      
      Serial.printf("Sent %d bytes, Remaining %d bytes. (%d)\n", chunkSize, remainingLength, offset);
      
      // Add delay between chunks
      delay(NOTIFY_DELAY);
    }

    esp_camera_fb_return(fb);

    uint16_t notifyEndMagic = 0x00;
    blueController->getCharacteristic()->setValue(notifyEndMagic);
    blueController->getCharacteristic()->notify();
    delay(NOTIFY_DELAY);
  }
}

void loopBlue() {
  Serial.println(blueController->isConnected() ? "Connected" : "Disconnected");
  loopBlueCamera();
}
