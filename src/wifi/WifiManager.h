#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include "SPI.h"

void connectWifi(const char *ssid, const char *password);

#endif

