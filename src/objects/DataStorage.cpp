// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/DataStorage.h"
#include "util/Utility.h"

DataStorage::DataStorage() = default;

DataStorage::DataStorage(const string& preference)
    : preference{ preference }
{}

void DataStorage::update() {
    value = Utility::readPref(preference, "");
}

string DataStorage::getValue() const {
    return value;
}

void DataStorage::setValue(const string& newValue) {
    value = newValue;
    Utility::writePref(preference, newValue);
}
