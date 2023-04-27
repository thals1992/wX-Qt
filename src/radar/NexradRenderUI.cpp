// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/NexradRenderUI.h"
#include <QMessageBox>
#include <cmath>
#include <numbers>
#include <string>
#include "objects/WString.h"
#include "misc/AlertsDetail.h"
#include "radar/Watch.h"
#include "radar/Warnings.h"
#include "spc/SpcMcdWatchMpdViewer.h"
#include "ui/LongPressMenu.h"
#include "util/DownloadText.h"
#include "misc/TextViewerStatic.h"

void NexradRenderUI::showPolygonText(QWidget * parent, const LatLon& location) {
    const auto url = Warnings::show(location);
    if (!url.empty()) {
        new AlertsDetail{parent, url};
    }
}

void NexradRenderUI::showNearestProduct(QWidget * parent, PolygonType type, const LatLon& location) {
    const auto txt = Watch::show(location, type);
    // https://www.spc.noaa.gov/products/md/mcd0922.gif
    // https://www.wpc.ncep.noaa.gov/metwatch/images/mcd0339.gif
    // https://www.spc.noaa.gov/products/watch/ww0283_radar.gif
    string url;
    if (type == Mcd) {
        url = "https://www.spc.noaa.gov/products/md/mcd" + txt + ".png";
    } else if (type == Mpd) {
        url = "https://www.wpc.ncep.noaa.gov/metwatch/images/mcd" + txt + ".gif";
    } else if (type == Watch) {
        url = "https://www.spc.noaa.gov/products/watch/ww" + txt + "_radar.gif";
    }
    if (!txt.empty()) {
        new SpcMcdWatchMpdViewer{parent, url};
    }
}

LatLon NexradRenderUI::getLatLonFromScreenPosition(const NexradState& nexradState, double x, double y) {
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

void NexradRenderUI::showRadarStatusMessage(QWidget * parent, const string& radarSite) {
    auto message = DownloadText::getRadarStatusMessage(WString::toUpper(radarSite));
    if (message.empty()) {
        message = "The current radar status for " + radarSite + " is not available.";
    }
    new TextViewerStatic{parent, message};
}
