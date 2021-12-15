// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ColoredBox.h"

ColoredBox::ColoredBox() {
}

ColoredBox::ColoredBox(QWidget * parent, WXColor wxcolor) {
    colorPatchCurrent = new ClickableLabel(parent);
    colorPatchCurrent->setStyleSheet(wxcolor.styleSheetCurrent());
    colorPatchCurrent->setFixedSize(sizeColorBlock, sizeColorBlock);
}

void ColoredBox::regenerate(WXColor wxcolor) {
    colorPatchCurrent->setStyleSheet(wxcolor.styleSheetCurrent());
}

void ColoredBox::connect(std::function<void()> fn) {
    get()->connect([fn] { fn(); });
}

ClickableLabel * ColoredBox::get() {
    return colorPatchCurrent;
}
