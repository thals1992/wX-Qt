// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SCROLLEDWINDOW_H
#define SCROLLEDWINDOW_H

#include <QBoxLayout>
#include "ui/VBox.h"
#include "ui/Window.h"

class ScrolledWindow {
public:
    ScrolledWindow();
    ScrolledWindow(Window * parent, QBoxLayout * layout);
    ScrolledWindow(Window * parent, VBox& layout);
};

#endif  // SCROLLEDWINDOW_H
