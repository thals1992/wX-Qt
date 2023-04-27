// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/CardLocationItem.h"
#include "settings/Location.h"
#include "util/UtilityTimeSunMoon.h"

CardLocationItem::CardLocationItem(QWidget * parent, int index)
    : text1{ Text{parent} }
    , text2{ Text{parent} }
{
    const auto latLon = Location::getLatLon(index);

    text1.setText(Location::getName(index) + " (" + latLon.printSpaceSeparated() + ")");
    text1.setWordWrap(false);
    text1.setBlue();
    text1.setBold();
    text2.setText(Location::getWfo(index) + ", " + Location::getRadarSite(index) + " " + UtilityTimeSunMoon::getSunTimes(latLon));
    text2.setWordWrap(false);

    box.addWidget(text1);
    box.addWidget(text2);
    addLayout(box);
}
