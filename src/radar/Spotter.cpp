// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/Spotter.h"
#include "util/UtilityString.h"

Spotter::Spotter() {
}

Spotter::Spotter(
    const QString& firstName,
    const QString& lastName,
    const LatLon& location,
    const QString& reportedAt,
    const QString& email,
    const QString& phone,
    const QString& uniq
) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->lastName = this->lastName.replace("^ ", "");
    this->lastName = UtilityString::toCamelCase(this->lastName);
    this->location = location;
    this->reportedAt = reportedAt;
    this->email = email;
    this->phone = phone;
    this->uniq = uniq;
}
