//
// Created by user on 01.11.2021.
//

#ifndef STEPPER_DEMO_PAGE_H
#define STEPPER_DEMO_PAGE_H

#include "Constants.h"
#include "Display.h"

class Page {
public:

    virtual ~Page() = default;

    virtual void draw() = 0;

    virtual bool isDirty() const { return _dirty; }

    virtual void handleEvent(Event) = 0;

protected:
    explicit Page(Display& display) : _display(display), _dirty(true) {}

    void setDirty() {
        _dirty = true;
    }

    void drawHeader(const String& header);

    Display& _display;
    bool _dirty;
};



#endif //STEPPER_DEMO_PAGE_H
