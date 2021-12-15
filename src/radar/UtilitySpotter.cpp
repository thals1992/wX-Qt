// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/UtilitySpotter.h"
#include <QStringList>
#include "common/GlobalVariables.h"
#include "objects/LatLon.h"
#include "util/To.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"

QVector<Spotter> UtilitySpotter::spotterList;
QVector<SpotterReports> UtilitySpotter::reportsList;
DownloadTimer UtilitySpotter::timer = DownloadTimer("SPOTTER");
QVector<float> UtilitySpotter::lat;
QVector<float> UtilitySpotter::lon;

QVector<Spotter> UtilitySpotter::get() {
    if (timer.isRefreshNeeded()) {
        spotterList.clear();
        reportsList.clear();
        QStringList latitudeList;
        QStringList longitudeList;
        auto html = UtilityIO::getHtml("https://www.spotternetwork.org/feeds/csv.txt");
        auto reportData = html.replace(".*?//storm reports", "");
        processReports(reportData);
        html = html.replace("//storm reports.*?$", "");
        auto lines = html.split(GlobalVariables::newline);
        for (const auto& line : lines) {
            auto items = line.split(";;");
            if (items.size() > 15) {
                spotterList.push_back(Spotter(items[14], items[15], LatLon(items[4], items[5]), items[3], items[11], items[10], items[0]));
                latitudeList.push_back(items[4]);
                longitudeList.push_back(items[5]);
            }
        }
        if (latitudeList.size() == longitudeList.size()) {
            lat.clear();
            lon.clear();
            for (auto index : UtilityList::range(latitudeList.size())) {
                lat.push_back(To::Float(latitudeList[index]));
                lon.push_back(-1.0 * To::Float(longitudeList[index]));
            }
        } else {
            lat.clear();
            lon.clear();
            lat.push_back(0.0f);
            lon.push_back(0.0f);
        }
    }
    return spotterList;
}

void UtilitySpotter::processReports(const QString& html) {
    auto lines = html.split(GlobalVariables::newline);
    for (const auto& line : lines) {
        auto items = line.split(";;");
        if (items.size() > 10 && items.size() < 16 && !items[0].startsWith("//")) {
            reportsList.push_back(SpotterReports(items[9], items[10], LatLon(items[5], items[6]), items[8], items[0], items[3], items[2], items[7]));
        }
    }
}
