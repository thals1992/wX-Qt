// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ObjectCardLocationItem.h"
#include "settings/Location.h"
#include "util/UtilityTimeSunMoon.h"

ObjectCardLocationItem::ObjectCardLocationItem() {
}

ObjectCardLocationItem::ObjectCardLocationItem(QWidget * parent, int index) : VBox(parent) {
    hbox = HBox(parent);
    text1 = Text(parent);
    text2 = Text(parent);
    text3 = Text(parent);
    text4 = Text(parent);

    text1.setText(Location::getName(index));
    text1.setBlue();
    text1.setBold();

    const auto latLon = Location::getLatLon(index);
    text2.setText(latLon.printSpaceSeparated());
    text3.setText(Location::getWfo(index) + ", " + Location::getRadarSite(index));
    text4.setText(UtilityTimeSunMoon::getSunTimes(latLon));
    text4.setWrap(false);

    hbox.addWidget(text1.get());
    hbox.addWidget(text2.get());
    hbox.addWidget(text3.get());
    hbox.addWidget(text4.get());
    addLayout(hbox.get());
}
