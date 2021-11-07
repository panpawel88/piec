//
// Created by user on 05.11.2021.
//

#ifndef PIEC_DUMMYTEMPDETECTOR_H
#define PIEC_DUMMYTEMPDETECTOR_H


#include "TempDetector.h"

class DummyTempDetector : public TempDetector {
public:
    ~DummyTempDetector() override = default;
    void setup() override;
    void update() override;
    float readTemperature() override;
private:
    float _temperature;
};


#endif //PIEC_DUMMYTEMPDETECTOR_H
