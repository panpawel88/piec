//
// Created by user on 01.11.2021.
//

#ifndef STEPPER_DEMO_MENUPAGE_H
#define STEPPER_DEMO_MENUPAGE_H


#include <Arduino.h>
#include <models/Context.h>

#include "Button.h"
#include "Display.h"
#include "Page.h"
#include "PageManager.h"

enum MenuItem {
    PUMP_SETTINGS,
    CLOCK_SETTINGS,
    RETURN,
};

class SettingsPage : public Page {
public:
    SettingsPage(PageManager& manager, Display& display, Context& context);

    ~SettingsPage() override;

    void draw() override;

    void handleEvent(Event event) override;

private:
    PageManager& _manager;
    Display& _display;
    TFT& _tft;
    Context& _context;
    bool _headerDrawn;
    MenuItem _focusedMenuItem;
    Button *_buttons[RETURN + 1];
};


#endif //STEPPER_DEMO_MENUPAGE_H
