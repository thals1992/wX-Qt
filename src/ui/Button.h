// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTBUTTON_H
#define OBJECTBUTTON_H

#include <functional>
#include <QPushButton>
#include "ui/Icon.h"

class Button {
public:
    Button();
    Button(QWidget *, QString);
    Button(QWidget *, Icon, QString);
    QPushButton * get();
    void connect(std::function<void()>);
    void setText(const QString&);
    QString getText() const;
    void setVisible(bool);
    void setCheckable(bool);
    void setChecked(bool);

private:
    QWidget * parent;
    QPushButton * button;
};

#endif  // OBJECTBUTTON_H
