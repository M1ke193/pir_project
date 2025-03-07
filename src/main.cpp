#include "Arduino.h"
#include "pins.h"
#include "./camera/CameraManager.h"
#include "./wifi/WifiManager.h"
#include "./gmail/MailManager.h"

// NUMBER OF PHOTO WILL
#define NUM_IMAGE 5
#define EMAIL_INTERVAL 15000

// WIFI CREDENTIALS
const char *SSID = "";
const char *PASSWORD = "";

unsigned long lastDetected = 0;

void setup()
{
  Serial.begin(115200);
  Serial.printf("Wait for setup ...");
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN_INTERNAL, OUTPUT);
  connectWifi(SSID, PASSWORD);
  initCamera();
  
  // delay 15 second for stable
  delay(15000);
  digitalWrite(LED_PIN, HIGH);
}

void loop()
{
  if (digitalRead(PIR_PIN) == HIGH && millis() - lastDetected > EMAIL_INTERVAL)
  {
    digitalWrite(LED_PIN_INTERNAL, HIGH);
    lastDetected = millis();
    Serial.println("Motion detected, capturing image...");
    capturePicture(NUM_IMAGE);
    digitalWrite(LED_PIN_INTERNAL, LOW);
    //SEND EMAIL AFTER DETECTED
    sendEmail(NUM_IMAGE);
  }
}
