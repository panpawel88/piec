//
// Created by user on 05.11.2021.
//

#include "DummyClock.h"

DummyClock::~DummyClock() = default;

void DummyClock::update() {
    if (_time.seconds < 59) {
        _time.seconds = _time.seconds + 1;
    } else {
        _time.seconds = 0;
        if (_time.minutes < 59) {
            _time.minutes = _time.minutes + 1;
        } else {
            _time.minutes = 0;
            if (_time.hours < 23) {
                _time.hours = _time.hours + 1;
            } else {
                _time.hours = 0;
            }
        }
    }
}

void DummyClock::getTime(Time &currentTime) const {
    currentTime = _time;
}
