//
// Created by user on 05.11.2021.
//

#ifndef PIEC_SELECTPUMPPAGE_H
#define PIEC_SELECTPUMPPAGE_H


#include <models/Context.h>
#include "Page.h"
#include "PageManager.h"
#include "Button.h"

class SelectPumpPage : public Page {
public:
    SelectPumpPage(PageManager& manager, Display& display, Context& context);

    ~SelectPumpPage() override;

    void draw() override;

    void handleEvent(Event event) override;

private:
    PageManager& _manager;
    Display& _display;
    TFT& _tft;
    Context& _context;
    bool _headerDrawn;
    Button** _buttons;
    uint8_t _selectedButton;

};

#endif //PIEC_SELECTPUMPPAGE_H
