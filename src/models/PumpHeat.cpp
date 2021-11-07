//
// Created by user on 01.11.2021.
//

#include "PumpHeat.h"

#include <EEPROM.h>

class PumpHeat::IActivation {
public:
    virtual ~IActivation() = default;

    virtual void update() = 0;

    virtual PumpData getData() = 0;
};

class PumpHeat::TempBasedActivation : public PumpHeat::IActivation {
public:
    TempBasedActivation(PumpHeat *pumpHeat, TempDetector &tempDetector, float temperature) : _pumpHeat(pumpHeat),
                                                                                             _tempDetector(
                                                                                                     tempDetector),
                                                                                             _temperature(temperature) {
    }

    ~TempBasedActivation() override = default;

    void update() override {
        float currentTemperature = _tempDetector.readTemperature();
        if (currentTemperature < (_temperature - 0.5))
            _pumpHeat->activate();
        else if (currentTemperature >= _temperature)
            _pumpHeat->deactivate();
    }

    PumpData getData() override {
        PumpData data{};
        data.activationMode = TempBased;
        data.td.temperature = _temperature;
        return data;
    }

private:
    PumpHeat *_pumpHeat;
    TempDetector &_tempDetector;
    float _temperature;
};

class PumpHeat::ClockBasedActivation : public PumpHeat::IActivation {
public:
    ClockBasedActivation(PumpHeat *pumpHeat, const Time &start, const Time &end, Clock &clock) : _pumpHeat(pumpHeat),
                                                                                                 _start(start),
                                                                                                 _stop(end),
                                                                                                 _clock(clock) {
    }

    ~ClockBasedActivation() override = default;

    void update() override {
        Time currentTime{};
        _clock.getTime(currentTime);
        if (shouldActivate(currentTime))
            _pumpHeat->activate();
        else
            _pumpHeat->deactivate();
    }

    PumpData getData() override {
        PumpData data{};
        data.activationMode = ClockBased;
        data.cd.start = _start;
        data.cd.stop = _stop;
        return data;
    }

private:

    bool shouldActivate(const Time &currentTime) {
//        Serial.print("start: "); Serial.print(_start.ToString()); Serial.print(", current: "); Serial.print(currentTime.ToString()); Serial.print(", stop: "); Serial.println(_stop.ToString());
        if (currentTime >= _start && currentTime < _stop) {
            return true;
        } else if (_stop < _start) {
            return !(currentTime >= _stop && currentTime < _start);
        } else return _stop == _start;
    }

    PumpHeat *_pumpHeat;
    Time _start;
    Time _stop;
    Clock &_clock;
};

void restore(TempDetector &tempDetector, Clock &clock);

PumpHeat::PumpHeat(uint8_t pin, uint8_t idx) : _pin(pin), _idx(idx), _activationMode(None), _activation{} {
}

void PumpHeat::setup(TempDetector &tempDetector, Clock &clock) {
    pinMode(_pin, OUTPUT);

    restore(tempDetector, clock);
}

void PumpHeat::restore(TempDetector &tempDetector, Clock &clock) {
    PumpData data{};
    EEPROM.get(this->_idx, data);
    if (data.activationMode == None)
        return;
    else if (data.activationMode == TempBased) {
        float temperature = data.td.temperature;
        this->setTempBasedActivation(tempDetector, temperature);
    } else if (data.activationMode == ClockBased) {
        Time start = data.cd.start;
        Time stop = data.cd.stop;
        this->setClockBasedActivation(clock, start, stop);
    }
}

void PumpHeat::save() {
    PumpData data = getData();
    EEPROM.put(_idx, data);
}

void PumpHeat::setTempBasedActivation(TempDetector &tempDetector, float temperature) {
    if (_activation != nullptr) {
        delete _activation;
        _activation = nullptr;
    }
    _activation = new TempBasedActivation(this, tempDetector, temperature);
    _activationMode = TempBased;
    save();
}

void PumpHeat::setClockBasedActivation(Clock &clock, const Time &start, const Time &stop) {
    if (_activation != nullptr) {
        delete _activation;
        _activation = nullptr;
    }
    _activation = new ClockBasedActivation(this, start, stop, clock);
    _activationMode = ClockBased;
    save();
}

void PumpHeat::update() {
    if (_activation != nullptr)
        _activation->update();
}

void PumpHeat::activate() {
    _state = true;
    digitalWrite(_pin, HIGH);
}

void PumpHeat::deactivate() {
    _state = false;
    digitalWrite(_pin, LOW);
}

PumpData PumpHeat::getData() const {
    PumpData data{};
    if (_activation == nullptr)
        data.activationMode = None;
    else
        data = _activation->getData();
    return data;
}




