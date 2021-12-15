// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef TIMER_H
#define TIMER_H

#include <functional>
#include <QTimer>

class Timer {
public:
    Timer(QObject *, std::function<void()>);
    void update();
    bool isActive() const;
    void stop();
    void start(int);
    void setInterval(int);
    int remainingTime();

private:
    QTimer * timer;
};

#endif  // TIMER_H
