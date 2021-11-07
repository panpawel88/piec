//
// Created by user on 05.11.2021.
//

#ifndef PIEC_SETCLOCKBASEDACTIVATIONPAGE_H
#define PIEC_SETCLOCKBASEDACTIVATIONPAGE_H


#include <models/Context.h>
#include "Page.h"
#include "PageManager.h"
#include "Label.h"

class SetClockBasedActivationPage : public Page {
public:
    SetClockBasedActivationPage(PageManager& manager, Display& display, Context& context, uint8_t pumpIndex);

    ~SetClockBasedActivationPage() override;

    void draw() override;

    void handleEvent(Event event) override;

private:

    void setValues(const Time& start, const Time& stop);

    int getMaxValue(int selectedValue) const;

    PageManager& _manager;
    Display& _display;
    TFT& _tft;
    Context& _context;
    uint8_t _pumpIndex;
    bool _headerDrawn;

    uint8_t _values[17];
    Label* _valueLabels[17];
    uint8_t _selectedValue;
    uint16_t _unfocusedColor;
    uint16_t _focusedColor;
};


#endif //PIEC_SETCLOCKBASEDACTIVATIONPAGE_H
