#include "global.h"

Servo barrierServo;

void initServo() {
  barrierServo.attach(SERVO_PIN);
  openBarrier(); // Ensure the barrier starts in the closed position
}

void openBarrier() {
  barrierServo.write(90); // Adjust angle as needed for your servo

  digitalWrite(BUZZER_PIN, LOW);   // Shut down all when barrier is opened
  digitalWrite(ALERT_LED_PIN, LOW);
  vTaskSuspend(distanceMeasurementTaskHandle); // Suspend this task until motion is detected again
}

void closeBarrier() {
  barrierServo.write(0); // Adjust angle as needed for your servo
  vTaskResume(distanceMeasurementTaskHandle); // Resume distance measurement when motion is detected
}

void servoTask(void *parameter) {
  while (true) {
    if (motionDetected) {
      closeBarrier();
    } else {
      openBarrier();
    }
    vTaskDelay(250 / portTICK_PERIOD_MS); // Check every 250 ms
  }
}