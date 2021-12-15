// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef CALENDAR_H
#define CALENDAR_H

#include <functional>
#include <QCalendarWidget>
#include <QString>

class Calendar {
public:
    Calendar();
    explicit Calendar(QWidget * parent);
    void connect(std::function<void()>);
    int getDay();
    int getMonth();
    int getYear();
    QCalendarWidget * get();

private:
    QCalendarWidget * cal;
    QWidget * parent;
    QDate date;
};

#endif  // CALENDAR_H
