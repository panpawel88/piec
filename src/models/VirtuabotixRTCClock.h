//
// Created by user on 05.11.2021.
//

#if USE_REAL_CLOCK

#ifndef PIEC_VIRTUABOTIXRTCCLOCK_H
#define PIEC_VIRTUABOTIXRTCCLOCK_H

#include <Arduino.h>
#include <virtuabotixRTC.h>

#include "Clock.h"

class VirtuabotixRTCClock : public Clock {
public:
    VirtuabotixRTCClock(uint8_t clk, uint8_t io, uint8_t enable);
    void update() override;
    void getTime(Time& currentTime) const override;
    // TODO: set time
private:
    virtuabotixRTC _clock;
};

#endif //PIEC_VIRTUABOTIXRTCCLOCK_H

#endif
