// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/FutureVoid.h"
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <QObject>

FutureVoid::FutureVoid() {}

FutureVoid::FutureVoid(QWidget * parent, std::function<void()> downloadFunc, std::function<void()> updateFunc) {
    auto * watcher = new QFutureWatcher<void>;
    const QFuture<void> future = QtConcurrent::run(downloadFunc);
    watcher->setFuture(future);
    QObject::connect(watcher, &QFutureWatcher<void>::finished, parent, updateFunc);
}
