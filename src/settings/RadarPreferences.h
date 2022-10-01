// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef RADARPREFERENCES_H
#define RADARPREFERENCES_H

#include <string>
#include <QColor>

using std::string;

class RadarPreferences {
public:
    static void initialize();
    static void initializeColors();
    static QColor getInitialPreference(const string&, int);
    static bool rememberLocation;
    static int dataRefreshInterval;
    static bool swo;
    static bool locationDot;
    static bool locdotFollowsGps;
    static bool cities;
    static bool countyLabels;
    static bool obs;
    static bool obsWindbarbs;
    static bool sti;
    static bool hi;
    static bool tvs;
    static bool showWpcFronts;
    static bool dualpaneshareposn;
    static bool radarShowControls;
    static bool radarShowStatusBar;
    static bool colorLegend;
    static int radarTextSize;
    static double warnLinesize;
    static double watmcdLinesize;
//    static double gpsCircleLinesize;
    static double stiLinesize;
    static double swoLinesize;
    static double wbLinesize;
    // was 10.0 for vala/gtk port
    static double lineFactor;
    static double locdotSize;
    static double aviationSize;
    static QColor colorLocdot;
    static QColor colorCity;
    static QColor colorSti;
    static QColor colorHi;
    static QColor colorObs;
    static QColor colorObsWindbarbs;
    static QColor colorCountyLabels;
    static QColor nexradRadarBackgroundColor;
};

#endif  // RADARPREFERENCES_H
