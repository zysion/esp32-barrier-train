#ifndef MOTION_SENSOR_MODULE_H
#define MOTION_SENSOR_MODULE_H

#include <Arduino.h>

#define MOTION_SENSOR_PIN 36
void initMotionSensor();
bool isMotionDetected();
void motionSensorTask(void *parameter);

#endif // MOTION_SENSOR_MODULE_H