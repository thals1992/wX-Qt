// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/StatusBar.h"

StatusBar::StatusBar(QWidget * parent)
    : statusBar{ new QStatusBar{parent} }
{}

void StatusBar::addWidget(QWidget * w) {
    statusBar->addWidget(w);
}

void StatusBar::addWidget(Widget2& w) {
    statusBar->addWidget(w.getView());
}

void StatusBar::setVisible(bool b) {
    statusBar->setVisible(b);
}

QStatusBar * StatusBar::getView() {
    return statusBar;
}
