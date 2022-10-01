// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <vector>
#include "objects/LatLon.h"
#include "settings/ObjectLocation.h"
#include "ui/ComboBox.h"

using std::string;
using std::vector;

class Location {
public:
    static int currentLocationIndex;
    static int numberOfLocations;
    static int getNumLocations();
    static string radar();
    // used in gtk
    static string radarSite();
    static string wfo();
    static string office();
    static string getRadarSite(int);
    static string getWfo(int);
    static LatLon getLatLon(int);
    static string name();
    static string locationName();
    static string getName(int);
    static LatLon getLatLonCurrent();
    static void refreshLocationData();
    static void initNumLocations();
    static vector<string> getWfoRadarSiteFromPoint(const LatLon&);
    static vector<string> save(const LatLon&, const string&);
    static void deleteItem(int);
    static void setCurrentLocationStr(const string&);
    static vector<string> listOfNames();
    static void setCurrentLocation(int);
    static vector<LatLon> getListLatLons();
    static string getObs();
    static int getCurrentLocation();
    static void setMainScreenComboBox();
    static ComboBox * comboBox;

private:
    static vector<ObjectLocation> locations;
};

#endif  // LOCATION_H
