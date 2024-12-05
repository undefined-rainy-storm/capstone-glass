#ifndef CAM_H
#define CAM_H

#include "esp_camera.h"

#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

#define XCLK_FREQ 20000000
#define PIXEL_FORMAT PIXFORMAT_JPEG

#define FRAME_BUFFER_SIZE 8192

#define LEDC_CHANNEL       LEDC_CHANNEL_0
#define LEDC_TIMER         LEDC_TIMER_0

#define FRAME_SIZE FRAMESIZE_QVGA
#define JPEG_QUALITY 20
#define FB_COUNT 1

#define DELAY_BETWEEN_FRAME 100

void initCamera();
void loopCamera();

#endif
