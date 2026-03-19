#include "global.h"

Servo barrierServo;

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
      vTaskDelay(3000 / portTICK_PERIOD_MS);

      closeBarrier();
      if (alertTaskHandle != NULL) {
        vTaskResume(alertTaskHandle); // Resume alert task when motion is detected
      }
    } else {
      openBarrier();
      digitalWrite(BUZZER_PIN, LOW);   // Shut down all when barrier is opened
      digitalWrite(ALERT_LED_PIN, LOW);
      if (alertTaskHandle != NULL) {
      vTaskSuspend(alertTaskHandle); // Suspend this task until motion is detected again
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS); // Check every 100 ms
  }
}