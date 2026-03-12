#ifndef SERVO_MODULE_H
#define SERVO_MODULE_H

#include <Arduino.h>
#include <Servo.h>

#define SERVO_PIN 37

void initServo();
void openBarrier();
void closeBarrier();
void servoTask(void *parameter);

#endif // SERVO_MODULE_H