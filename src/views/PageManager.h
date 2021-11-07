//
// Created by user on 01.11.2021.
//

#ifndef STEPPER_DEMO_PAGEMANAGER_H
#define STEPPER_DEMO_PAGEMANAGER_H

#include "Constants.h"
#include "Page.h"


class PageManager {
public:
    void setPage(Page *page);
    void handleEvent(Event event);
    void update();
private:
    Page *_page{};
    Page *_nextPage{};
};

#endif //STEPPER_DEMO_PAGEMANAGER_H
