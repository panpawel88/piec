//
// Created by user on 05.11.2021.
//

#ifndef PIEC_CLOCKSETTINGSPAGE_H
#define PIEC_CLOCKSETTINGSPAGE_H


#include <models/Context.h>
#include "Page.h"
#include "PageManager.h"

class ClockSettingsPage : public Page {
public:
    ClockSettingsPage(PageManager& manager, Display& display, Context& context);

    ~ClockSettingsPage() override;

    void draw() override;

    void handleEvent(Event event) override;

private:
    PageManager& _manager;
    Display& _display;
    TFT& _tft;
    Context& _context;
    bool _headerDrawn;
};


#endif //PIEC_CLOCKSETTINGSPAGE_H
