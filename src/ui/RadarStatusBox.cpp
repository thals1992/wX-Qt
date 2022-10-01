// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/RadarStatusBox.h"

RadarStatusBox::RadarStatusBox(QWidget * parent)
    : parent{ parent }
    , label{ new ClickableLabel{parent} }
{}

void RadarStatusBox::setCurrent(const string& s) {
    setText(s);
    setBackGroundGreen();
}

void RadarStatusBox::setOld(const string& s) {
    setText(s);
    setBackGroundRed();
}

void RadarStatusBox::setText(const string& s) {
    label->setText(QString::fromStdString(s));
}

void RadarStatusBox::setBackGroundRed() {
    label->setStyleSheet("QLabel { background-color : red ; color : white; }");
}

void RadarStatusBox::setBackGroundGreen() {
    label->setStyleSheet("QLabel { background-color : green ; color : white; }");
}

void RadarStatusBox::connect(const function<void()>& fn) {
    QObject::connect(label, &ClickableLabel::clicked, parent, fn);
}

ClickableLabel * RadarStatusBox::get() {
    return label;
}
