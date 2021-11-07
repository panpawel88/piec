//
// Created by panpa on 22.09.2019.
//

#include <views/PageManager.h>
#include <views/SerialInput.h>
#include <views/HomePage.h>
#include <views/FontManager.h>
#include <models/PumpHeat.h>
#include <models/DummyTempDetector.h>
#include <models/Context.h>
#include <models/DummyClock.h>
#include <models/DhtTempDetector.h>
#include <views/PumpSettingsPage.h>

PumpHeat p1(A1, 0);
PumpHeat p2(A1, 1);

PumpHeat* pumps[2];
DummyClock clock;
DhtTempDetector tempDetector(0, 0);
Context context(pumps, 2, clock, tempDetector);
FontManager fontManager;
PageManager manager;
Display display(fontManager);
SerialInput input;

unsigned long lastUpdateTime = 0;

void setup() {
    Serial.begin(9600);
    input.setup();
    display.setup();

    p1.setup(tempDetector, clock);
    p2.setup(tempDetector, clock);
    pumps[0] = &p1;
    pumps[1] = &p2;

    context.update();
    manager.setPage(new HomePage(manager, display, context));
    manager.update();
}

void loop() {
    if (input.available()) {
        Event event = input.getEvent();
        manager.handleEvent(event);
        manager.update();
        lastUpdateTime = millis();
    } else if (millis() - lastUpdateTime >= 1000) {
        context.update();
        manager.update();
        lastUpdateTime = millis();
    }
}



