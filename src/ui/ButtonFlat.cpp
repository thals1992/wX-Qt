// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ButtonFlat.h"
#include "common/GlobalVariables.h"

ButtonFlat::ButtonFlat() {
}

ButtonFlat::ButtonFlat(QString imageName, QString label, QWidget * parent) {
    this->parent = parent;
    const auto iconSize = 40;
    button = new QPushButton(parent);
    button->setFlat(true);
    button->setToolTip(label);
    if (imageName != "") {
        auto pixmap = QPixmap(GlobalVariables::imageDir + imageName);
        auto buttonIcon = QIcon(pixmap);
        button->setIcon(buttonIcon);
        button->setIconSize(QSize(iconSize, iconSize));
    }
}

QPushButton * ButtonFlat::get() {
    return button;
}

void ButtonFlat::connect(std::function<void()> f) {
    QObject::connect(get(), &QPushButton::released, parent, f);
}

void ButtonFlat::setText(const QString& s) {
    button->setText(s);
}

QString ButtonFlat::getText() const {
    return button->text();
}

void ButtonFlat::setVisible(bool b) {
    button->setVisible(b);
}

void ButtonFlat::setCheckable(bool b) {
    button->setCheckable(b);
}

void ButtonFlat::setChecked(bool b) {
    button->setChecked(b);
}
