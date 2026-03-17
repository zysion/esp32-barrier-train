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

extern bool motionDetected;

//include module
#include "motion_sensor_module.h"
#include "Servo_module.h"
#include "webserver.h"
#include "connect_wifi.h"
#include "LCD_module.h"
#include "ledblinky.h"
#include "LED_RGB.h"
#include "distance_module.h"



#endif // GLOBAL_H