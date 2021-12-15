// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QStatusBar>

class StatusBar {
public:
    StatusBar();
    explicit StatusBar(QWidget * parent);
    void addWidget(QWidget * w);
    void setVisible(bool);
    QStatusBar * get();

private:
    QStatusBar * statusBar;
};

#endif  // STATUSBAR_H
