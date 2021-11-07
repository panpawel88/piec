//
// Created by user on 04.11.2021.
//

#ifndef PIEC_TEMPDETECTOR_H
#define PIEC_TEMPDETECTOR_H


class TempDetector {
public:
    virtual ~TempDetector() = default;
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual float readTemperature() = 0;
};


#endif //PIEC_TEMPDETECTOR_H
