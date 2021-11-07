//
// Created by user on 01.11.2021.
//

#ifndef STEPPER_DEMO_BUTTON_H
#define STEPPER_DEMO_BUTTON_H

#include <Arduino.h>
#include "Display.h"

class Button {
public:
    explicit Button(Display& display, const String& label);

    void setup();

    void setFocus(bool isFocused);

    bool focused() const {
        return _focused;
    }

    void getSize(uint16_t *width, uint16_t *height) const;

    void setSize(uint16_t width, uint16_t height);

    void setPosition(int16_t x, int16_t y);

    void draw();

private:
    TFT& _tft;
    FontManager& _fontManager;
    String _label;
    int16_t _x;
    int16_t _y;
    int16_t _labelXOffset;
    int16_t _labelYOffset;
    uint16_t _width;
    uint16_t _height;
    uint16_t _labelWidth;
    uint16_t _labelHeight;
    bool _focused;
    bool _dirty;
};


#endif //STEPPER_DEMO_BUTTON_H
