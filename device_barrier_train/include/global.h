#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>
#include <HCSR04.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

// Define global variables and constants here

// define WiFi credentials
#define SSID "TECNO POVA 6"
#define PASSWORD "zysion123"

// motion sensor
extern volatile bool motionDetected;
extern volatile bool isopenbarrier; //true for open, false for close
#define MOTION_SENSOR_PIN 36

// distance sensor
extern volatile float distance;
#define TRIGGER_PIN 41
#define ECHO_PIN 42

// Alert & Buzzer
#define ALERT_LED_PIN 38
#define BUZZER_PIN 39
#define UNKNOWN -1 
#define SAFE 0 // asian pro max
#define DANGER 1 // 5 - 10
#define ALERT 2 // duoi 5
extern TaskHandle_t alertTaskHandle;

// SERVO
#define SERVO_PIN 37
extern Servo barrierServo;

// LCD
#define I2C_SDA 20
#define I2C_SCL 21

// System mode
extern volatile bool AUTO_mode; // false for manual, true for auto

//-------------------------------------------------------------------------

//include module
#include "motion_sensor_module.h"
#include "Servo_module.h"
#include "webserver.h"
#include "connect_wifi.h"
#include "LCD_module.h"
#include "distance_module.h"
#include "alert_module.h"



#endif // GLOBAL_H