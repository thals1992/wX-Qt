// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/UtilityRadarUI.h"
#include <cmath>
#include <iostream>
#include "misc/AlertsDetail.h"
#include "radar/UtilityWatch.h"
#include "radar/UtilityWXOGL.h"
#include "spc/SpcMcdWatchMpdViewer.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityDownload.h"

void UtilityRadarUI::showPolygonText(QWidget * parent, const LatLon& location) {
    auto url = UtilityWXOGL::showTextProducts(location);
    if (url != "") {
        new AlertsDetail(parent, url);
    }
}

void UtilityRadarUI::showNearestProduct(QWidget * parent, PolygonType type, const LatLon& location) {
    auto txt = UtilityWatch::show(location, type);
    // https://www.spc.noaa.gov/products/md/mcd0922.gif
    // https://www.wpc.ncep.noaa.gov/metwatch/images/mcd0339.gif
    // https://www.spc.noaa.gov/products/watch/ww0283_radar.gif
    QString url;
    if (type == PolygonType::mcd) {
        url = "https://www.spc.noaa.gov/products/md/mcd" + txt + ".gif";
    } else if (type == PolygonType::mpd) {
        url = "https://www.wpc.ncep.noaa.gov/metwatch/images/mcd" + txt + ".gif";
    } else if (type == PolygonType::watch) {
        url = "https://www.spc.noaa.gov/products/watch/ww" + txt + "_radar.gif";
    }
    if (txt != "") {
        SpcMcdWatchMpdViewer * window = new SpcMcdWatchMpdViewer(parent, url);
        window->show();
    }
}

LatLon UtilityRadarUI::getLatLonFromScreenPosition(const NexradState& nexradState, float ortInt, float x, float y) {
    auto width = nexradState.windowWidth;
    auto height = nexradState.windowHeight;
    auto yModified = y;
    auto xModified = x;
    auto density = (ortInt * 2.0) / width;
    auto yMiddle = height / 2.0;
    auto xMiddle = width / 2.0;
    auto diffX = density * (xMiddle - xModified) / nexradState.zoom;
    auto diffY = density * (yMiddle - yModified) / nexradState.zoom;
    auto radarX = To::Double(Utility::getRadarSiteX(nexradState.radarSite));
    auto radarY = To::Double(Utility::getRadarSiteY(nexradState.radarSite));
    auto radarLocation = LatLon(radarX, radarY);
    auto ppd = nexradState.pn.oneDegreeScaleFactor;
    auto newX = radarLocation.lon + (nexradState.xPos / nexradState.zoom + diffX) / ppd;
    auto test2 = 180.0 / M_PI * log(tan(M_PI / 4 + radarLocation.lat * (M_PI / 180) / 2.0));
    auto newY = test2 + (nexradState.yPos / nexradState.zoom + diffY) / ppd;
    newY = (180.0 / M_PI * (2 * atan(exp(newY * M_PI / 180.0)) - M_PI / 2.0));
    return LatLon(newY, -1.0 * newX);
}

QString UtilityRadarUI::getRadarStatusMessage(const QString& radarSite) {
    auto ridSmall = radarSite;
    auto message = UtilityDownload::getRadarStatusMessage(ridSmall.toUpper());
    if (message == "") {
        return "The current radar status for " + radarSite + " is not available.";
    } else {
        return message;
    }
}
