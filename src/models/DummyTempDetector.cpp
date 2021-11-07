//
// Created by user on 05.11.2021.
//

#include "DummyTempDetector.h"

void DummyTempDetector::setup() {

}

void DummyTempDetector::update() {
    _temperature = readTemperature();
}

float DummyTempDetector::readTemperature() {
    return 0;
}
