//
// Created by user on 05.11.2021.
//

#include "PumpSettingsPage.h"
#include "Label.h"
#include "colors.h"
#include "SettingsPage.h"
#include "SetClockBasedActivationPage.h"

namespace {
    enum Buttons {
        SET_CLOCK_BASED,
        SET_TEMP_BASED,
        BACK,
    };
}

PumpSettingsPage::PumpSettingsPage(PageManager& manager, Display& display, Context& context, uint8_t pumpIndex) : Page(display),
                                                                                                               _manager(manager),
                                                                                                               _display(display),
                                                                                                               _tft(_display.tft()),
                                                                                                               _context(context),
                                                                                                               _pumpIndex(pumpIndex),
                                                                                                               _headerDrawn(false),
                                                                                                               _pumpDetails(_tft),
                                                                                                               _setClockBasedActivationButton(display, F("TRYB ZEGARA")),
                                                                                                               _setTempBasedActivationButton(display, F("TRYB TEMPERATURY")),
                                                                                                               _backButton(display, F("POWROT")),
                                                                                                               _focusedButton(0) {
    uint16_t bigFontHeight = _display.bigFontHeight();
    uint16_t y = 4 * Margin + bigFontHeight;
    const GFXfont* font = _display.fontManager().getSegoeui10pt7b();

    _pumpDetails.setCursor(Margin, y);
    _pumpDetails.setFont(font);
    _pumpDetails.setColor(BLACK);
    _pumpDetails.setBackgroundColor(_tft.color565(223, 223, 223));
    _pumpDetails.setForegroundColor(_tft.color565(223, 223, 223));

    PumpHeat* pump = _context.getPump(pumpIndex);
    PumpData data = pump->getData();
    switch (data.activationMode) {
        case None:
            _pumpDetails.setText(String(F("Aktualny tryb: Nie wybrany")));
            break;
        case ClockBased: {
            String text = String(F("Aktualny tryb: Zegar\n("));
            text += data.cd.start.ToString();
            text += F(" - ");
            text += data.cd.stop.ToString();
            text += F(")");
            _pumpDetails.setText(text);
            break;
        }
        case TempBased: {
            String text = String(F("Aktualny tryb: Temperatura\n("));
            text += data.td.temperature;
            text += F("ºC)");
            _pumpDetails.setText(text);
            break;
        }
    }

    int16_t x = Margin;
    y = _display.height() / 2 - Margin;

    uint16_t height;
    setupButton(_setClockBasedActivationButton, x, y, true, height);
    y += height + Margin;
    setupButton(_setTempBasedActivationButton, x, y, false, height);
    y += height + Margin;
    setupButton(_backButton, x, y, false, height);
}

void PumpSettingsPage::setupButton(Button &button, int16_t x, int16_t y, bool focus, uint16_t & outHeight) {
    button.setup();
    button.setFocus(focus);
    uint16_t width, height;
    button.getSize(&width, &height);
    button.setSize(_display.width() - Margin * 2, height);
    button.setPosition(x, y);

    outHeight = height;
}

PumpSettingsPage::~PumpSettingsPage() = default;

void PumpSettingsPage::draw() {
    if (!_headerDrawn) {
        drawHeader(String(F("USTAWIENIA P")) + _pumpIndex);
        _pumpDetails.draw();
        _headerDrawn = true;
    }

    _setClockBasedActivationButton.draw();
    _setTempBasedActivationButton.draw();
    _backButton.draw();
}

void PumpSettingsPage::handleEvent(Event event) {
    if (event == UP) {
        if (_focusedButton > 0) {
            getButton(_focusedButton).setFocus(false);
            --_focusedButton;
            getButton(_focusedButton).setFocus(true);
            setDirty();
        }
    } else if (event == DOWN) {
        if (_focusedButton < BACK) {
            getButton(_focusedButton).setFocus(false);
            ++_focusedButton;
            getButton(_focusedButton).setFocus(true);
            setDirty();
        }
    } else if (event == ENTER) {
        Page *page;
        switch (_focusedButton) {
//            case SET_TEMP_BASED:
//                page = new SetTempBasedActivationPage(_manager, _display, _context, _pumpIndex);
//                break;
            case SET_CLOCK_BASED:
                page = new SetClockBasedActivationPage(_manager, _display, _context, _pumpIndex);
                break;
            case BACK:
                page = new SettingsPage(_manager, _display, _context);
                break;
        }

        _manager.setPage(page);
    }
}

Button &PumpSettingsPage::getButton(int id) {
    if (id == SET_CLOCK_BASED) return _setClockBasedActivationButton;
    if (id == SET_TEMP_BASED)  return _setTempBasedActivationButton;
    return _backButton;
}
