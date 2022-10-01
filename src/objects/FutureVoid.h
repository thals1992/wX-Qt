// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef FUTUREVOID_H
#define FUTUREVOID_H

#include <functional>
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <QObject>
#include <QWidget>

using std::function;

class FutureVoid {
public:
    FutureVoid(QWidget *, const function<void()>&, const function<void()>&);

private:
    function<void()> updateFunc;
    QFutureWatcher<void> * watcher;
    QFuture<void> future;
};

#endif  // FUTUREVOID_H
