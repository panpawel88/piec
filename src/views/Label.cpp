//
// Created by user on 05.11.2021.
//

#include "Label.h"

Label::Label(TFT &tft) : _tft(tft) {
}

void Label::setCursor(int16_t x, int16_t y) {
    _x = x;
    _y = y;
}

void Label::setText(const String &text) {
    _text = text;
}

void Label::draw() {
    if (_w > 0)
        _tft.fillRect(_boundsX, _boundsY, _w, _h, _bgColor);

    _tft.setFont(_font);
    _tft.setCursor(_x, _y);
    _tft.setTextColor(_color);
    getBounds(_boundsX, _boundsY, _w, _h);
    _tft.fillRect(_boundsX, _boundsY, _w, _h, _fgColor);
    _tft.print(_text);
}

void Label::setBackgroundColor(uint16_t color) {
    _bgColor = color;
}

void Label::setColor(uint16_t color) {
    _color = color;
}

void Label::setForegroundColor(uint16_t color) {
    _fgColor = color;
}

void Label::setFont(const GFXfont *f) {
    _font = f;
}

void Label::getBounds(int16_t &x, int16_t &y, uint16_t &w, uint16_t &h) {
    _tft.getTextBounds(_text, _x, _y, &x, &y, &w, &h);
}
