// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef FUTUREBYTES_H
#define FUTUREBYTES_H

#include <functional>
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <QWidget>

class FutureBytes : public QObject {

    Q_OBJECT

public:
    FutureBytes(QWidget *, const QString&, std::function<void(const QByteArray&)>);

private:
    QByteArray ba;
    QFuture<void> future;
    QFutureWatcher<void> * watcher;
    std::function<void(const QByteArray&)> updateFunc2;
};

#endif  // FUTUREBYTES_H
