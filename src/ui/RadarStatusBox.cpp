// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/RadarStatusBox.h"

RadarStatusBox::RadarStatusBox() {
}

RadarStatusBox::RadarStatusBox(QWidget * parent) {
    label = new QLabel(parent);
}

void RadarStatusBox::setCurrent(const QString& s) {
    setText(s);
    setBackGroundGreen();
}

void RadarStatusBox::setOld(const QString& s) {
    setText(s);
    setBackGroundRed();
}

void RadarStatusBox::setText(const QString& s) {
    label->setText(s);
}

void RadarStatusBox::setBackGroundRed() {
    label->setStyleSheet("QLabel { background-color : red ; color : white; }");
}

void RadarStatusBox::setBackGroundGreen() {
    label->setStyleSheet("QLabel { background-color : green ; color : white; }");
}

QLabel * RadarStatusBox::get() {
    return label;
}
