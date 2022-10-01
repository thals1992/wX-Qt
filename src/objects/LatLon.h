// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef LATLON_H
#define LATLON_H

#include <string>
#include <vector>
#include <string>
#include "external/ExternalPoint.h"
#include "radar/ProjectionNumbers.h"

using std::string;
using std::vector;

class LatLon {
public:
    LatLon();
    LatLon(double, double);
    LatLon(const string&, const string&);
    explicit LatLon(const vector<float>&);
    explicit LatLon(const string&);
    double lat() const;
    double lon() const;
    string latStr() const;
    string lonStr() const;
    void setLonStr(const string&);
    double dist(const LatLon&) const;
    string printSpaceSeparated() const;
    vector<double> getProjection(const ProjectionNumbers&) const;
    ExternalPoint asPoint() const;
    vector<double> asList() const;
    string latForNws() const;
    string lonForNws() const;
    string printPretty() const;
    static LatLon fromList(vector<double>);
    static LatLon fromRadarSite(const string&);
    static string storeWatchMcdLatLon(const string&);
    static LatLon getLatLonFromString(const string&);
    static string getLatLon(const string&);
    static vector<double> latLonListToListOfDoubles(const vector<LatLon>&, const ProjectionNumbers&);
    static vector<LatLon> parseStringToLatLons(const string&, int = 1, bool = true);
    static vector<LatLon> parseStringToLatLonsForMcdLongPress(const string&, int = 1, bool = true);
    static string getWatchLatLon(const string&);

private:
    static string parseNwsPreSecondMatch(const string&);
    string latString;
    string lonString;
    double latNum;
    double lonNum;
};

#endif  // LATLON_H
