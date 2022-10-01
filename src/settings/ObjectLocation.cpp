// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/ObjectLocation.h"
#include "util/To.h"
#include "util/Utility.h"

ObjectLocation::ObjectLocation() = default;

ObjectLocation::ObjectLocation(int locationNumber)
    : locNumAsString{ To::string(locationNumber + 1) }
    , lat{ Utility::readPref("LOC" + locNumAsString + "_X", "") }
    , lon{ Utility::readPref("LOC" + locNumAsString + "_Y", "") }
    , name{ Utility::readPref("LOC" + locNumAsString + "_LABEL", "") }
    , wfo{ Utility::readPref("NWS" + locNumAsString, "") }
    , rid{ Utility::readPref("RID" + locNumAsString, "") }
{}

void ObjectLocation::saveToNewSlot(int newLocNumInt) {
    locNumAsString = To::string(newLocNumInt + 1);
    Utility::writePref("LOC" + locNumAsString + "_X", lat);
    Utility::writePref("LOC" + locNumAsString + "_Y", lon);
    Utility::writePref("LOC" + locNumAsString + "_LABEL", name);
    Utility::writePref("NWS" + locNumAsString, wfo);
    Utility::writePref("RID" + locNumAsString, rid);
}

string ObjectLocation::getLat() const {
    return lat;
}

string ObjectLocation::getLon() const {
    return lon;
}

LatLon ObjectLocation::getLatLon() const {
    return {getLat(), getLon()};
}

string ObjectLocation::getName() const {
    return name;
}

string ObjectLocation::getWfo() const {
    return wfo;
}

string ObjectLocation::getRadarSite() const {
    return rid;
}
