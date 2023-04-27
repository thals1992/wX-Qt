// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef CALENDAR_H
#define CALENDAR_H

#include <functional>
#include <QCalendarWidget>
#include "ui/Widget2.h"

using std::function;

class Calendar : public Widget2 {
public:
    explicit Calendar(QWidget * parent);
    void connect(const function<void()>&);
    int getYear();
    int getMonth();
    int getDayOfMonth();
    QCalendarWidget * getView();

private:
    QWidget * parent;
    QCalendarWidget * cal;
    QDate date;
};

#endif  // CALENDAR_H
