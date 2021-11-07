//
// Created by user on 01.11.2021.
//

#include "Button.h"

#include <Adafruit_GFX.h>

#include "colors.h"
#include "Constants.h"

Button::Button(Display &display, const String& label)
        : _tft(display.tft()), _fontManager(display.fontManager()), _label(label), _x(), _y(), _labelXOffset(), _labelYOffset(), _width(), _height(),
          _labelWidth(),
          _labelHeight(), _focused(false),
          _dirty(true) {
}

void Button::setup() {
    int16_t x1, y1;
    uint16_t w, h;
    _tft.setFont(_fontManager.getSegoeui10pt7b());
    _tft.getTextBounds(_label, 0, 0, &x1, &y1, &w, &h);
    _labelXOffset = x1;
    _labelYOffset = y1;
    _labelWidth = w;
    _labelHeight = h;
    _width = _labelWidth + 2 * Margin;
    _height = _labelHeight + 2 * Margin;
}

void Button::draw() {
    if (!_dirty)
        return;

    int16_t radius = 10;

    _tft.drawRoundRect(_x, _y, _width, _height, radius, BLACK);
    if (_focused) {
        _tft.fillRoundRect(_x + 1, _y + 1, _width - 2, _height - 2, radius, _tft.color565(126, 126, 126));
        _tft.setTextColor(WHITE);
    } else {
        _tft.fillRoundRect(_x + 1, _y + 1, _width - 2, _height - 2, radius, WHITE);
        _tft.setTextColor(BLACK);
    }
    _tft.setFont(_fontManager.getSegoeui10pt7b());
    _tft.setCursor(_x + _width / 2 - _labelWidth / 2 - _labelXOffset,
                  _y + _height / 2 - _labelHeight / 2 - _labelYOffset);
    _tft.print(_label);
    _dirty = false;
}

void Button::setFocus(bool isFocused) {
    if (_focused != isFocused) {
        _focused = isFocused;
        _dirty = true;
    }
}

void Button::getSize(uint16_t *width, uint16_t *height) const {
    *width = _width;
    *height = _height;
}

void Button::setSize(uint16_t width, uint16_t height) {
    if (_width != width || _height != height) {
        _width = width;
        _height = height;
        _dirty = true;
    }
}

void Button::setPosition(int16_t x, int16_t y) {
    if (_x != x || _y != y) {
        _x = x;
        _y = y;
        _dirty = true;
    }
}
