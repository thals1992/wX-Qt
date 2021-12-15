// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/DataStorage.h"
#include "util/Utility.h"

DataStorage::DataStorage() {
    preference = "";
    val = "";
}

DataStorage::DataStorage(const QString& pref) {
    preference = pref;
    val = "";
}

void DataStorage::update() {
    val = Utility::readPref(preference, "");
}

QString DataStorage::getValue() const {
    return val;
}

void DataStorage::setValue(const QString& newValue) {
    val = newValue;
    Utility::writePref(preference, newValue);
}
