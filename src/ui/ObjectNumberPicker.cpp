// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ObjectNumberPicker.h"
#include <QtGlobal>
#include <QObject>
#include "settings/RadarPreferences.h"
#include "settings/UIPreferences.h"
#include "util/Utility.h"

ObjectNumberPicker::ObjectNumberPicker() {
}

ObjectNumberPicker::ObjectNumberPicker(QWidget * parent, const QString& label, const QString& pref, int defaultValue, int low, int up, int step) : QObject(parent) {
    this->parent = parent;
    this->pref = pref;
    this->defaultValue = defaultValue;

    box = HBox(parent);
    text = Text(parent, label);
    text.setWrap(false);
    qSpinBox = new QSpinBox(parent);
    box.addWidget(qSpinBox);
    box.addWidget(text.get());


    qSpinBox->setRange(low, up);
    qSpinBox->setSingleStep(step);
    qSpinBox->setValue(getCurrentValue());

    //qSpinBox.textChanged.connect(this, "updateNp(String)");
    //connect(get(), &QSpinBox::textChanged, this, [this] (QString s) { updateNp(s); });

// #if QT_VERSION >= 0x051400 //0x060000
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    QObject::connect(qSpinBox, static_cast<void (QSpinBox::*)(const QString &)>(&QSpinBox::textChanged), this, [=](QString val) { updateNp(val); });
#else
    QObject::connect(qSpinBox, static_cast<void (QSpinBox::*)(const QString &)>(&QSpinBox::valueChanged), this, [=](QString val) { updateNp(val); });
#endif
}

void ObjectNumberPicker::updateNp(const QString& newValue) {
    Utility::writePref(pref, newValue);
    RadarPreferences::initialize();
    UIPreferences::initialize();
}

int ObjectNumberPicker::getCurrentValue() {
    return Utility::readPrefInt(pref, defaultValue);
}

QBoxLayout * ObjectNumberPicker::get() {
    return box.get();
}
