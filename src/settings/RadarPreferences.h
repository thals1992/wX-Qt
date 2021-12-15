// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef RADARPREFERENCES_H
#define RADARPREFERENCES_H

#include <QColor>

class RadarPreferences {
public:
    static void initialize();
    static void initializeColors();
    static QColor getInitialPreference(const QString&, int);
    static bool wxoglRememberLocation;
    static bool mcd;
    static bool watch;
    static bool mpd;
    static int dataRefreshInterval;
    static bool swo;
    static bool hw;
    static bool hwEnhExt;
    static bool caBorders;
    static bool mxBorders;
    static bool locDot;
    static bool county;
    static bool lakes;
    static bool cities;
    static bool countyLabels;
    static bool obs;
    static bool spotters;
    static bool spotterLabels;
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
    static double stateLinesize;
    static double countyLinesize;
    static double hwLinesize;
    static double hwExtLinesize;
    static double lakeLinesize;
    static double gpsCircleLinesize;
    static double stiLinesize;
    static double swoLinesize;
    static double wbLinesize;
    // was 10.0 for vala/gtk port
    static double lineFactor;
    static double locdotSize;
    static double aviationSize;
    static QColor colorHw;
    static QColor colorHwExt;
    static QColor colorState;
    static QColor colorTstorm;
    static QColor colorTstormWatch;
    static QColor colorTor;
    static QColor colorTorWatch;
    static QColor colorFfw;
    static QColor colorMcd;
    static QColor colorMpd;
    static QColor colorLocdot;
    static QColor colorSpotter;
    static QColor colorCity;
    static QColor colorLakes;
    static QColor colorCounty;
    static QColor colorSti;
    static QColor colorHi;
    static QColor colorObs;
    static QColor colorObsWindbarbs;
    static QColor colorCountyLabels;
};

#endif  // RADARPREFERENCES_H
