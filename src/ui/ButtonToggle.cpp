// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ButtonToggle.h"
#include <QString>
#include "common/GlobalVariables.h"
#include "ui/IconMapping.h"

ButtonToggle::ButtonToggle(QWidget * parent, Icon icon, const string& label)
    : parent{ parent }
    , button{ new QPushButton{parent} }
{
    button->setToolTip(QString::fromStdString(label));
    if (icon != None) {
        const auto pixmap = QPixmap(QString::fromStdString(GlobalVariables::imageDir + IconMapping::toString(icon)));
        const auto buttonIcon = QIcon(pixmap);
        button->setIcon(buttonIcon);
    }
    if (!label.empty() && icon == None) {
        button->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        button->setText(QString::fromStdString(label));
    }
    setCheckable(true);
}

void ButtonToggle::connect(const function<void()>& fn) {
    QObject::connect(button, &QPushButton::released, parent, fn);
}

void ButtonToggle::setText(const string& s) {
    button->setText(QString::fromStdString(s));
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

bool ButtonToggle::isChecked() {
    return button->isChecked();
}

void ButtonToggle::setActive(bool b) {
    button->setChecked(b);
}

QPushButton * ButtonToggle::getView() {
    return button;
}
