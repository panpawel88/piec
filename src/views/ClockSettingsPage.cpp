//
// Created by user on 05.11.2021.
//

#include "ClockSettingsPage.h"

ClockSettingsPage::ClockSettingsPage(PageManager &manager, Display &display, Context &context) : Page(display),
                                                                                                 _manager(manager),
                                                                                                 _display(display),
                                                                                                 _tft(_display.tft()),
                                                                                                 _context(context),
                                                                                                 _headerDrawn(false) {
}

ClockSettingsPage::~ClockSettingsPage() = default;

void ClockSettingsPage::draw() {
    if (!_headerDrawn) {
        drawHeader(F("USTAWIENIA ZEGARA"));
        _headerDrawn = true;
    }
}

void ClockSettingsPage::handleEvent(Event event) {

}
