//
// Created by user on 05.11.2021.
//

#include "SelectPumpPage.h"
#include "PumpSettingsPage.h"
#include "SettingsPage.h"

SelectPumpPage::SelectPumpPage(PageManager &manager, Display &display, Context &context) : Page(display),
                                                                                                 _manager(manager),
                                                                                                 _display(display),
                                                                                                 _tft(_display.tft()),
                                                                                                 _context(context),
                                                                                                 _headerDrawn(false),
                                                                                                 _selectedButton(0){
    int16_t x = Margin;
    int16_t y = 4 * Margin + _display.bigFontHeight();
    uint8_t pumpsCount = _context.pumpsCount();
    _buttons = new Button*[pumpsCount + 1];
    for (uint8_t i = 0; i < pumpsCount; ++i) {
        String label = String(F("Pompa P")) + i;
        auto* button = new Button(display, label);
        button->setup();
        if (i == _selectedButton)
            button->setFocus(true);
        uint16_t width, height;
        button->getSize(&width, &height);
        button->setSize(_display.width() - Margin * 2, height);
        button->setPosition(x, y);
        y += height + Margin;
        _buttons[i] = button;
    }

    String label = String("POWROT");
    auto* button = new Button(display, label);
    button->setup();
    uint16_t width, height;
    button->getSize(&width, &height);
    button->setSize(_display.width() - Margin * 2, height);
    button->setPosition(x, y);
    _buttons[pumpsCount] = button;
}

SelectPumpPage::~SelectPumpPage() {
    uint8_t pumpsCount = _context.pumpsCount();
    for (uint8_t i = 0; i < pumpsCount + 1; ++i) {
        delete _buttons[i];
    }
    delete [] _buttons;
}

void SelectPumpPage::draw() {
    if (!_headerDrawn) {
        drawHeader(F("WYBIERZ POMPE"));
        _headerDrawn = true;
    }

    uint8_t pumpsCount = _context.pumpsCount();
    for (uint8_t i = 0; i < pumpsCount + 1; ++i) {
        _buttons[i]->draw();
    }
}

void SelectPumpPage::handleEvent(Event event) {
    if (event == UP) {
        if (_selectedButton > 0) {
            _buttons[_selectedButton]->setFocus(false);
            _selectedButton = _selectedButton - 1;
            _buttons[_selectedButton]->setFocus(true);
            setDirty();
        }
    } else if (event == DOWN) {
        if (_selectedButton < _context.pumpsCount() + 1) {
            _buttons[_selectedButton]->setFocus(false);
            _selectedButton = _selectedButton + 1;
            _buttons[_selectedButton]->setFocus(true);
            setDirty();
        }
    } else if (event == ENTER) {
        Page *page;
        if (_selectedButton < _context.pumpsCount()) {
            page = new PumpSettingsPage(_manager, _display, _context, _selectedButton);
        } else {
            page = new SettingsPage(_manager, _display, _context);
        }

        _manager.setPage(page);
    }
}
