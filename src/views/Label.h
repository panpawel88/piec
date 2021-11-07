//
// Created by user on 05.11.2021.
//

#ifndef PIEC_LABEL_H
#define PIEC_LABEL_H

#include <Arduino.h>
#include "Display.h"

class Label {
public:
    explicit Label(TFT& tft);

    void setText(const String& text);
    void setFont(const GFXfont *f);
    void setCursor(int16_t x, int16_t y);
    void setColor(uint16_t color);
    void setForegroundColor(uint16_t color);
    void setBackgroundColor(uint16_t color);

    void getBounds(int16_t& x, int16_t& y, uint16_t& w, uint16_t& h);

    void draw();

private:
    TFT& _tft;
    String _text;
    const GFXfont* _font{};
    int16_t _x{};
    int16_t _boundsX{};
    int16_t _y{};
    int16_t _boundsY{};
    uint16_t _w{};
    uint16_t _h{};
    uint16_t _color{};
    uint16_t _fgColor{};
    uint16_t _bgColor{};

};


#endif //PIEC_LABEL_H
