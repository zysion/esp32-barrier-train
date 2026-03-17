#include "global.h"

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);

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

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}