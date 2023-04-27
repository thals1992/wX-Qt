// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef NEXRADSTATE_H
#define NEXRADSTATE_H

#include <string>
#include <vector>
#include <QWidget>
#include "radar/ProjectionNumbers.h"
#include "radar/NexradLevelData.h"
#include "ui/RadarStatusBox.h"
#include "ui/TextViewMetal.h"

using std::string;
using std::vector;

class NexradState {
public:
    NexradState(QWidget *, int, int, bool, const string&, int, int);
    void reset();
    void resetZoom();
    ProjectionNumbers getPn() const;
    string getRadarSite() const;
    string getRadarProduct() const;
    void setRadar(const string&);
    void readPreferences();
    void writePreferences();
    void processAnimationFiles(int, FileStorage *);
    int paneNumber{};
    int numberOfPanes{1};
    bool useASpecificRadar;
    std::unique_ptr<RadarStatusBox> radarStatusBox;
    double xPos{};
    double yPos{};
    double zoom{1.0};
    int tiltInt{};
    vector<TextViewMetal> cities;
    vector<TextViewMetal> countyLabels;
    vector<TextViewMetal> pressureCenterLabelsRed;
    vector<TextViewMetal> pressureCenterLabelsBlue;
    vector<TextViewMetal> observations;
    vector<string> initialRadarProducts{"N0Q", "N0U", "EET", "DVL"};
    double zoomToHideMiscFeatures{0.2};
    vector<NexradLevelData> levelDataList;

private:
    ProjectionNumbers pn;
    string radarSite;
    const string radarType{"WXMETAL"};
public: // TODO FIXME
    int originalWidth{};
    int originalHeight{};
    string radarProduct{"N0Q"};
};

#endif  // NEXRADSTATE_H
