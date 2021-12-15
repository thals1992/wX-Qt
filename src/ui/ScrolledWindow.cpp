// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ScrolledWindow.h"
#include <QScrollArea>

ScrolledWindow::ScrolledWindow() {
}

ScrolledWindow::ScrolledWindow(Window * parent, QBoxLayout * layout) {
    auto scrollArea = new QScrollArea(parent);
    scrollArea->setWidget(parent->centralWidget);
    scrollArea->setWidgetResizable(true);
    parent->setCentralWidget(scrollArea);
    parent->centralWidget->setLayout(layout);
    parent->show();
}

ScrolledWindow::ScrolledWindow(Window * parent, VBox& layout) {
    auto scrollArea = new QScrollArea(parent);
    scrollArea->setWidget(parent->centralWidget);
    scrollArea->setWidgetResizable(true);
    parent->setCentralWidget(scrollArea);
    parent->centralWidget->setLayout(layout.get());
    parent->show();
}
