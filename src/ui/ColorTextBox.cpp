// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ColorTextBox.h"

ColorTextBox::ColorTextBox() {
}

ColorTextBox::ColorTextBox(QWidget * parent) {
    label = new QLabel(parent);
}

void ColorTextBox::setText(const QString& s) {
    label->setText(s);
}

void ColorTextBox::setBackGroundRed() {
    label->setStyleSheet("QLabel { background-color : red ; color : white; }");
}

void ColorTextBox::setBackGroundGreen() {
    label->setStyleSheet("QLabel { background-color : green ; color : white; }");
}

QLabel * ColorTextBox::get() {
    return label;
}
