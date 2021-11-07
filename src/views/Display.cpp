//
// Created by user on 01.11.2021.
//

#include <Adafruit_GFX.h>

#include "Display.h"
#include "colors.h"


Display::Display(FontManager& manager)
        : _fontManager(manager), _width(400), _height(240) {
}

void Display::setup() {
    _tft.reset();
    _tft.begin(0x65);
    _tft.setRotation(1);
    _tft.fillScreen(WHITE);

    int16_t dummy;
    uint16_t fontWidth;
    _tft.setFont(_fontManager.getSegoeui10pt7b());
    _tft.getTextBounds("P", 0, 0, &dummy, &dummy, &fontWidth, &_smallFontHeight);
    _tft.setFont(_fontManager.getSegoeui20pt7b());
    _tft.getTextBounds("P", 0, 0, &dummy, &dummy, &fontWidth, &_bigFontHeight);
    _tft.setTextColor(BLACK);
}

