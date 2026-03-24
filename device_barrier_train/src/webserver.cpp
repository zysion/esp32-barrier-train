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
                Serial.printf("Received from client %u: ", client->id());
                for(size_t i=0; i<len; i++) { Serial.print((char)data[i]); }
                Serial.println();
                JsonDocument doc;
                DeserializationError error = deserializeJson(doc, data);
                if (!error) {
                    const char* command = doc["type"];
                    if (strcmp(command, "Mode") == 0) {
                        const char* mode = doc["mode"];
                        if (strcmp(mode, "AUTO") == 0) {
                            AUTO_mode = true;
                            Serial.println("Switched to AUTO mode");
                        } else if (strcmp(mode, "MANUAL") == 0) {
                            AUTO_mode = false;
                            Serial.println("Switched to MANUAL mode");
                        }
                    } else if (strcmp(command, "barrier_status") == 0) {
                        const char* action = doc["action"];
                        if (strcmp(action, "open") == 0) {
                            if (!isopenbarrier) {
                                openBarrier();
                                sendalertstatus_SAFE(); // Update webserver with safe status when barrier is opened
                            }
                            Serial.println("Barrier opened via webserver");
                        } else if (strcmp(action, "close") == 0) {
                            if (isopenbarrier) {
                                closeBarrier();
                            }
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
    
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/style.css", "text/css");
    });
    
    server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request) {
        String json = "{";
        json += "\"autoMode\":" + String(AUTO_mode ? "true" : "false") + ",";
        json += "\"barrierOpen\":" + String(isopenbarrier ? "true" : "false") + ",";
        json += "\"trespassing\":" + String(motionDetected ? "true" : "false"); 
        json += "}";
        request->send(200, "application/json", json);
    });
    
    server.begin();
    webserverisrunning = true;
    Serial.println("WebServer started");
}


void sendbarrierstatus() {
    String status = isopenbarrier ? "open" : "close";
    ws.textAll("{\"type\":\"barrierstatus\",\"value\":\"" + status + "\"}");
}

void sendalertstatus_SAFE() {
    ws.textAll("{\"type\":\"alert\",\"value\":\"SAFE\"}");
}

void sendalertstatus_DANGER() {
    ws.textAll("{\"type\":\"alert\",\"value\":\"DANGER\"}");
}


void runWebServer(void *parameter) {
    connectwebserver();
    while (true) {
        ws.cleanupClients();
        sendbarrierstatus();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}