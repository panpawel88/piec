//
// Created by user on 01.11.2021.
//

#ifndef STEPPER_DEMO_INPUT_H
#define STEPPER_DEMO_INPUT_H


#include "Constants.h"

class Input {
public:
    virtual void setup() = 0;

    virtual bool available() = 0;

    virtual Event getEvent() = 0;
};

#endif //STEPPER_DEMO_INPUT_H
