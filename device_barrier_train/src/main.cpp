#include "global.h"

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  initMotionSensor();
  initServo();
  initI2C();

  xTaskCreate(motionSensorTask, "Motion Sensor Task", 2048, NULL, 1, NULL);
  xTaskCreate(servoTask, "Servo Task", 2048, NULL, 1, NULL);
}

void loop() {
  // put your main code here, to run repeatedly:
}
