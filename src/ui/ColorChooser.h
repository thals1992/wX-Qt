// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef COLORCHOOSER_H
#define COLORCHOOSER_H

#include <QWidget>
#include "ui/ColoredBox.h"
#include "objects/WXColor.h"

class ColorChooser {
public:
    ColorChooser(QWidget *, WXColor *, ColoredBox *);
    void run();

private:
    QWidget * parent;
    WXColor * wxcolor;
    ColoredBox * colorPatchCurrent;
};

#endif  // COLORCHOOSER_H
