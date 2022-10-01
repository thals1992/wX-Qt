// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef TIMER_H
#define TIMER_H

#include <functional>
#include <QTimer>

using std::function;

class Timer {
public:
    Timer(QObject *, const function<void()>&);
    bool isActive() const;
    void stop();
    void start(int);
    void setInterval(int);

private:
    QTimer * timer;
};

#endif  // TIMER_H
