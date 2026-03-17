#include "distance_module.h"
#include "global.h"

TaskHandle_t distanceMeasurementTaskHandle = NULL;
float distance = 0.0;

void distanceMeasurementTask(void *parameter) {
  UltraSonicDistanceSensor distanceSensor(TRIGGER_PIN, ECHO_PIN);

  while (true) {
    distance = distanceSensor.measureDistanceCm();
    vTaskDelay(100 / portTICK_PERIOD_MS); // Measure every 100 ms
  }
}