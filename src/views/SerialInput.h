//
// Created by user on 01.11.2021.
//

#ifndef STEPPER_DEMO_SERIALINPUT_H
#define STEPPER_DEMO_SERIALINPUT_H

#include "Constants.h"
#include "Input.h"

class SerialInput : public Input {
public:
    SerialInput();

    void setup() override { }

    bool available() override;

    Event getEvent() override;

private:
    bool _hasEvent{};
    Event _event;
};


#endif //STEPPER_DEMO_SERIALINPUT_H
