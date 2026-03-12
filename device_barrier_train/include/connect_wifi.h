#ifndef CONNECT_WIFI_H
#define CONNECT_WIFI_H

#include "global.h"

void connectWiFi(const char* ssid, const char* password);
bool isWiFiConnected();
void disconnectWiFi();

#endif // CONNECT_WIFI_H