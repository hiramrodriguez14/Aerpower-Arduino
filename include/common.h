#pragma once

#include "../lib/ESP32Servo-master/src/ESP32Servo.h"
#include <iostream>
#include <string>
#include <Arduino.h>
#include "gpio.h"
//In here will be all common code different classes need and global variables
Servo blades;
QueueHandle_t rpmQueue = xQueueCreate(1, sizeof(double));
#define TIMER_0 (0u)
#define TIMER_1 (1u)
#define TIMER_2 (2u)

void servoControl(int targetAngle) {
    int currentAngle = blades.read();
    int step;
    if(targetAngle > currentAngle) {
        step = 1;
    } else {
        step = -1;
    }
    while(currentAngle!= targetAngle){
        currentAngle += step;
        blades.write(currentAngle);
    }
}

