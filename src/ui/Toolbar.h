// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTTOOLBAR_H
#define OBJECTTOOLBAR_H

#include <functional>
#include <vector>
#include "ui/ButtonFlat.h"
#include "ui/ComboBox.h"
#include "ui/RouteItem.h"
#include "ui/VBox.h"

using std::function;
using std::vector;

class Toolbar : public VBox {
public:
    Toolbar(QWidget *, const function<void()>&);
    void launchSettings();
    void launchNexrad(int);
    void launchHourly();
    void launchWfoText();
    void launchSpcSwoSummary();
    void launchGoesViewer();
    void launchSpcSwoDay1(const string&);
    void launchNationalText();
    void launchSpcTstormOutlooks();
    void launchSpcCompmap();
    void launchSevereDashboard();
    void launchNhc();
    void launchRadarMosaicViewer();
    void launchLightning();
    void launchObservationSites();
    void launchObservations();
    void launchSpcMeso();
    void launchModelViewer();
    void launchModelViewerGeneric(const string&);
    void launchNationalImages();
    void launchUsAlerts();
    void launchRainfallOutlookSummary();
    void launchSpcFireWeatherOutlookSummary();
    void launchSpcStormReports(const string&);
    void launchOpc();
    void launchRtma();
    void refresh();

private:
    QWidget * parent;
    function<void()> reloadFn;
    vector<RouteItem> routeItems;
    vector<ButtonFlat> buttons;
};

#endif  // OBJECTTOOLBAR_H
