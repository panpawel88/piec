//
// Created by user on 01.11.2021.
//

#include <Adafruit_GFX.h>

#include "HomePage.h"
#include "colors.h"
#include "SettingsPage.h"

HomePage::HomePage(PageManager &manager, Display &display, Context &context)
        : Page(display), _manager(manager), _display(display), _tft(_display.tft()), _context(context), _headerDrawn(false),
          _clockValue(_tft),
          _moreButton{} {
    int16_t x = Margin;
    int16_t y = 2 * Margin + _display.height() / 2;

    _moreButton = new Button(display, F("WIECEJ"));
    _moreButton->setup();
    _moreButton->setFocus(true);
    uint16_t width, height;
    _moreButton->getSize(&width, &height);
    _moreButton->setSize(_display.width() - Margin * 2, height);
    _moreButton->setPosition(x, y);

    uint8_t pumpsCount = _context.pumpsCount();
    _pumpStateLabels = new Label*[pumpsCount];
    _pumpStateValues = new Label*[pumpsCount];
    uint16_t displayWidth = _display.width();
    uint16_t bigFontHeight = _display.bigFontHeight();
    y = 4 * Margin + bigFontHeight;
    const GFXfont* font = _display.fontManager().getSegoeui10pt7b();
    for (uint8_t i = 0; i < pumpsCount; ++i) {
        auto* label = new Label(_tft);
        auto* value = new Label(_tft);
        label->setCursor(Margin, y);
        label->setFont(font);
        label->setColor(BLACK);
        label->setBackgroundColor(_tft.color565(223, 223, 223));
        label->setForegroundColor(_tft.color565(223, 223, 223));
        value->setCursor(displayWidth / 2, y);
        value->setFont(font);
        value->setColor(BLACK);
        value->setBackgroundColor(_tft.color565(223, 223, 223));
        value->setForegroundColor(_tft.color565(223, 223, 223));

        label->setText(String(F("STAN P")) + i + String(":"));
        int16_t boundsX;
        int16_t boundsY;
        uint16_t boundsW;
        uint16_t boundsH;
        label->getBounds(boundsX, boundsY, boundsW, boundsH);
        y = boundsY + 2 * boundsH + Margin;
        _pumpStateLabels[i] = label;
        _pumpStateValues[i] = value;
    }

    _clockValue.setCursor(Margin, y);
    _clockValue.setFont(font);
    _clockValue.setColor(BLACK);
    _clockValue.setBackgroundColor(_tft.color565(223, 223, 223));
    _clockValue.setForegroundColor(_tft.color565(223, 223, 223));
}

HomePage::~HomePage() {
    delete _moreButton;
    uint8_t pumpsCount = _context.pumpsCount();
    for (uint8_t i = 0; i < pumpsCount; ++i) {
        delete _pumpStateLabels[i];
        delete _pumpStateValues[i];
    }

    delete[] _pumpStateLabels;
    delete[] _pumpStateValues;
}

void HomePage::draw() {
    uint8_t pumpsCount = _context.pumpsCount();
    if (!_headerDrawn) {
        drawHeader(F("STEROWNIK PIECA"));
        for (uint8_t i = 0; i < pumpsCount; ++i) {
            _pumpStateLabels[i]->draw();
        }

        _headerDrawn = true;
    }

    for (uint8_t i = 0; i < pumpsCount; ++i) {
        bool state = _context.getPump(i)->state();
        _pumpStateValues[i]->setText(String(state));
        _pumpStateValues[i]->draw();
    }

    Time currentTime{};
    _context.clock().getTime(currentTime);
    _lastTime = currentTime;
    _clockValue.setText(currentTime.ToString());
    _clockValue.draw();

    _moreButton->draw();
}

void HomePage::handleEvent(Event event) {
    if (event == ENTER) {
        Page *page = new SettingsPage(_manager, _display, _context);
        _manager.setPage(page);
    }
}

bool HomePage::isDirty() const {
    Time time{};
    _context.clock().getTime(time);
    return Page::isDirty() && time != _lastTime;
}
