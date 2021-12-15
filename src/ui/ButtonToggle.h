// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef BUTTONTOGGLE_H
#define BUTTONTOGGLE_H

#include <functional>
#include <QPushButton>
#include <QString>
#include "ui/Icon.h"

class ButtonToggle {
public:
    ButtonToggle();
    ButtonToggle(QWidget *, Icon, QString);
    void connect(QObject, QString);
    void connect(QString);
    void connect(std::function<void()>);
    void setText(QString);
    void setVisible(bool);
    void setCheckable(bool);
    void setChecked(bool);
    void setActive(bool);
    QPushButton * get();

private:
    QWidget * parent;
    QPushButton * button;
};

#endif  // BUTTONTOGGLE_H
