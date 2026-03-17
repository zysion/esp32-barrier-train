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

// Define global variables and constants here

// motion sensor
extern bool motionDetected;
#define MOTION_SENSOR_PIN 36

// distance sensor
extern TaskHandle_t distanceMeasurementTaskHandle;
extern float distance;
#define TRIGGER_PIN 41
#define ECHO_PIN 42

// Alert & Buzzer
#define ALERT_LED_PIN 38
#define BUZZER_PIN 39
#define UNKNOWN -1 
#define SAFE 0 // asian pro max
#define DANGER 1 // 5 - 10
#define ALERT 2 // duoi 5

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