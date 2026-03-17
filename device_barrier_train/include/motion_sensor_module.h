#ifndef MOTION_SENSOR_MODULE_H
#define MOTION_SENSOR_MODULE_H

#include <global.h>

void initMotionSensor();
bool isMotionDetected();
void motionSensorTask(void *parameter);

#endif // MOTION_SENSOR_MODULE_H