// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QStatusBar>
#include "ui/Widget2.h"

class StatusBar : Widget2 {
public:
    explicit StatusBar(QWidget *);
    void addWidget(QWidget *);
    void addWidget(Widget2&);
    void setVisible(bool);
    QStatusBar * getView();

private:
    QStatusBar * statusBar;
};

#endif  // STATUSBAR_H
