//
// Created by user on 04.11.2021.
//

#if USE_DHT

#ifndef PIEC_DHTTEMPDETECTOR_H
#define PIEC_DHTTEMPDETECTOR_H

#include <Arduino.h>
#include <DHT.h>

#include "TempDetector.h"

class DhtTempDetector : public TempDetector {
public:
    DhtTempDetector(uint8_t pin, uint8_t type);
    ~DhtTempDetector() override = default;

    void setup() override;
    void update() override;
    float readTemperature() override;
private:
    DHT _dht;
    float _temperature;
};


#endif //PIEC_DHTTEMPDETECTOR_H

#endif
