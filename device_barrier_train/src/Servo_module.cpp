#include "global.h"

Servo barrierServo;
volatile bool AUTO_mode = true;
volatile bool isopenbarrier = true; 

void initServo() {
  barrierServo.attach(SERVO_PIN);
  openBarrier(); // Ensure the barrier starts in the closed position
}

void openBarrier() {
  barrierServo.write(90); // Adjust angle as needed for your servo
  isopenbarrier = true;
}

void closeBarrier() {
  barrierServo.write(0); // Adjust angle as needed for your servo
  isopenbarrier = false;
}

void servoTask(void *parameter) {
  uint32_t lastMotionTime = 0;
  bool waitingToOpen = false;

  while (true) {
    if(AUTO_mode) { // Only operate in AUTO mode
      if (motionDetected) {
        waitingToOpen = false;
        if (isopenbarrier) {
            closeBarrier();
        }
      } else {
        if (!isopenbarrier) {
            if (!waitingToOpen) {
                lastMotionTime = millis();
                waitingToOpen = true;
            } else if (millis() - lastMotionTime >= 2000) {
                openBarrier();
                waitingToOpen = false;
            }
        } else {
            waitingToOpen = false;
        }
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS); // Check every 100 ms
  }
}