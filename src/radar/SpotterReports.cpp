// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/SpotterReports.h"

SpotterReports::SpotterReports() {
}

SpotterReports::SpotterReports(
    const QString& firstName,
    const QString& lastName,
    const LatLon& location,
    const QString& narrative,
    const QString& uniq,
    const QString& reportType,
    const QString& time,
    const QString& city
) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->lastName = this->lastName.replace("^ ", "");
    this->location = location;
    this->narrative = narrative;
    this->uniq = uniq;
    this->reportType = reportType;
    this->time = time;
    this->city = city;
}
