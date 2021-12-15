// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef LOCATION_H
#define LOCATION_H

#include "objects/LatLon.h"
#include "settings/ObjectLocation.h"

class Location {
public:
    static int currentLocationIndex;
    static int numberOfLocations;
    static int getNumLocations();
    static QString radar();
    // used in gtk
    static QString radarSite();
    static QString wfo();
    static QString office();
    static QString getRadarSite(int);
    static QString getWfo(int);
    static LatLon getLatLon(int);
    static float x();
    static float getX(int);
    static float y();
    static QString name();
    static QString locationName();
    static QString getName(int);
    static float getY(int);
    static LatLon getLatLonCurrent();
    static LatLon getLatLonCurrentByString();
    static void refreshLocationData();
    static void initNumLocations();
    static QStringList getWfoRadarSiteFromPoint(const LatLon&);
    static QStringList save(LatLon, const QString&);
    static void deleteItem(int);
    static void setCurrentLocationStr(const QString&);
    static QStringList listOfNames();
    static void changeLocationByIndex(int);
    static QVector<LatLon> getListLatLons();
    static QString getObs();
    static int getCurrentLocation();

private:
    static QVector<ObjectLocation> locations;
};

#endif  // LOCATION_H
