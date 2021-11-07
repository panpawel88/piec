//
// Created by user on 01.11.2021.
//

#include <Adafruit_GFX.h>

#include "SettingsPage.h"
#include "colors.h"
#include "ClockSettingsPage.h"
#include "SelectPumpPage.h"
#include "HomePage.h"

namespace {

    const __FlashStringHelper *MenuItemString(MenuItem menuItem) {
        switch (menuItem) {
            case PUMP_SETTINGS:
                return F("USTAWIENIA POMP");
            case CLOCK_SETTINGS:
                return F("USTAWIENIA ZEGARA");
            case RETURN:
                return F("POWROT");
        }
    }

}

SettingsPage::SettingsPage(PageManager &manager, Display &display, Context& context)
        : Page(display), _manager(manager), _display(display), _tft(_display.tft()), _context(context), _headerDrawn(false),
          _focusedMenuItem(PUMP_SETTINGS) {
    int16_t x = Margin;
    int16_t y = 4 * Margin + _display.bigFontHeight();
    for (int i = 0; i <= RETURN; ++i) {
        auto *button = new Button(_display, MenuItemString((MenuItem) i));
        button->setup();
        if (i == _focusedMenuItem)
            button->setFocus(true);
        uint16_t width, height;
        button->getSize(&width, &height);
        button->setSize(_display.width() - Margin * 2, height);
        button->setPosition(x, y);
        y += height + Margin;
        _buttons[i] = button;
    }
}

SettingsPage::~SettingsPage() {
    for (auto &_button : _buttons) {
        delete _button;
    }
}

void SettingsPage::draw() {
    if (!_headerDrawn) {
        drawHeader(F("USTAWIENIA"));
        _headerDrawn = true;
    }

    for (auto &button: _buttons) {
        button->draw();
    }
}

void SettingsPage::handleEvent(Event event) {
    if (event == UP) {
        if (_focusedMenuItem > 0) {
            _buttons[_focusedMenuItem]->setFocus(false);
            _focusedMenuItem = (MenuItem) (_focusedMenuItem - 1);
            _buttons[_focusedMenuItem]->setFocus(true);
            setDirty();
        }
    } else if (event == DOWN) {
        if (_focusedMenuItem < RETURN) {
            _buttons[_focusedMenuItem]->setFocus(false);
            _focusedMenuItem = (MenuItem) (_focusedMenuItem + 1);
            _buttons[_focusedMenuItem]->setFocus(true);

            setDirty();
        }
    } else if (event == ENTER) {
        Page *page;
        switch (_focusedMenuItem) {
            case PUMP_SETTINGS:
                page = new SelectPumpPage(_manager, _display, _context);
                break;
            case CLOCK_SETTINGS:
                page = new ClockSettingsPage(_manager, _display, _context);
                break;
            case RETURN:
                page = new HomePage(_manager, _display, _context);
                break;
        }

        _manager.setPage(page);
    }
}
