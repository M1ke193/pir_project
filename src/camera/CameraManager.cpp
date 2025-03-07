#include "CameraManager.h"

void initCamera()
{
    if (!SPIFFS.begin(true))
    {
        Serial.println("Failed when mounting SPIFFS");
        ESP.restart();
    }
    else
    {
        delay(1000);
        Serial.println("SPIFFS mounted successfully");
    }

    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sccb_sda = SIOD_GPIO_NUM;
    config.pin_sccb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 2;
    if (HIGH_RESOLUTION)
    {
        config.frame_size = FRAMESIZE_UXGA;
        config.jpeg_quality = 10;
    }
    else
    {
        config.frame_size = FRAMESIZE_SVGA;
        config.jpeg_quality = 12;
    }

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK)
    {
        Serial.printf("Camera init failed with error 0x%x", err);
        return;
    }
}

void capturePicture(int imageQuanatity)
{
    camera_fb_t *frameBuffer = NULL;

    // SKIP FRAME FOR STABLE IMAGE
    for (int i = 0; i < SKIP_FRAME; i++)
    {
        frameBuffer = esp_camera_fb_get();
        esp_camera_fb_return(frameBuffer);
        frameBuffer = NULL;
    }

    for (int i = 0; i < imageQuanatity; i++)
    {
        frameBuffer = NULL;
        frameBuffer = esp_camera_fb_get();

        if (!frameBuffer)
        {
            Serial.println("Camera capture failed");
            continue;
        }

        File file = SPIFFS.open("/" + String(i) + ".jpg", FILE_WRITE);

        if (file)
        {
            file.write(frameBuffer->buf, frameBuffer->len);
            Serial.print(file.size());
            Serial.println(" bytes");
        }

        file.close();
        esp_camera_fb_return(frameBuffer);
    }
}
