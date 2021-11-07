//
// Created by user on 05.11.2021.
//

#ifndef PIEC_PUMPSETTINGSPAGE_H
#define PIEC_PUMPSETTINGSPAGE_H


#include <models/Context.h>
#include "PageManager.h"
#include "Label.h"
#include "Button.h"

class PumpSettingsPage: public Page {
public:
    PumpSettingsPage(PageManager& manager, Display& display, Context& context, uint8_t pumpIndex);

    ~PumpSettingsPage() override;

    void draw() override;

    void handleEvent(Event event) override;
private:

    void setupButton(Button& button, int16_t x, int16_t y, bool focus, uint16_t & outHeight);
    Button& getButton(int id);
    PageManager& _manager;
    Display& _display;
    TFT& _tft;
    Context& _context;
    uint8_t _pumpIndex;
    bool _headerDrawn;
    Label _pumpDetails;
    Button _setClockBasedActivationButton;
    Button _setTempBasedActivationButton;
    Button _backButton;
    int _focusedButton;
};


#endif //PIEC_PUMPSETTINGSPAGE_H
