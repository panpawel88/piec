//
// Created by user on 05.11.2021.
//

#ifndef PIEC_DUMMYCLOCK_H
#define PIEC_DUMMYCLOCK_H


#include "Clock.h"

class DummyClock : public Clock {
public:
    ~DummyClock() override;

    void update() override;

    void getTime(Time &currentTime) const override;
private:
    Time _time;
};


#endif //PIEC_DUMMYCLOCK_H
