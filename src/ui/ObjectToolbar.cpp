// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ObjectToolbar.h"
#include <string>
#include <vector>
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
#include "radar/RadarMosaicNws.h"
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

using std::string;
using std::vector;

ObjectToolbar::ObjectToolbar(QWidget * parent, const function<void()>& reloadFn)
    : VBox{}
    , parent{ parent }
    , reloadFn{ reloadFn }
{
    routeItems.emplace_back("reload.png", "Reload data, Ctrl-u", [reloadFn] { reloadFn(); });
    routeItems.emplace_back("baseline_settings_black_48dp.png", "Settings", [this] { launchSettings(); });

    routeItems.emplace_back("baseline_warning_black_48dp.png", "Severe Dashboard, Ctrl-d", [this] { launchSevereDashboard(); });
    routeItems.emplace_back("baseline_cloud_black_48dp.png", "GOES imagery, Ctrl-c", [this] { launchGoesViewer(); });
    routeItems.emplace_back("baseline_date_range_black_48dp.png", "Hourly Forecast, Ctrl-h", [this] { launchHourly(); });
    routeItems.emplace_back("baseline_info_black_48dp.png", "WFO Text products, Ctrl-a", [this] { launchWfoText(); });

    routeItems.emplace_back("baseline_flash_on_black_48dp.png", "Nexrad radar viewer, Ctrl-r", [this] { launchNexrad(1); });
    routeItems.emplace_back("wxogldualpane.png", "Nexrad radar viewer, dual pane, Ctrl-2", [this] { launchNexrad(2); });
    routeItems.emplace_back("wxoglquadpane.png", "Nexrad radar viewer, quad pane, Ctrl-4", [this] { launchNexrad(4); });

    routeItems.emplace_back("spc_sum.png", "SPC Convective Outlook Summary, Ctrl-s", [this] { launchSpcSwoSummary(); });
    for (const string day : {"1", "2", "3", "48"}) {
        routeItems.emplace_back("day" + day + ".png", "SPC Convective Outlook Day ", [this, day] { launchSpcSwoDay1(day); });
    }
    routeItems.emplace_back("fmap.png", "National Images, Ctrl-i", [this] { launchNationalImages(); });
    routeItems.emplace_back("meso.png", "SPC Mesoanalysis, Ctrl-z", [this] { launchSpcMeso(); });
    routeItems.emplace_back("nwsobssites.png", "Observation Sites", [this] { launchObservationSites(); });
    routeItems.emplace_back("nwsobs.png", "Observations", [this] { launchObservations(); });

    routeItems.emplace_back("radarmosaicnws.png", "Radar Mosaic", [this] { launchRadarMosaicViewer(); });
    routeItems.emplace_back("srfd.png", "National Text", [this] { launchNationalText(); });
    routeItems.emplace_back("uswarn.png", "US Alerts", [this] { launchUsAlerts(); });
    routeItems.emplace_back("wpc_rainfall.png", "WPC Rainfall Outlook Summary", [this] { launchRainfallOutlookSummary(); });
    routeItems.emplace_back("spccompmap.png", "SPC Compmap", [this] { launchSpcCompmap(); });
    routeItems.emplace_back("tstorm.png", "SPC Thunderstorm Outlooks", [this] { launchSpcTstormOutlooks(); });

    routeItems.emplace_back("lightning.png", "Lightning, Ctrl-l", [this] { launchLightning(); });
    routeItems.emplace_back("fire_outlook.png", "SPC Fire Weather Outlooks, Ctrl-f", [this] { launchSpcFireWeatherOutlookSummary(); });
    routeItems.emplace_back("report_today.png", "SPC Storm Reports - today", [this] { launchSpcStormReports("today"); });
    routeItems.emplace_back("report_yesterday.png", "SPC Storm Reports - yesterday", [this] { launchSpcStormReports("yesterday"); });
    routeItems.emplace_back("nhc.png", "NHC product viewer, Ctrl-o", [this] { launchNhc(); });

    routeItems.emplace_back("ncep.png", "NCEP Models, Ctrl-m", [this] { launchModelViewer(); });
    routeItems.emplace_back("spchrrr.png", "SPC HRRR", [this] { launchModelViewerGeneric("SPCHRRR"); });
    routeItems.emplace_back("spcsref.png", "SPC SREF", [this] { launchModelViewerGeneric("SPCSREF"); });
    routeItems.emplace_back("hrrrviewer.png", "ESRL HRRR/RAP", [this] { launchModelViewerGeneric("ESRL"); });
    routeItems.emplace_back("glcfs.png", "GLCFS", [this] { launchModelViewerGeneric("GLCFS"); });
    routeItems.emplace_back("opc.png", "Ocean Prediction Center", [this] { launchOpc(); });
    routeItems.emplace_back("nsslwrf.png", "NSSL WRF", [this] { launchModelViewerGeneric("NSSLWRF"); });
    routeItems.emplace_back("wpcgefs.png", "WPC GEFS", [this] { launchModelViewerGeneric("WPCGEFS"); });
    routeItems.emplace_back("spchref.png", "SPC HREF", [this] { launchModelViewerGeneric("SPCHREF"); });

    for (const auto& item : routeItems) {
        buttons.emplace_back(item.iconString, item.toolTip, parent);
        buttons.back().connect(item.fn);
        addWidget(buttons.back().get());
    }
    addStretch();
}

void ObjectToolbar::launchNexrad(int numberOfPanes) {
    new Nexrad{parent, numberOfPanes, false, ""};
}

void ObjectToolbar::launchHourly() {
    new Hourly{parent};
}

void ObjectToolbar::launchWfoText() {
    new WfoText{parent};
}

void ObjectToolbar::launchSpcSwoSummary() {
    new SpcSwoSummary{parent};
}

void ObjectToolbar::launchSpcSwoDay1(const string& day) {
    new SpcSwoDay1{parent, day};
}

void ObjectToolbar::launchGoesViewer() {
    new GoesViewer{parent, ""};
}

void ObjectToolbar::launchNationalText() {
    new NationalText{parent, ""};
}

void ObjectToolbar::launchSpcTstormOutlooks() {
    new SpcTstormOutlooks{parent};
}

void ObjectToolbar::launchSpcCompmap() {
    new SpcCompMap{parent};
}

void ObjectToolbar::launchSevereDashboard() {
    new SevereDashboard{parent};
}

void ObjectToolbar::launchNhc() {
    new Nhc{parent};
}

void ObjectToolbar::launchRadarMosaicViewer() {
    new RadarMosaicNws{parent};
}

void ObjectToolbar::launchLightning() {
    new GoesViewer{parent, "", "GLM", "CONUS"};
}

void ObjectToolbar::launchObservationSites() {
    new ObservationSites{parent};
}

void ObjectToolbar::launchObservations() {
    new Observations{parent};
}

void ObjectToolbar::launchSpcMeso() {
    new SpcMeso{parent};
}

void ObjectToolbar::launchModelViewer() {
    new ModelViewer{parent, "NCEP"};
}

void ObjectToolbar::launchModelViewerGeneric(const string& modelType) {
    new ModelViewer{parent, modelType};
}

void ObjectToolbar::launchNationalImages() {
    new NationalImages{parent};
}

void ObjectToolbar::launchUsAlerts() {
    new UsAlerts{parent};
}

void ObjectToolbar::launchRainfallOutlookSummary() {
    new RainfallOutlookSummary{parent};
}

void ObjectToolbar::launchSpcFireWeatherOutlookSummary() {
    new SpcFireSummary{parent};
}

void ObjectToolbar::launchSpcStormReports(const string& day) {
    new SpcStormReports{parent, day};
}

void ObjectToolbar::launchOpc() {
    new Opc{parent};
}

void ObjectToolbar::launchSettings() {
    new SettingsMain{parent, reloadFn, true, false};
}

void ObjectToolbar::refresh() {
    if (UIPreferences::toolbarIconSize != ButtonFlat::iconSize) {
        for (auto& button : buttons) {
            button.refresh();
        }
    }
}
