//
// Created by user on 01.11.2021.
//

#include "PageManager.h"

void PageManager::setPage(Page *page) {
    Serial.println("PageManager::setPage");
    if (page == nullptr)
        Serial.println("PageManager::setPage page is null");
    _nextPage = page;
}

void PageManager::handleEvent(Event event) {
    if (_page == nullptr)
        return;
    _page->handleEvent(event);
}

void PageManager::update() {
    if (_nextPage != nullptr) {
        Serial.println("PageManager::update swaping page");
        delete _page;
        _page = _nextPage;
        _nextPage = nullptr;
    }

    if (_page != nullptr && _page->isDirty()) {
        _page->draw();
    }
}
