// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/Button.h"
#include "common/GlobalVariables.h"
#include "ui/IconMapping.h"

Button::Button() {
}

Button::Button(QWidget * parent, QString label) {
    this->parent = parent;
    button = new QPushButton(parent);
    button->setToolTip(label);
    if (label != "") {
        button->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        button->setText(label);
    }
}

Button::Button(QWidget * parent, Icon icon, QString label) {
    this->parent = parent;
    button = new QPushButton(parent);
    button->setToolTip(label);
    if (icon != Icon::None) {
        auto pixmap = QPixmap(GlobalVariables::imageDir + IconMapping::toString(icon));
        auto buttonIcon = QIcon(pixmap);
        button->setIcon(buttonIcon);
    }
    if (label != "" && icon == Icon::None) {
        button->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        button->setText(label);
    }
}

QPushButton * Button::get() {
    return button;
}

void Button::connect(std::function<void()> f) {
    QObject::connect(get(), &QPushButton::released, parent, f);
}

void Button::setText(const QString& s) {
    button->setText(s);
}

QString Button::getText() const {
    return button->text();
}

void Button::setVisible(bool b) {
    button->setVisible(b);
}

void Button::setCheckable(bool b) {
    button->setCheckable(b);
}

void Button::setChecked(bool b) {
    button->setChecked(b);
}
