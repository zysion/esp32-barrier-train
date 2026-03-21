#include "global.h"

void ledblinky(void *parameter) {
  while (true) {
    digitalWrite(8, HIGH);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    digitalWrite(8, LOW);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  pinMode(8, OUTPUT); // Example pin for debugging
  Serial.begin(115200);
  connectWiFi(SSID, PASSWORD);

  initMotionSensor();
  initServo();
  initAlert();
  initI2C();

   xTaskCreate(motionSensorTask, "Motion Sensor Task", 2048, NULL, 1, NULL);
   xTaskCreate(servoTask, "Servo Task", 2048, NULL, 1, NULL);
   xTaskCreate(distanceMeasurementTask, "Distance Task", 2048, NULL, 1, NULL);
   xTaskCreate(alertTask, "Alert Task", 8192, NULL, 1, &alertTaskHandle);
  xTaskCreate(runWebServer, "Web Server Task", 8192, NULL, 2, NULL);
  xTaskCreate(ledblinky, "LED Blinky Task", 1024, NULL, 1, NULL); // Debugging task
}

void loop() {
  // put your main code here, to run repeatedly:
  if(motionDetected) Serial.println("Distance: " + String(distance) + " cm");
  // Serial.println("Motion Detected: " + String(motionDetected ? "Yes" : "No"));
  // Serial.println("Barrier State: " + String(barrierServo.read() == 0 ? "Closed" : "Open"));
  vTaskDelay(2000 / portTICK_PERIOD_MS); // Print status every 2 seconds
}