// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef COLOREDBOX_H
#define COLOREDBOX_H

#include <functional>
#include <QLabel>
#include <QString>
#include "objects/WXColor.h"
#include "ui/ClickableLabel.h"

class ColoredBox {
public:
    ColoredBox();
    ColoredBox(QWidget * parent, WXColor wxcolor);
    void regenerate(WXColor wxcolor);
    void connect(std::function<void()>);
    ClickableLabel * get();

private:
    ClickableLabel * colorPatchCurrent;
    int sizeColorBlock = 30;
};

#endif  // COLOREDBOX_H
