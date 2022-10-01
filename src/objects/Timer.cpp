// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/Timer.h"

Timer::Timer(QObject * parent, const function<void()>& updateFn)
    : timer{ new QTimer{parent} }
{
    QObject::connect(timer, &QTimer::timeout, parent, [updateFn] { updateFn(); });
}

bool Timer::isActive() const {
    return timer->isActive();
}

void Timer::stop() {
    timer->stop();
}

void Timer::start(int msec) {
    timer->start(msec);
}

void Timer::setInterval(int msec) {
    timer->setInterval(msec);
}

// KEEP
// int Timer::remainingTime() {
//    return timer->remainingTime();
// }
