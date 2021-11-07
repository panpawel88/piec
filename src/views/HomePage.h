//
// Created by user on 01.11.2021.
//

#ifndef STEPPER_DEMO_HOMEPAGE_H
#define STEPPER_DEMO_HOMEPAGE_H

#include <Arduino.h>
#include <models/Context.h>

#include "Button.h"
#include "Constants.h"
#include "Page.h"
#include "PageManager.h"
#include "Label.h"


class HomePage : public Page {
public:
    HomePage(PageManager& manager, Display& display, Context& context);

    ~HomePage() override;

    void draw() override;

    void handleEvent(Event event) override;

    bool isDirty() const override;

private:
    PageManager& _manager;
    Display& _display;
    TFT& _tft;
    Context& _context;
    bool _headerDrawn;
    Label** _pumpStateLabels;
    Label** _pumpStateValues;
    Label _clockValue;
    Button *_moreButton;
    Time _lastTime;
};


#endif //STEPPER_DEMO_HOMEPAGE_H
