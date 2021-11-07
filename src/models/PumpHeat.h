//
// Created by user on 01.11.2021.
//

#ifndef PIEC_PUMPHEAT_H
#define PIEC_PUMPHEAT_H

#include <Arduino.h>
#include <DHT.h>
#include "Clock.h"
#include "TempDetector.h"

enum ActivationMode {
    None,
    ClockBased,
    TempBased,
};

struct ClockBasedData {
    Time start;
    Time stop;
};

struct TempBasedData {
    float temperature;
};

struct PumpData {
    ActivationMode activationMode;
    union {
        ClockBasedData cd;
        TempBasedData td;
    };
};

class PumpHeat {
public:
    explicit PumpHeat(uint8_t pin, uint8_t idx);

    void setup(TempDetector &tempDetector, Clock &clock);
    void setClockBasedActivation(Clock &clock, const Time &start, const Time &stop);
    void setTempBasedActivation(TempDetector& dht, float temperature);
    void update();

    ActivationMode activationMode() const { return _activationMode; }
    bool state() const { return _state; }
    PumpData getData() const;

private:
    void activate();
    void deactivate();
    void restore(TempDetector &tempDetector, Clock &clock);
    void save();

    uint8_t _pin;
    uint8_t _idx;
    ActivationMode _activationMode;
    bool _state{};
    class IActivation;
    class TempBasedActivation;
    class ClockBasedActivation;
    IActivation* _activation;
};


#endif //PIEC_PUMPHEAT_H
