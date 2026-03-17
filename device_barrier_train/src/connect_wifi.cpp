#include <global.h>

void connectWiFi(const char* ssid, const char* password) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    Serial.print("Connecting to WiFi");

    unsigned long startAttemptTime = millis();
    const unsigned long timeout = 15000;

    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < timeout) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println();
        Serial.println("WiFi connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println();
        Serial.println("WiFi connection failed!");
    }
}

bool isWiFiConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void disconnectWiFi() {
    WiFi.disconnect(true);
    Serial.println("WiFi disconnected.");
}