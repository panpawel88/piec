//
// Created by user on 05.11.2021.
//

#include "Context.h"

Context::Context(PumpHeat **pumps, uint8_t count, Clock &clock, TempDetector &tempDetector) : _pumps(pumps),
                                                                                              _count(count),
                                                                                              _clock(clock),
                                                                                              _tempDetector(
                                                                                                      tempDetector) {

}

PumpHeat *Context::getPump(uint8_t idx) {
    return _pumps[idx];
}

void Context::update() {
    _clock.update();
    _tempDetector.update();

    for (int i = 0; i < _count; ++i) {
        _pumps[i]->update();
    }
}
