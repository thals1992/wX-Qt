// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTCOLORLABEL_H
#define OBJECTCOLORLABEL_H

#include <QLabel>
#include <QWidget>
#include "objects/WXColor.h"
#include "ui/ColoredBox.h"
#include "ui/HBox.h"
#include "ui/Button.h"
#include "ui/Text.h"

class ColorLabel : public HBox {
public:
    ColorLabel(QWidget *, const WXColor&);

private:
    void launchColorPicker();
    QWidget * parent;
    WXColor wxcolor;
    ColoredBox colorPatchCurrent;
    Text label;
};

#endif  // OBJECTCOLORLABEL_H
