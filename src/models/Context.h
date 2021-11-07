//
// Created by user on 05.11.2021.
//

#ifndef PIEC_CONTEXT_H
#define PIEC_CONTEXT_H

#include "PumpHeat.h"

class Context {
public:
    Context(PumpHeat** pumps, uint8_t count, Clock& clock, TempDetector& tempDetector);

    PumpHeat* getPump(uint8_t idx);
    uint8_t pumpsCount() const { return _count; }

    Clock& clock() { return _clock; }

    void update();

private:
    PumpHeat** _pumps;
    uint8_t _count;

    Clock& _clock;
    TempDetector& _tempDetector;

};


#endif //PIEC_CONTEXT_H
