#include "motion_sensor_module.h"
#include "global.h"

extern bool motionDetected = false;

void initMotionSensor() {
  pinMode(MOTION_SENSOR_PIN, INPUT);
}

bool isMotionDetected() {
  return digitalRead(MOTION_SENSOR_PIN) == HIGH;
}

void motionSensorTask(void *parameter) {
  while (true) {
    motionDetected = isMotionDetected();
    vTaskDelay(250 / portTICK_PERIOD_MS); // Check every 250 ms
  }
}