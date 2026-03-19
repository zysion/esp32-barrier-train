#ifndef SERVO_MODULE_H
#define SERVO_MODULE_H

#include <global.h>

void initServo();
void openBarrier();
void closeBarrier();
void servoTask(void *parameter);

#endif // SERVO_MODULE_H