// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/TimeLine.h"

TimeLine::TimeLine() {
}

TimeLine::TimeLine(QObject * parent, int speed, int count, std::function<void(int)> updateFn) {
    this->count = count;
    timeLine = new QTimeLine(speed, parent);
    timeLine->setFrameRange(0, count - 1);
    timeLine->setLoopCount(0);
    QObject::connect(timeLine, &QTimeLine::frameChanged, parent, updateFn);
}

void TimeLine::stop() {
    running = false;
    timeLine->stop();
}

void TimeLine::setCount(int count) {
    this->count = count;
    timeLine->setFrameRange(0, count - 1);
}

void TimeLine::setSpeed(int s) {
    timeLine->setDuration(s);
}

int TimeLine::getCount() {
    return count;
}

void TimeLine::start() {
    running = true;
    timeLine->start();
}

bool TimeLine::isRunning() {
    return running;
}

QTimeLine::State TimeLine::state() {
    return timeLine->state();
}
