// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef HOURLY_H
#define HOURLY_H

#include "ui/Window.h"
#include "ui/ScrolledWindow.h"
#include "ui/Text.h"
#include "ui/VBox.h"

class Hourly : public Window {
public:
    explicit Hourly(QWidget *);

private:
    VBox box;
    ScrolledWindow sw;
    Text text;
};

#endif  // HOURLY_H
