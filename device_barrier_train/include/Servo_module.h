#ifndef SERVO_MODULE_H
#define SERVO_MODULE_H

#include <global.h>

#define SERVO_PIN 37

void initServo();
void openBarrier();
void closeBarrier();
void servoTask(void *parameter);

#endif // SERVO_MODULE_H