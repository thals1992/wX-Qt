// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef COLOREDBOX_H
#define COLOREDBOX_H

#include <functional>
#include <QLabel>
#include "objects/WXColor.h"
#include "ui/ClickableLabel.h"

using std::function;

class ColoredBox {
public:
    ColoredBox(QWidget *, const WXColor&);
    void regenerate(const WXColor&);
    void connect(const function<void()>&);
    ClickableLabel * get();

private:
    ClickableLabel * colorPatchCurrent;
    int sizeColorBlock{30};
};

#endif  // COLOREDBOX_H
