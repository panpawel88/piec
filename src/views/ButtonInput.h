//
// Created by user on 01.11.2021.
//

#ifndef STEPPER_DEMO_BUTTONINPUT_H
#define STEPPER_DEMO_BUTTONINPUT_H

#include <Arduino.h>

#include "Input.h"
#include "Constants.h"

class ButtonInput : public Input {
public:
    ButtonInput();

    void setup() override;

    bool available() override;

    Event getEvent() override;

private:
    static bool isPressed(int16_t pin);

    int16_t _leftPin;
    int16_t _rightPin;
    int16_t _upPin;
    int16_t _downPin;
    int16_t _enterPin;
    int16_t _exitPin;
    bool _hasEvent{};
    Event _event;
};


#endif //STEPPER_DEMO_BUTTONINPUT_H
