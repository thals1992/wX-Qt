// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef FUTURETEXT_H
#define FUTURETEXT_H

#include <functional>
#include <QObject>
#include <QWidget>

class FutureText : public QObject {

    Q_OBJECT

public:
    FutureText(QWidget *, const QString&, std::function<void(QString)>);
    QString html;

private:
    std::function<void(QString)> updateFunc2;
};

#endif  // FUTURETEXT_H
