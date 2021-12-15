// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef NEXRADSTATE_H
#define NEXRADSTATE_H

#include <QStringList>
#include <QVector>
#include "ui/TextViewMetal.h"
#include "util/ProjectionNumbers.h"

class NexradState {
public:
    NexradState();
    NexradState(int, int, bool);
    void reset();
    void readPreferences();
    void writePreferences();
    int paneNumber = 0;
    int numberOfPanes = 1;
    bool useASpecificRadar;
    double xPos = 0.0;
    double yPos = 0.0;
    double zoom = 1.0;
    QString radarSite = "KDTX";
    QString radarProduct = "N0Q";
    int tiltInt = 0;
    int windowHeight;
    int windowWidth;
    ProjectionNumbers pn;
    QVector<TextViewMetal> cities;
    QVector<TextViewMetal> countyLabels;
    QVector<TextViewMetal> pressureCenterLabelsRed;
    QVector<TextViewMetal> pressureCenterLabelsBlue;
    QVector<TextViewMetal> observations;
    QVector<TextViewMetal> spotterLabels;
    QStringList initialRadarProducts = {"N0Q", "N0U", "EET", "DVL"};
    double zoomToHideMiscFeatures = 0.2;
};

#endif  // NEXRADSTATE_H
