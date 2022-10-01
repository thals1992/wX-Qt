// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/FutureVoid.h"

FutureVoid::FutureVoid(QWidget * parent, const function<void()>& downloadFunc, const function<void()>& updateFunc)
    : updateFunc{ updateFunc }
    , watcher{ new QFutureWatcher<void> }
    , future{ QtConcurrent::run(downloadFunc) }
{
    watcher->setFuture(future);
    QObject::connect(watcher, &QFutureWatcher<void>::finished, parent, [this] {
        this->updateFunc();
        delete watcher;
        delete this;
    });
}
