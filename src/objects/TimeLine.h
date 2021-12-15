// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef TIMELINE_H
#define TIMELINE_H

#include <functional>
#include <QString>
#include <QObject>
#include <QTimeLine>

class TimeLine {
public:
    TimeLine();
    TimeLine(QObject *, int, int, std::function<void(int)>);
    void update(int i);
    void stop();
    void setCount(int);
    void setSpeed(int);
    int getCount();
    void start();
    bool isRunning();

private:
    QTimeLine::State state();
    QTimeLine * timeLine;
    int count;
    bool running = false;
};

#endif  // TIMELINE_H
