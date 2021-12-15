// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include <QColorDialog>
#include "ui/ColorChooser.h"
#include "objects/Color.h"

ColorChooser::ColorChooser() {
}

ColorChooser::ColorChooser(QWidget * parent, WXColor * wxcolor, ColoredBox * colorPatchCurrent) {
    this->parent = parent;
    this->wxcolor = wxcolor;
    this->colorPatchCurrent = colorPatchCurrent;
}

void ColorChooser::run() {
    auto qColorDialog = new QColorDialog(Color::qtBlack(), parent);
    const QColor color = qColorDialog->getColor(wxcolor->qcolorDefault);
    if (color.isValid()) {
        int red = color.red();
        int green = color.green();
        int blue = color.blue();
        int colorAsInt = Color::qcolorToInt(color);
        wxcolor->red = red;
        wxcolor->green = green;
        wxcolor->blue = blue;
        wxcolor->setValue(colorAsInt);
        colorPatchCurrent->regenerate(*wxcolor);
    }
}
