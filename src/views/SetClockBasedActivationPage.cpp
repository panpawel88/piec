//
// Created by user on 05.11.2021.
//

#include "SetClockBasedActivationPage.h"
#include "colors.h"

namespace {
    enum Values {
        START_HOURS_HIGHER,
        START_HOURS_LOWER,
        START_FIRST_SEPARATOR,
        START_MINUTES_HIGHER,
        START_MINUTES_LOWER,
        START_SECOND_SEPARATOR,
        START_SECONDS_HIGHER,
        START_SECONDS_LOWER,
        SEPARATOR,
        STOP_HOURS_HIGHER,
        STOP_HOURS_LOWER,
        STOP_FIRST_SEPARATOR,
        STOP_MINUTES_HIGHER,
        STOP_MINUTES_LOWER,
        STOP_SECOND_SEPARATOR,
        STOP_SECONDS_HIGHER,
        STOP_SECONDS_LOWER,
    };
}

SetClockBasedActivationPage::SetClockBasedActivationPage(PageManager &manager, Display &display, Context &context,
                                                         uint8_t pumpIndex) : Page(display),
                                                                              _manager(manager),
                                                                              _display(display),
                                                                              _tft(_display.tft()),
                                                                              _context(context),
                                                                              _pumpIndex(pumpIndex),
                                                                              _headerDrawn(false),
                                                                              _selectedValue(0),
                                                                              _unfocusedColor(
                                                                                      _tft.color565(223, 223, 223)),
                                                                              _focusedColor(
                                                                                      _tft.color565(223, 223, 0)) {


    PumpHeat *pump = _context.getPump(_pumpIndex);
    PumpData data = pump->getData();
    if (data.activationMode == ClockBased)
        setValues(data.cd.start, data.cd.stop);
    else
        setValues(Time{}, Time{});
    int16_t x = Margin * 2;
    int16_t y = _display.height() / 2;
    const GFXfont *font = _display.fontManager().getSegoeui20pt7b();
    for (uint8_t i = 0; i < 17; ++i) {
        Label *label = new Label(_tft);
        label->setCursor(x, y);
        label->setFont(font);
        label->setColor(BLACK);
        label->setBackgroundColor(_unfocusedColor);
        label->setForegroundColor(_unfocusedColor);

        if (i == START_FIRST_SEPARATOR || i == START_SECOND_SEPARATOR || i == STOP_FIRST_SEPARATOR ||
            i == STOP_SECOND_SEPARATOR)
            label->setText(F(":"));
        else if (i == SEPARATOR)
            label->setText(F("---"));
        else
            label->setText(String(_values[i]));
        int16_t boundsX;
        int16_t boundsY;
        uint16_t boundsW;
        uint16_t boundsH;
        label->getBounds(boundsX, boundsY, boundsW, boundsH);
        x = boundsX + boundsW + Margin;
        _valueLabels[i] = label;
    }

    _valueLabels[0]->setForegroundColor(_focusedColor);
}

SetClockBasedActivationPage::~SetClockBasedActivationPage() {
    for (uint8_t i = 0; i < 17; ++i) {
        delete _valueLabels[i];
    }
}

void SetClockBasedActivationPage::draw() {
    if (!_headerDrawn) {
        drawHeader(F("TRYB ZEGARA"));
        _headerDrawn = true;
    }
    for (uint8_t i = 0; i < 17; ++i) {
        _valueLabels[i]->draw();
    }
}

void SetClockBasedActivationPage::handleEvent(Event event) {
    if (event == UP) {
        _values[_selectedValue]++;
        if (_values[_selectedValue] == getMaxValue(_selectedValue))
            _values[_selectedValue] = 0;
        _valueLabels[_selectedValue]->setText(String(_values[_selectedValue]));
    } else if (event == DOWN) {
        if (_values[_selectedValue] == 0)
            _values[_selectedValue] = getMaxValue(_selectedValue);
        _values[_selectedValue]--;
        _valueLabels[_selectedValue]->setText(String(_values[_selectedValue]));
    } else if (event == RIGHT) {
        uint8_t lastSelectedValue = _selectedValue;
        if (_selectedValue < STOP_SECONDS_LOWER)
            _selectedValue++;
        if (_selectedValue == START_FIRST_SEPARATOR || _selectedValue == START_SECOND_SEPARATOR ||
            _selectedValue == SEPARATOR || _selectedValue == STOP_FIRST_SEPARATOR ||
            _selectedValue == STOP_SECOND_SEPARATOR)
            _selectedValue++;
        if (lastSelectedValue != _selectedValue) {
            _valueLabels[lastSelectedValue]->setForegroundColor(_unfocusedColor);
            _valueLabels[_selectedValue]->setForegroundColor(_focusedColor);
        }
    } else if (event == LEFT) {
        uint8_t lastSelectedValue = _selectedValue;
        if (_selectedValue > 0)
            _selectedValue--;
        if (_selectedValue == START_FIRST_SEPARATOR || _selectedValue == START_SECOND_SEPARATOR ||
            _selectedValue == SEPARATOR || _selectedValue == STOP_FIRST_SEPARATOR ||
            _selectedValue == STOP_SECOND_SEPARATOR)
            _selectedValue--;
        if (lastSelectedValue != _selectedValue) {
            _valueLabels[lastSelectedValue]->setForegroundColor(_unfocusedColor);
            _valueLabels[_selectedValue]->setForegroundColor(_focusedColor);
        }
    }
}

void SetClockBasedActivationPage::setValues(const Time &start, const Time &stop) {
    _values[START_HOURS_HIGHER] = start.hours / 10;
    _values[START_HOURS_LOWER] = start.hours % 10;
    _values[START_MINUTES_HIGHER] = start.minutes / 10;
    _values[START_MINUTES_LOWER] = start.minutes % 10;
    _values[START_SECONDS_HIGHER] = start.seconds / 10;
    _values[START_SECONDS_LOWER] = start.seconds % 10;
    _values[STOP_HOURS_HIGHER] = stop.hours / 10;
    _values[STOP_HOURS_LOWER] = stop.hours % 10;
    _values[STOP_MINUTES_HIGHER] = stop.minutes / 10;
    _values[STOP_MINUTES_LOWER] = stop.minutes % 10;
    _values[STOP_SECONDS_HIGHER] = stop.seconds / 10;
    _values[STOP_SECONDS_LOWER] = stop.seconds % 10;
}

int SetClockBasedActivationPage::getMaxValue(int selectedValue) const {
    if (selectedValue == START_HOURS_HIGHER || selectedValue == STOP_HOURS_HIGHER) return 3;
    if (selectedValue == START_HOURS_LOWER || selectedValue == STOP_HOURS_LOWER) return 10;
    if (selectedValue == START_MINUTES_HIGHER || selectedValue == STOP_MINUTES_HIGHER) return 6;
    if (selectedValue == START_SECONDS_HIGHER || selectedValue == STOP_SECONDS_HIGHER) return 6;
    return 10;
}


