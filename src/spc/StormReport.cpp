// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/StormReport.h"

StormReport::StormReport() {
}

StormReport::StormReport(
    const QString& text,
    const QString& lat,
    const QString& lon,
    const QString& time,
    const QString& magnitude,
    const QString& address,
    const QString& city,
    const QString& state,
    const QString& damageReport,
    const QString& damageHeader
) {
    this->text = text;
    this->lat = lat;
    this->lon = lon;
    this->time = time;
    this->magnitude = magnitude;
    this->address = address;
    this->city = city;
    this->state = state;
    this->damageReport = damageReport;
    this->damageHeader = damageHeader;
}
