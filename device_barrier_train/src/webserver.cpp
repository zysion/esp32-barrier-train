#include "global.h"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

bool webserverisrunning = false;

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    switch(type) {
        case WS_EVT_CONNECT:
            Serial.printf("WebSocket client connected: %u\n", client->id());
            break;
        case WS_EVT_DISCONNECT:
            Serial.printf("WebSocket client disconnected: %u\n", client->id());
            break;
        case WS_EVT_DATA:
        {
            AwsFrameInfo *info = (AwsFrameInfo*)arg;
            if(info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
                data[len] = 0; // Null-terminate the incoming message
                Serial.printf("Received from client %u: %s\n", client->id(), (char*)data);
                JsonDocument doc;
                DeserializationError error = deserializeJson(doc, data);
                if (!error) {
                    const char* command = doc["type"];
                    if (strcmp(command, "Mode") == 0) {
                        const char* mode = doc["mode"];
                        if (strcmp(mode, "AUTO") == 0) {
                            system_mode = true;
                            Serial.println("Switched to AUTO mode");
                        } else if (strcmp(mode, "MANUAL") == 0) {
                            system_mode = false;
                            Serial.println("Switched to MANUAL mode");
                        }
                    } else if (strcmp(command, "barrier_status") == 0) {
                        const char* action = doc["action"];
                        if (strcmp(action, "open") == 0) {
                            openBarrier();
                            Serial.println("Barrier opened via webserver");
                        } else if (strcmp(action, "close") == 0) {
                            closeBarrier();
                            Serial.println("Barrier closed via webserver");
                        }
                    }
                }
            }
            // Handle incoming data if needed
            break;
        }
        case WS_EVT_PING:
            break;
        case WS_EVT_PONG:
            break;
        case WS_EVT_ERROR:
            break;
    }

}

void connectwebserver() {
  if (!LittleFS.begin(true)) {
        Serial.println("LittleFS mount failed");
        return;
    }
    Serial.println("LittleFS mounted successfully");
    
    Serial.print("Web Server IP: ");
    Serial.println(WiFi.localIP());
    
    ws.onEvent(onEvent);
    server.addHandler(&ws);
    
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/index.html", "text/html");
    });
    
    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/script.js", "application/javascript");
    });
    
    server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/styles.css", "text/css");
    });
    
    server.begin();
    webserverisrunning = true;
    Serial.println("WebServer started");
}


void sendbarrierstatus() {
    String status = motionDetected ? "Closed" : "Open";
    ws.textAll("{\"type\":\"barrierstatus\",\"status\":\"" + status + "\"}");
}

void sendtrespassingalert() {
    ws.textAll("{\"type\":\"trespass\",\"value\":\"trespass\"}");
}

void runWebServer(void *parameter) {
    connectwebserver();
    while (true) {
        ws.cleanupClients();
        sendbarrierstatus();
        sendtrespassingalert();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}