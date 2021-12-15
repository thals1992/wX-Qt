// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTTOOLBAR_H
#define OBJECTTOOLBAR_H

#include <functional>
#include "ui/ButtonFlat.h"
#include "ui/ComboBox.h"
#include "ui/RouteItem.h"
#include "ui/VBox.h"

class ObjectToolbar : public VBox {
public:
    ObjectToolbar();
    explicit ObjectToolbar(QWidget *, std::function<void()>, ComboBox *);
    void launchSettings();
    void launchNexrad(int);
    void launchHourly();
    void launchWfoText();
    void launchSpcSwoSummary();
    void launchGoesViewer();
    void launchSpcSwoDay1(const QString&);
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
    void launchModelViewerGeneric(const QString&);
    void launchNationalImages();
    void launchUsAlerts();
    void launchRainfallOutlookSummary();
    void launchSpcFireWeatherOutlookSummary();
    void launchSpcStormReports(const QString&);
    void launchOpc();

private:
    QWidget * parent;
    ComboBox * comboBox;
    std::function<void()> reloadFn;
    QVector<RouteItem> routeItems;
    QVector<ButtonFlat> buttons;
};

#endif  // OBJECTTOOLBAR_H
