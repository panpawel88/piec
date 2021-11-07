//
// Created by user on 05.11.2021.
//

#if USE_REAL_CLOCK

#include "VirtuabotixRTCClock.h"

VirtuabotixRTCClock::VirtuabotixRTCClock(uint8_t clk, uint8_t io, uint8_t enable) : _clock(clk, io, enable) {

}

void VirtuabotixRTCClock::update() {
    _clock.updateTime();
}

void VirtuabotixRTCClock::getTime(Time &currentTime) const {
    currentTime.hours = _clock.hours;
    currentTime.minutes = _clock.minutes;
    currentTime.seconds = _clock.seconds;
}

#endif