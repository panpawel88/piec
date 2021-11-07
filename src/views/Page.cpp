//
// Created by user on 05.11.2021.
//

#include "Page.h"
#include "colors.h"

void Page::drawHeader(const String &header) {
    TFT &tft = _display.tft();
    tft.fillScreen(tft.color565(223, 223, 223));
    tft.fillRoundRect(0, -Margin, _display.width(), 3 * Margin + _display.bigFontHeight(), 10,
                      tft.color565(101, 96, 198));
    tft.setCursor(Margin, Margin + _display.bigFontHeight());
    tft.setFont(_display.fontManager().getSegoeui20pt7b());
    tft.setTextColor(WHITE);
    tft.print(header);
}
