//
// Created by user on 01.11.2021.
//

#ifndef PIEC_CLOCK_H
#define PIEC_CLOCK_H

#include <Arduino.h>


struct Time {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    friend bool operator<(const Time& l, const Time& r);
    friend bool operator>(const Time& l, const Time& r);
    friend bool operator<=(const Time& l, const Time& r);
    friend bool operator>=(const Time& l, const Time& r);
    friend bool operator==(const Time& l, const Time& r);
    friend bool operator!=(const Time& l, const Time& r);

    String ToString() const;
};

class Clock {
public:
    virtual ~Clock() = default;
    virtual void update() = 0;
    virtual void getTime(Time& currentTime) const = 0;
    // TODO: set time
};


#endif //PIEC_CLOCK_H
