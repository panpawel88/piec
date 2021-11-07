//
// Created by user on 01.11.2021.
//

#include "SerialInput.h"

#include <Arduino.h>

SerialInput::SerialInput() : _hasEvent(false), _event(ENTER) {
}

bool SerialInput::available() {
    if (_hasEvent)
        return true;
    if (Serial.available()) {
        char c = (char) Serial.read();
        _hasEvent = true;
        switch (c) {
            case 'a':
                _event = LEFT;
                break;
            case 'd':
                _event = RIGHT;
                break;
            case 's':
                _event = DOWN;
                break;
            case 'w':
                _event = UP;
                break;
            case 'j':
                _event = ENTER;
                break;
            case 'h':
                _event = EXIT;
            default:
                _hasEvent = false;
                break;
        }
    }
    return _hasEvent;
}

Event SerialInput::getEvent() {
    _hasEvent = false;
    return _event;
}
