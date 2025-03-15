#include "Arduino.h"
#include "pins.h"
#include "./camera/CameraManager.h"
#include "./wifi/WifiManager.h"
#include "./gmail/MailManager.h"
#include <HTTPClient.h>
#include "soc/soc.h"           // Disable brownour 
#include "soc/rtc_cntl_reg.h"  // Disable brownour 

// NUMBER OF PHOTO WILL
#define NUM_IMAGE 5
#define EMAIL_INTERVAL 10000

// WIFI CREDENTIALS
const char *SSID = "";
const char *PASSWORD = "";

String endPointSound = "http://192.168.1.100:80/play";

unsigned long lastDetected = 0;

void callSoundHTTPRequest() {
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    http.begin(endPointSound.c_str());
    int httpResponseCode = http.GET();
    http.end(); 
  }
}

void setup()
{
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout 
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
    callSoundHTTPRequest();
    Serial.println("Motion detected, capturing image...");
    capturePicture(NUM_IMAGE);
    digitalWrite(LED_PIN_INTERNAL, LOW);
    //SEND EMAIL AFTER DETECTED
    sendEmail(NUM_IMAGE);
  }
}
