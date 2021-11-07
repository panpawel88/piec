//
// Created by user on 04.11.2021.
//

#if USE_DHT

#include "DhtTempDetector.h"

DhtTempDetector::DhtTempDetector(uint8_t pin, uint8_t type) : _dht(pin, type), _temperature(0.0f) {
}

void DhtTempDetector::setup() {
    update();
}

void DhtTempDetector::update() {
    _temperature = _dht.readTemperature();
}

float DhtTempDetector::readTemperature() {
    return _temperature;
}

#endif