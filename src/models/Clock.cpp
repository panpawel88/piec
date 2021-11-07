//
// Created by user on 01.11.2021.
//

#include "Clock.h"

bool operator<(const Time &l, const Time &r) {
    if (l.hours < r.hours)
        return true;
    else if (l.hours == r.hours) {
        if (l.minutes < r.minutes)
            return true;
        else if (l.minutes == r.minutes)
            return l.seconds < r.seconds;
        else
            return false;
    } else
        return false;
}

bool operator>(const Time &l, const Time &r) {
    return r < l;
}

bool operator<=(const Time &l, const Time &r) {
    return !(l > r);
}

bool operator>=(const Time &l, const Time &r) {
    return !(l < r);
}

bool operator==(const Time &l, const Time &r) {
    return l.hours == r.hours && l.minutes == r.minutes && l.seconds == r.seconds;
}

bool operator!=(const Time &l, const Time &r) {
    return !(l == r);
}

String Time::ToString() const {
    const __FlashStringHelper *separator = F(":");
    const __FlashStringHelper *zero = F("0");
    String result{};

    if (hours < 10)
        result += zero;
    result += hours;
    result += separator;
    if (minutes < 10)
        result += zero;
    result += minutes;
    result += separator;
    if (seconds < 10)
        result += zero;
    result += seconds;
    return result;
}
