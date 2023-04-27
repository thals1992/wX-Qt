// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/NexradLongPressMenu.h"
#include <QMessageBox>
#include <cmath>
#include <numbers>
#include <string>
#include "common/GlobalArrays.h"
#include "common/GlobalVariables.h"
#include "objects/LatLon.h"
#include "objects/PolygonWarning.h"
#include "objects/PolygonWatch.h"
#include "objects/WString.h"
#include "misc/AlertsDetail.h"
#include "misc/TextViewer.h"
#include "radar/Metar.h"
#include "radar/NexradUtil.h"
#include "radar/NexradRenderUI.h"
#include "settings/Location.h"
#include "settings/UtilityLocation.h"
#include "spc/SpcMcdWatchMpdViewer.h"
#include "ui/CMenuItem.h"
#include "ui/LongPressMenu.h"
#include "util/To.h"
#include "util/UtilityList.h"

void NexradLongPressMenu::setupContextMenu(
    QWidget * parent,
    const QPoint& posGlobal,
    const NexradState& nexradState,
    const LatLon& latLon,
    const function<void(int, string)>& fnSector,
    const function<void(int, string)>& fnProduct
) {
    const auto distFromLocation = To::string(static_cast<int>(latLon.dist(Location::getLatLonCurrent())));
    const auto obsSite = Metar::findClosestObservation(latLon);
    const auto radarSites = UtilityLocation::getNearestRadarSites(latLon, 5, true);

    const auto actionDistance = CMenuItem{latLon.printPretty() + " " + distFromLocation + " miles from location", [] {}};
    const auto actionObservation = CMenuItem{"Show Nearest Observation: " + obsSite.name + " (" + To::string(static_cast<int>(round(obsSite.distance))) + " mi)", [parent, obsSite] {
        const auto url = GlobalVariables::tgftpSitePrefix + "/data/observations/metar/decoded/" + obsSite.name + ".TXT";
        new TextViewer{parent, url, 600, 400};
    }};
    const auto actionSaveLocation = CMenuItem{"Save as a location: " + latLon.printPretty(), [latLon] {
        Location::save(latLon, latLon.printPretty());
        Location::setMainScreenComboBox();
    }};
    const auto actionWarnings = CMenuItem{"Show Warning", [parent, latLon] { NexradRenderUI::showPolygonText(parent, latLon); }};
    const auto actionWatch = CMenuItem{"Show Watch", [parent, latLon] { NexradRenderUI::showNearestProduct(parent, Watch, latLon); }};
    const auto actionMcd = CMenuItem{"Show MCD", [parent, latLon] { NexradRenderUI::showNearestProduct(parent, Mcd, latLon); }};
    const auto actionMpd = CMenuItem{"Show MPD", [parent, latLon] { NexradRenderUI::showNearestProduct(parent, Mpd, latLon); }};
    const auto closestRadar = radarSites[0].name;
    const auto actionRadarStatusMessage = CMenuItem{"Show radar status message: " + closestRadar, [parent, closestRadar] {
        NexradRenderUI::showRadarStatusMessage(parent, closestRadar);
    }};
    //
    // radar sites
    //
    vector<CMenuItem> actionRadarSitesList;
    for (const auto& rid : radarSites) {
        const auto radarDescription = rid.name + " " + UtilityLocation::getRadarSiteName(rid.name) + " " + To::string(static_cast<int>(round(rid.distance))) + " mi";
        actionRadarSitesList.emplace_back(radarDescription, [&rid, &nexradState, &fnSector] { fnSector(nexradState.paneNumber, rid.name); });
    }
    //
    // products
    //
    auto productList = NexradUtil::radarProductList;
    if (contains(GlobalArrays::tdwrRadarCodes(), nexradState.getRadarSite())) {
        productList = NexradUtil::radarProductListTdwr;
    }
    auto prodLength = 5;
    if (contains(GlobalArrays::tdwrRadarCodes(), nexradState.getRadarSite())) {
        productList = NexradUtil::radarProductListTdwr;
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
    longPressMenu.add(actionDistance);
    longPressMenu.add(actionObservation);
    longPressMenu.add(actionSaveLocation);
    for (const auto& action : actionRadarSitesList) {
        longPressMenu.add(action);
    }
    if (PolygonWarning::areAnyEnabled() && PolygonWarning::isCountNonZero()) {
        longPressMenu.add(actionWarnings);
    }
    if (PolygonWatch::byType[PolygonType::Watch]->isEnabled && (!PolygonWatch::byType[PolygonType::Watch]->latLonList.getValue().empty() || !PolygonWatch::watchLatlonCombined.getValue().empty())) {
        longPressMenu.add(actionWatch);
    }
    if (PolygonWatch::byType[PolygonType::Mcd]->isEnabled && !PolygonWatch::byType[PolygonType::Mcd]->latLonList.getValue().empty()) {
        longPressMenu.add(actionMcd);
    }
    if (PolygonWatch::byType[PolygonType::Mpd]->isEnabled && !PolygonWatch::byType[PolygonType::Mpd]->latLonList.getValue().empty()) {
        longPressMenu.add(actionMpd);
    }
    for (const auto& action : productActions) {
        longPressMenu.add(action);
    }
    for (const auto& action : productActions) {
        longPressMenu.add(action);
    }
    longPressMenu.add(actionRadarStatusMessage);
    longPressMenu.show(posGlobal);
}
