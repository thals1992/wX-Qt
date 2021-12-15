// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/UtilitySpcStormReports.h"
#include "common/GlobalVariables.h"

QVector<StormReport> UtilitySpcStormReports::process(const QStringList& lines) {
    QVector<StormReport> stormReports;
    for (const auto& line : lines) {
        if (line == "") {
            continue;
        }
        QString lat = "";
        QString lon = "";
        QString state = "";
        QString time = "";
        QString address = "";
        QString damageReport = "";
        QString magnitude = "";
        QString city = "";
        QString output = "";
        QString damageHeader = "";
        if (line.contains(",F_Scale,")) {
            damageHeader = "Tornado Reports";
        } else if (line.contains(",Speed,")) {
            damageHeader = "Wind Reports";
        } else if (line.contains(",Size,")) {
            damageHeader = "Hail Reports";
        } else {
            auto lineChunks = line.split(",");
            if (lineChunks.size() > 7) {
                output += lineChunks[0];
                output += " ";
                output += lineChunks[1];
                output += " ";
                output += lineChunks[2];
                output += " ";
                output += lineChunks[3];
                output += " ";
                output += lineChunks[4];
                output += " ";
                output += lineChunks[5];
                output += " ";
                output += lineChunks[6];
                output += GlobalVariables::newline;
                output += lineChunks[7];
                time = lineChunks[0];
                magnitude = lineChunks[1];
                address = lineChunks[2];
                city = lineChunks[3];
                state = lineChunks[4];
                lat = lineChunks[5];
                lon = lineChunks[6];
                damageReport = lineChunks[7];
            }
        }
        stormReports.push_back(StormReport(output, lat, lon, time, magnitude, address, city, state, damageReport, damageHeader));
    }
    return stormReports;
}
