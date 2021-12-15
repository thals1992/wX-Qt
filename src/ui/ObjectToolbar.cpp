// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ObjectToolbar.h"
#include "misc/Hourly.h"
#include "misc/ObservationSites.h"
#include "misc/Observations.h"
#include "misc/Opc.h"
#include "misc/SevereDashboard.h"
#include "misc/UsAlerts.h"
#include "misc/WfoText.h"
#include "models/ModelViewer.h"
#include "nhc/Nhc.h"
#include "radar/Nexrad.h"
#include "radar/RadarMosaicAwc.h"
#include "settings/SettingsMain.h"
#include "settings/UIPreferences.h"
#include "spc/SpcCompMap.h"
#include "spc/SpcFireSummary.h"
#include "spc/SpcMeso.h"
#include "spc/SpcStormReports.h"
#include "spc/SpcSwoDay1.h"
#include "spc/SpcSwoSummary.h"
#include "spc/SpcTstormOutlooks.h"
#include "vis/GoesViewer.h"
#include "wpc/NationalImages.h"
#include "wpc/NationalText.h"
#include "wpc/RainfallOutlookSummary.h"

ObjectToolbar::ObjectToolbar() {
}

ObjectToolbar::ObjectToolbar(QWidget * parent, std::function<void()> reloadFn, ComboBox * comboBox) : VBox(parent) {
    this->parent = parent;
    this->comboBox = comboBox;
    this->reloadFn = reloadFn;
    routeItems.push_back(RouteItem("reload.png", "Reload data, Ctrl-u", [reloadFn] { reloadFn(); }));
    routeItems.push_back(RouteItem("baseline_settings_black_48dp.png", "Settings", [this] { launchSettings(); }));
    routeItems.push_back(RouteItem("baseline_flash_on_black_48dp.png", "Nexrad radar viewer, Ctrl-r", [this] { launchNexrad(1); }));
    routeItems.push_back(RouteItem("wxogldualpane.png", "Nexrad radar viewer, dual pane, Ctrl-2", [this] { launchNexrad(2); }));
    routeItems.push_back(RouteItem("wxoglquadpane.png", "Nexrad radar viewer, quad pane, Ctrl-4", [this] { launchNexrad(4); }));
    routeItems.push_back(RouteItem("baseline_warning_black_48dp.png", "Severe Dashboard, Ctrl-d", [this] { launchSevereDashboard(); }));
    routeItems.push_back(RouteItem("baseline_cloud_black_48dp.png", "GOES imagery, Ctrl-c", [this] { launchGoesViewer(); }));
    routeItems.push_back(RouteItem("baseline_date_range_black_48dp.png", "Hourly Forecast, Ctrl-h", [this] { launchHourly(); }));
    routeItems.push_back(RouteItem("baseline_info_black_48dp.png", "WFO Text products, Ctrl-a", [this] { launchWfoText(); }));
    routeItems.push_back(RouteItem("fmap.png", "National Images, Ctrl-i", [this] { launchNationalImages(); }));
    routeItems.push_back(RouteItem("meso.png", "SPC Mesoanalysis, Ctrl-z", [this] { launchSpcMeso(); }));
    routeItems.push_back(RouteItem("spc_sum.png", "SPC Convective Outlook Summary, Ctrl-s", [this] { launchSpcSwoSummary(); }));
    for (const auto& day : QStringList({"1", "2", "3", "48"})) {
        routeItems.push_back(RouteItem("day" + day + ".png", "SPC Convective Outlook Day ", [this, day] { launchSpcSwoDay1(day); }));
    }
    routeItems.push_back(RouteItem("nhc.png", "NHC product viewer, Ctrl-o", [this] { launchNhc(); }));
    routeItems.push_back(RouteItem("srfd.png", "National Text", [this] { launchNationalText(); }));
    routeItems.push_back(RouteItem("wpc_rainfall.png", "WPC Rainfall Outlook Summary", [this] { launchRainfallOutlookSummary(); }));
    routeItems.push_back(RouteItem("spccompmap.png", "SPC Compmap", [this] { launchSpcCompmap(); }));
    routeItems.push_back(RouteItem("nwsobssites.png", "Observation Sites", [this] { launchObservationSites(); }));
    routeItems.push_back(RouteItem("fire_outlook.png", "SPC Fire Weather Outlooks, Ctrl-f", [this] { launchSpcFireWeatherOutlookSummary(); }));
    routeItems.push_back(RouteItem("tstorm.png", "SPC Thunderstorm Outlooks", [this] { launchSpcTstormOutlooks(); }));
    routeItems.push_back(RouteItem("nwsobs.png", "Observations", [this] { launchObservations(); }));
    routeItems.push_back(RouteItem("lightning.png", "Lightning, Ctrl-l", [this] { launchLightning(); }));
    routeItems.push_back(RouteItem("report_today.png", "SPC Storm Reports - today", [this] { launchSpcStormReports("today"); }));
    routeItems.push_back(RouteItem("report_yesterday.png", "SPC Storm Reports - yesterday", [this] { launchSpcStormReports("yesterday"); }));
    routeItems.push_back(RouteItem("uswarn.png", "US Alerts", [this] { launchUsAlerts(); }));
    routeItems.push_back(RouteItem("nws_sector.png", "AWC Radar Mosaic", [this] { launchRadarMosaicViewer(); }));
    routeItems.push_back(RouteItem("ncep.png", "NCEP Models, Ctrl-m", [this] { launchModelViewer(); }));
    routeItems.push_back(RouteItem("spcsref.png", "SPC SREF", [this] { launchModelViewerGeneric("SPCSREF"); }));
    routeItems.push_back(RouteItem("spchrrr.png", "SPC HRRR", [this] { launchModelViewerGeneric("SPCHRRR"); }));
    routeItems.push_back(RouteItem("spchref.png", "SPC HREF", [this] { launchModelViewerGeneric("SPCHREF"); }));
    routeItems.push_back(RouteItem("nsslwrf.png", "NSSL WRF", [this] { launchModelViewerGeneric("NSSLWRF"); }));
    routeItems.push_back(RouteItem("wpcgefs.png", "WPC GEFS", [this] { launchModelViewerGeneric("WPCGEFS"); }));
    routeItems.push_back(RouteItem("glcfs.png", "GLCFS", [this] { launchModelViewerGeneric("GLCFS"); }));
    routeItems.push_back(RouteItem("hrrrviewer.png", "ESRL HRRR/RAP", [this] { launchModelViewerGeneric("ESRL"); }));
    routeItems.push_back(RouteItem("opc.png", "Ocean Prediction Center", [this] { launchOpc(); }));

    for (auto& item: routeItems) {
        buttons.push_back(ButtonFlat(item.iconString, item.toolTip, parent));
        buttons.back().connect(item.fn);
        addWidget(buttons.back().get());
    }
    addStretch();
}

void ObjectToolbar::launchNexrad(int numberOfPanes) {
    new Nexrad(parent, numberOfPanes, false, "", true);
}

void ObjectToolbar::launchHourly() {
    new Hourly(parent);
}

void ObjectToolbar::launchWfoText() {
    new WfoText(parent);
}

void ObjectToolbar::launchSpcSwoSummary() {
    new SpcSwoSummary(parent);
}

void ObjectToolbar::launchSpcSwoDay1(const QString& day) {
    new SpcSwoDay1(parent, day);
}

void ObjectToolbar::launchGoesViewer() {
    new GoesViewer(parent, "");
}

void ObjectToolbar::launchNationalText() {
    new NationalText(parent);
}

void ObjectToolbar::launchSpcTstormOutlooks() {
    new SpcTstormOutlooks(parent);
}

void ObjectToolbar::launchSpcCompmap() {
    new SpcCompMap(parent);
}

void ObjectToolbar::launchSevereDashboard() {
    new SevereDashboard(parent);
}

void ObjectToolbar::launchNhc() {
    new Nhc(parent);
}

void ObjectToolbar::launchRadarMosaicViewer() {
    new RadarMosaicAwc(parent);
}

void ObjectToolbar::launchLightning() {
    new GoesViewer(parent, "", "GLM", "CONUS");
}

void ObjectToolbar::launchObservationSites() {
    new ObservationSites(parent);
}

void ObjectToolbar::launchObservations() {
    new Observations(parent);
}

void ObjectToolbar::launchSpcMeso() {
    new SpcMeso(parent);
}

void ObjectToolbar::launchModelViewer() {
    new ModelViewer(parent, "NCEP");
}

void ObjectToolbar::launchModelViewerGeneric(const QString& modelType) {
    new ModelViewer(parent, modelType);
}

void ObjectToolbar::launchNationalImages() {
    new NationalImages(parent);
}

void ObjectToolbar::launchUsAlerts() {
    new UsAlerts(parent);
}

void ObjectToolbar::launchRainfallOutlookSummary() {
    new RainfallOutlookSummary(parent);
}

void ObjectToolbar::launchSpcFireWeatherOutlookSummary() {
    new SpcFireSummary(parent);
}

void ObjectToolbar::launchSpcStormReports(const QString& day) {
    new SpcStormReports(parent, day);
}

void ObjectToolbar::launchOpc() {
    new Opc(parent);
}

void ObjectToolbar::launchSettings() {
    new SettingsMain(parent, comboBox, reloadFn, true); 
}
