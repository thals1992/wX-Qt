// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ObjectSwitch.h"
#include "settings/RadarPreferences.h"
#include "settings/UIPreferences.h"
#include "util/Utility.h"

ObjectSwitch::ObjectSwitch() {
}

ObjectSwitch::ObjectSwitch(QWidget * parent, const QString& label, const QString& pref, bool defaultValue) : QObject(parent) {
    this->parent = parent;
    this->pref = pref;
    this->defaultValue = defaultValue;
    defaultValueAsString = defaultValue ? "true" : "false";
    checkBox = new QCheckBox(label, parent);
    checkBox->setChecked(isTrue());
    connect(checkBox, &QCheckBox::stateChanged, this, [this] { toggle(); });
}

ObjectSwitch * ObjectSwitch::fromPrefBool(QWidget * parent, const PrefBool& prefBool) {
    return new ObjectSwitch(parent, prefBool.label, prefBool.prefToken, prefBool.enabledByDefault);
}

bool ObjectSwitch::isTrue() {
    return Utility::readPref(pref, defaultValueAsString).startsWith("t");
}

void ObjectSwitch::toggle() {
    if (!isTrue()) {
        Utility::writePref(pref, "true");
    } else {
        Utility::writePref(pref, "false");
    }
    RadarPreferences::initialize();
    UIPreferences::initialize();
}

QWidget * ObjectSwitch::get() {
    return checkBox;
}
