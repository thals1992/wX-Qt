// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ButtonToggle.h"
#include "common/GlobalVariables.h"
#include "ui/IconMapping.h"

ButtonToggle::ButtonToggle() {
}

ButtonToggle::ButtonToggle(QWidget * parent, Icon icon, QString label) {
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
    setCheckable(true);
}

void ButtonToggle::connect(std::function<void()> f) {
    QObject::connect(get(), &QPushButton::released, parent, f);
}

void ButtonToggle::setText(QString s) {
    button->setText(s);
}

void ButtonToggle::setVisible(bool b) {
    button->setVisible(b);
}

void ButtonToggle::setCheckable(bool  b) {
    button->setCheckable(b);
}

void ButtonToggle::setChecked(bool b) {
    button->setChecked(b);
}

void ButtonToggle::setActive(bool b) {
    button->setChecked(b);
}

QPushButton * ButtonToggle::get() {
    return button;
}
