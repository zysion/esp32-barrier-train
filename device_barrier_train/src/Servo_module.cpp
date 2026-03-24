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
  while (true) {
    if(AUTO_mode) { // Only operate in AUTO mode
      if (motionDetected) {
        vTaskDelay(3000 / portTICK_PERIOD_MS);

        if (isopenbarrier) {
            closeBarrier();
        }
        if (alertTaskHandle != NULL) {
          vTaskResume(alertTaskHandle); // Resume alert task when motion is detected
        }
      } else {
        if (!isopenbarrier) {
            openBarrier();
        }
        digitalWrite(BUZZER_PIN, LOW);   // Shut down all when barrier is opened
        digitalWrite(ALERT_LED_PIN, LOW);
        sendalertstatus_SAFE(); // Update webserver with safe status
        if (alertTaskHandle != NULL) {
        vTaskSuspend(alertTaskHandle); // Suspend this task until motion is detected again
        }
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS); // Check every 100 ms
  }
}