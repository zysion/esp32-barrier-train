#include "global.h"

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_SDA, I2C_SCL); // Initialize I2C before LCD
  connectWiFi(SSID, PASSWORD);

  initMotionSensor();
  initServo();
  initAlert();
  initI2C();

  xTaskCreate(motionSensorTask, "Motion Sensor Task", 2048, NULL, 1, NULL);
  xTaskCreate(servoTask, "Servo Task", 2048, NULL, 1, NULL);
  xTaskCreate(distanceMeasurementTask, "Distance Task", 2048, NULL, 1, NULL);
  xTaskCreate(alertTask, "Alert Task", 8192, NULL, 1, &alertTaskHandle);
  xTaskCreate(runWebServer, "Web Server Task", 8192, NULL, 1, NULL);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(motionDetected) Serial.println("Distance: " + String(distance) + " cm");
  Serial.println("Motion Detected: " + String(motionDetected ? "Yes" : "No"));
  Serial.println("Barrier State: " + String(barrierServo.read() == 0 ? "Closed" : "Open"));
  vTaskDelay(2000 / portTICK_PERIOD_MS); // Print status every 2 seconds
}