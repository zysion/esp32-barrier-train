#include "global.h"

volatile bool motionDetected = false;

void initMotionSensor() {
  pinMode(MOTION_SENSOR_PIN, INPUT);
}

bool isMotionDetected() {
  return digitalRead(MOTION_SENSOR_PIN) == HIGH;
}

void motionSensorTask(void *parameter) {
  while (true) {
    motionDetected = isMotionDetected();
    vTaskDelay(100 / portTICK_PERIOD_MS); // Check every 100 ms
  }
}