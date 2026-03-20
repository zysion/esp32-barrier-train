#include "global.h"

Servo barrierServo;
bool system_mode = true; // false for normal mode, true for AUTO mode

void initServo() {
  barrierServo.attach(SERVO_PIN);
  openBarrier(); // Ensure the barrier starts in the closed position
}

void openBarrier() {
  barrierServo.write(90); // Adjust angle as needed for your servo
}

void closeBarrier() {
  barrierServo.write(0); // Adjust angle as needed for your servo
}

void servoTask(void *parameter) {
  while (true) {
    if (motionDetected) {
      if (system_mode) {
        closeBarrier();
      }
    } else {
      if(system_mode) {
        openBarrier();
      }
    }
    vTaskDelay(250 / portTICK_PERIOD_MS); // Check every 250 ms
  }
}