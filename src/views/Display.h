//
// Created by user on 01.11.2021.
//

#ifndef STEPPER_DEMO_DISPLAY_H
#define STEPPER_DEMO_DISPLAY_H

#include <MCUFRIEND_kbv.h>
#include "FontManager.h"

typedef MCUFRIEND_kbv TFT;

class Display {
public:
    explicit Display(FontManager& fontManager);
    void setup();

    uint16_t width() const { return _width; }
    uint16_t height() const { return _height; }

    uint16_t smallFontHeight() const { return _smallFontHeight; }
    uint16_t bigFontHeight() const { return _bigFontHeight; }

    TFT& tft() { return _tft; }
    FontManager& fontManager() { return _fontManager; }

private:
    TFT _tft;
    FontManager& _fontManager;

    uint16_t _width;
    uint16_t _height;

    uint16_t _smallFontHeight{};
    uint16_t _bigFontHeight{};
};


#endif //STEPPER_DEMO_DISPLAY_H
