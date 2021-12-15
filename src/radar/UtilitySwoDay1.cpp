// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/UtilitySwoDay1.h"
#include <iostream>
#include "common/GlobalVariables.h"
#include "objects/LatLon.h"
#include "util/To.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"

DownloadTimer UtilitySwoDay1::timer = DownloadTimer("SWO");
QHash<int, QVector<float>> UtilitySwoDay1::hashSwo;
QVector<QColor> UtilitySwoDay1::swoPaints;
QStringList UtilitySwoDay1::threatList;

void UtilitySwoDay1::get() {
    swoPaints.push_back(QColor(255, 0, 255)); // HIGH
    swoPaints.push_back(QColor(255, 0, 0));   // MDT
    swoPaints.push_back(QColor(255, 140, 0)); // ENH
    swoPaints.push_back(QColor(255, 255, 0)); // SLGT
    swoPaints.push_back(QColor(0, 100, 0));   // MGRL
    if (timer.isRefreshNeeded()) {
        threatList.clear();
        threatList.push_back("HIGH");
        threatList.push_back("MDT");
        threatList.push_back("ENH");
        threatList.push_back("SLGT");
        threatList.push_back("MRGL");
        auto day = 1;
        auto html = UtilityIO::getHtml(GlobalVariables::nwsSPCwebsitePrefix + "/products/outlook/KWNSPTSDY" + To::String(day) + ".txt");
        auto htmlBlob = UtilityString::parse(html, "... CATEGORICAL ...(.*?&)&").replace("   ", " ").replace("  ", " ");
        htmlBlob = htmlBlob.replace("   ", " ");
        htmlBlob = htmlBlob.replace("  ", " ");
        for (auto m : UtilityList::range(threatList.size())) {
            QString data = "";
            auto threatLevelCode = threatList[m];
            auto htmlList = UtilityString::parseColumn(htmlBlob, threatLevelCode.mid(1) + " (.*?)[A-Z&]");
            QVector<float> warningList;
            for (const auto& polygon : htmlList) {
                auto coordinates = UtilityString::parseColumn(polygon, "([0-9]{8}).*?");
                for (const auto& coord : coordinates) {
                    data += LatLon(coord).printSpaceSeparated();
                }
                data += ":";
                data = data.replace(" :", ":");
            }
            auto polygons = data.split(":");
            //
            // for each polygon parse apart the numbers and then add even numbers to one list and odd numbers to the other list
            // from there transform into the normal dataset needed for drawing lines in the graphic renderer
            //
            if (polygons.size() > 1) {
                for (const auto& polygon : polygons) {
                    if (polygon != "") {
                        auto numbers = polygon.split(" ");
                        QVector<float> x;
                        QVector<float> y;
                        for (auto index : UtilityList::range(numbers.size())) {
                            if (index % 2 == 0) {
                                x.push_back(To::Float(numbers[index]));
                            } else {
                                y.push_back(To::Float(numbers[index]));
                            }
                        }
                        if (x.size() > 0 && y.size() > 0) {
                            warningList.push_back(x[0]);
                            warningList.push_back(y[0]);
                            for (int j : UtilityList::range2(1, x.size() - 1)) {
                                if (x[j] < 99.0) {
                                    warningList.push_back(x[j]);
                                    warningList.push_back(y[j]);
                                    warningList.push_back(x[j]);
                                    warningList.push_back(y[j]);
                                } else {
                                    warningList.push_back(x[j - 1]);
                                    warningList.push_back(y[j - 1]);
                                    warningList.push_back(x[j + 1]);
                                    warningList.push_back(y[j + 1]);
                                }
                            }
                            warningList.push_back(x[x.size() - 1]);
                            warningList.push_back(y[x.size() - 1]);
                        }
                    }
                }
                hashSwo[m] = warningList;
            }
        }
    }
}
