// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef FUTUREBYTES_H
#define FUTUREBYTES_H

#include <functional>
#include <string>
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <QWidget>

using std::function;
using std::string;

class FutureBytes : public QObject {

    Q_OBJECT

public:
    FutureBytes(QWidget *, const string&, const function<void(const QByteArray&)>&);

private:
    function<void(const QByteArray&)> updateFunc;
    QFutureWatcher<void> * watcher;
    QFuture<void> future;
    QByteArray ba;
};

#endif  // FUTUREBYTES_H
