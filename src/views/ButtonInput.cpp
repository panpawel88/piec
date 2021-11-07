//
// Created by user on 01.11.2021.
//

#include "ButtonInput.h"

ButtonInput::ButtonInput()
        : _leftPin(0), _rightPin(0), _upPin(0), _downPin(0), _enterPin(0), _exitPin(0), _hasEvent(false),
          _event(ENTER) {}

void ButtonInput::setup() {
    pinMode(_leftPin, INPUT_PULLUP);
    pinMode(_rightPin, INPUT_PULLUP);
    pinMode(_upPin, INPUT_PULLUP);
    pinMode(_downPin, INPUT_PULLUP);
    pinMode(_enterPin, INPUT_PULLUP);
    pinMode(_exitPin, INPUT_PULLUP);
}

bool ButtonInput::available() {
    if (_hasEvent) return true;
    if (isPressed(_leftPin)) {
        _event = LEFT;
        _hasEvent = true;
    } else if (isPressed(_rightPin)) {
        _event = RIGHT;
        _hasEvent = true;
    } else if (isPressed(_upPin)) {
        _event = UP;
        _hasEvent = true;
    } else if (isPressed(_downPin)) {
        _event = DOWN;
        _hasEvent = true;
    } else if (isPressed(_enterPin)) {
        _event = ENTER;
        _hasEvent = true;
    }

    return _hasEvent;
}


Event ButtonInput::getEvent() {
    _hasEvent = false;
    return _event;
}

bool ButtonInput::isPressed(int16_t pin) {
    bool pressed = false;
    while (digitalRead(pin) == LOW) {
        pressed = true;
        delay(20);
    }
    return pressed;
}