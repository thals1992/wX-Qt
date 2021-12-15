// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/Calendar.h"

Calendar::Calendar() {
}

Calendar::Calendar(QWidget * parent) {
    this->parent = parent;
    cal = new QCalendarWidget(parent);
    // dateEdit->setDateTime(QDateTime::currentDateTime());
    cal->setMinimumDate(QDate(2005, 5, 5));
}

void Calendar::connect(std::function<void()> fn) {
    QObject::connect(cal, &QCalendarWidget::clicked, parent, [this, fn] (QDate d) { this->date = d; fn(); });
}

int Calendar::getDay() {
    return date.day();
}

int Calendar::getMonth() {
    return date.month();
}

int Calendar::getYear() {
    return date.year();
}

QCalendarWidget * Calendar::get() {
    return cal;
}
