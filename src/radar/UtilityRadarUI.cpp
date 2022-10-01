// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/UtilityRadarUI.h"
#include <QMessageBox>
#include <cmath>
#include <iostream>
#include <numbers>
#include <string>
#include "common/GlobalArrays.h"
#include "common/GlobalVariables.h"
#include "objects/WString.h"
#include "misc/AlertsDetail.h"
#include "misc/TextViewer.h"
#include "radar/UtilityMetar.h"
#include "radar/UtilityWatch.h"
#include "radar/WXGLNexrad.h"
#include "radar/WXGLPolygonWarnings.h"
#include "settings/Location.h"
#include "settings/UtilityLocation.h"
#include "spc/SpcMcdWatchMpdViewer.h"
#include "ui/CMenuItem.h"
#include "ui/LongPressMenu.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityDownload.h"
#include "util/UtilityList.h"
#include "misc/TextViewerStatic.h"

void UtilityRadarUI::setupContextMenu(
    QWidget * parent,
    const QPoint& posGlobal,
    const NexradState& nexradState,
    const LatLon& latLon,
    const function<void(int, string)>& fnSector,
    const function<void(int, string)>& fnProduct
) {
    // const auto latLon = getLatLonFromScreenPosition(nexradState, positionRelative.x(), positionRelative.y());
    const auto obsSite = UtilityMetar::findClosestObservation(latLon);
    const auto radarSites = UtilityLocation::getNearestRadarSites(latLon, 5, true);
    const auto actionObservation = CMenuItem{"Show Nearest Observation: " + obsSite.name + " (" + To::string(static_cast<int>(round(obsSite.distance))) + " mi)", [parent, obsSite] {
        const auto url = GlobalVariables::tgftpSitePrefix + "/data/observations/metar/decoded/" + obsSite.name + ".TXT";
        new TextViewer{parent, url, 600, 400};
    }};
    const auto actionPosition = CMenuItem{latLon.latStr() + ", " + latLon.lonStr(), [] {}};
    const auto actionSaveLocation = CMenuItem{"Save as a location: " + latLon.printPretty(), [latLon] {
        Location::save(latLon, latLon.printPretty());
        Location::setMainScreenComboBox();
    }};
    const auto actionWarnings = CMenuItem{"Show Warning", [parent, latLon] { showPolygonText(parent, latLon); }};
    const auto actionWatch = CMenuItem{"Show Watch", [parent, latLon] { showNearestProduct(parent, Watch, latLon); }};
    const auto actionMcd = CMenuItem{"Show MCD", [parent, latLon] { showNearestProduct(parent, Mcd, latLon); }};
    const auto actionMpd = CMenuItem{"Show MPD", [parent, latLon] { showNearestProduct(parent, Mpd, latLon); }};
    const auto actionRadarStatusMessage = CMenuItem{"Show radar status message", [parent, &nexradState] {
        getRadarStatusMessage(parent, nexradState.getRadarSite());
    }};
    //
    // radar sites
    //
    vector<CMenuItem> actionRadarSitesList;
    for (const auto& rid : radarSites) {
        const auto radarDescription = rid.name + ": " + Utility::getRadarSiteName(rid.name) + " (" + To::string(static_cast<int>(round(rid.distance))) + " mi)";
        actionRadarSitesList.emplace_back(radarDescription, [&rid, &nexradState, &fnSector] { fnSector(nexradState.paneNumber, rid.name); });
    }
    //
    // products
    //
    auto productList = WXGLNexrad::radarProductList;
    if (contains(GlobalArrays::tdwrRadarCodes(), nexradState.getRadarSite())) {
        productList = WXGLNexrad::radarProductListTdwr;
    }
    auto prodLength = 5;
    if (contains(GlobalArrays::tdwrRadarCodes(), nexradState.getRadarSite())) {
        productList = WXGLNexrad::radarProductListTdwr;
        prodLength = 3;
    }
    vector<CMenuItem> productActions;
    for (const auto& product : vector<string>{productList.begin(), productList.begin() + prodLength}) {
        productActions.emplace_back(product, [product, &nexradState, &fnProduct] {
            const auto productShortCode = WString::split(product, ":")[0];
            fnProduct(nexradState.paneNumber, productShortCode);
        });
    }
    //
    // long press
    //
    auto longPressMenu = LongPressMenu{parent};
    longPressMenu.add(actionPosition);
    longPressMenu.add(actionObservation);
    longPressMenu.add(actionSaveLocation);
    for (const auto& action : actionRadarSitesList) {
        longPressMenu.add(action);
    }
    longPressMenu.add(actionWarnings);
    longPressMenu.add(actionWatch);
    longPressMenu.add(actionMcd);
    longPressMenu.add(actionMpd);
    for (const auto& action : productActions) {
        longPressMenu.add(action);
    }
    longPressMenu.add(actionRadarStatusMessage);
    longPressMenu.show(posGlobal);
}

void UtilityRadarUI::showPolygonText(QWidget * parent, const LatLon& location) {
    const auto url = WXGLPolygonWarnings::show(location);
    if (!url.empty()) {
        new AlertsDetail{parent, url};
    }
}

void UtilityRadarUI::showNearestProduct(QWidget * parent, PolygonType type, const LatLon& location) {
    const auto txt = UtilityWatch::show(location, type);
    // https://www.spc.noaa.gov/products/md/mcd0922.gif
    // https://www.wpc.ncep.noaa.gov/metwatch/images/mcd0339.gif
    // https://www.spc.noaa.gov/products/watch/ww0283_radar.gif
    string url;
    if (type == Mcd) {
        url = "https://www.spc.noaa.gov/products/md/mcd" + txt + ".gif";
    } else if (type == Mpd) {
        url = "https://www.wpc.ncep.noaa.gov/metwatch/images/mcd" + txt + ".gif";
    } else if (type == Watch) {
        url = "https://www.spc.noaa.gov/products/watch/ww" + txt + "_radar.gif";
    }
    if (!txt.empty()) {
        new SpcMcdWatchMpdViewer{parent, url};
    }
}

LatLon UtilityRadarUI::getLatLonFromScreenPosition(const NexradState& nexradState, double x, double y) {
    const auto width = static_cast<double>(nexradState.originalWidth);
    const auto height = static_cast<double>(nexradState.originalHeight);
    // std::cout << width << " " << height << std::endl;
    const auto yModified = y;
    const auto xModified = x;
    auto density = 0.52 / nexradState.zoom;
    auto yMiddle = height / 2.0;
    auto xMiddle = width / 2.0;
    if (nexradState.numberOfPanes == 4) {
        yMiddle = height / 4.0;
        xMiddle = width / 4.0;
        density = 1.04 / nexradState.zoom;
    }
    const auto diffX = density * (xMiddle - xModified);
    const auto diffY = density * (yMiddle - yModified);
    const auto ppd = nexradState.getPn().oneDegreeScaleFactor;
    const auto newX = nexradState.getPn().y() + (nexradState.xPos / nexradState.zoom + diffX) / ppd;
    const auto test2 = 180.0 / std::numbers::pi * log(tan(std::numbers::pi / 4.0 + nexradState.getPn().x() * (std::numbers::pi / 180.0) / 2.0));
    auto newY = test2 + (nexradState.yPos / nexradState.zoom + diffY) / ppd;
    newY = (180.0 / std::numbers::pi * (2.0 * atan(exp(newY * std::numbers::pi / 180.0)) - std::numbers::pi / 2.0));
    return {newY, -1.0f * newX};
}

void UtilityRadarUI::getRadarStatusMessage(QWidget * parent, const string& radarSite) {
    auto message = UtilityDownload::getRadarStatusMessage(WString::toUpper(radarSite));
    if (message.empty()) {
        message = "The current radar status for " + radarSite + " is not available.";
    }
    new TextViewerStatic{parent, message};
}
