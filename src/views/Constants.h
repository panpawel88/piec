//
// Created by user on 01.11.2021.
//

#ifndef STEPPER_DEMO_CONSTANTS_H
#define STEPPER_DEMO_CONSTANTS_H

#include <Arduino.h>

const int16_t Margin = 10;

enum Event {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    ENTER,
    EXIT,
};

#endif //STEPPER_DEMO_CONSTANTS_H
