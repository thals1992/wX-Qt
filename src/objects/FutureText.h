// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef FUTURETEXT_H
#define FUTURETEXT_H

#include <functional>
#include <string>
#include <QObject>
#include <QWidget>
#include <QFutureWatcher>

using std::function;
using std::string;

class FutureText : public QObject {

    Q_OBJECT

public:
    FutureText(QWidget *, const string&, const function<void(string)>&);

private:
    function<void(string)> updateFunc;
    QFutureWatcher<void> * watcher;
    QFuture<void> future;
    string html;
};

#endif  // FUTURETEXT_H
