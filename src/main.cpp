#include "Arduino.h"
#include "./camera/CameraManager.h"
#include "./wifi/WifiManager.h"
#include "./gmail/MailManager.h"

const int PIR_PIN = 14;
const int LED_PIN = 4;

// WIFI CREDENTIALS
const char *SSID = "";
const char *PASSWORD = "";

// NUMBER OF PHOTO WILL  
#define NUM_IMAGE 5

void setup()
{
  Serial.begin(115200);
  connectWifi(SSID, PASSWORD);
  initCamera();
  capturePicture(NUM_IMAGE);
  sendEmail(NUM_IMAGE);
}

void loop()
{
}
