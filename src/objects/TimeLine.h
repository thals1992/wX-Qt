// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef TIMELINE_H
#define TIMELINE_H

#include <functional>
#include <QObject>
#include <QTimeLine>

using std::function;

class TimeLine {
public:
    TimeLine(QObject *, int, int, const function<void(int)>&);
    void stop();
    void setCount(int);
    void setSpeed(int);
    int getCount() const;
    void start();
    bool isRunning() const;

private:
    QTimeLine::State state();
    int count;
    QTimeLine * timeLine;
    bool running{false};
};

#endif  // TIMELINE_H
