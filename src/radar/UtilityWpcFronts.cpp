// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/UtilityWpcFronts.h"
#include <cmath>
#include "common/GlobalVariables.h"
#include "objects/LatLon.h"
#include "radar/FrontTypeEnum.h"
#include "radar/PressureCenterTypeEnum.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityMath.h"
#include "util/UtilityString.h"

// Data file - https://www.wpc.ncep.noaa.gov/basicwx/coded_srp.txt;
// Decoder - https://www.wpc.ncep.noaa.gov/basicwx/read_coded_fcst_bull.shtml;
// Image - https://www.wpc.ncep.noaa.gov/basicwx/basicwx_ndfd.php;

//  CODED SURFACE FRONTAL POSITIONS FORECAST;
//  NWS WEATHER PREDICTION CENTER COLLEGE PARK MD;
//  1117 AM EST FRI DEC 20 2019;

//  SURFACE PROG VALID 201912201800Z;
//  HIGHS 1043 5010795 1036 3750811 1036 4061092 1026 3121240;
//  LOWS 1000 5301138 1021 4610937 1005 4931216 1005 4151308 1021 3351009;
//  STNRY 2310761 2230786 2210811 2220827 2220838;
//  STNRY 4050725 4010749 3990769 4020794 4050809 4080816;
//  WARM 4610937 4610923 4560905 4480890 4340873 4220854 4140836;
//  4070815;
//  COLD 4620937 4570948 4570961 4600977;
//  WARM 5251080 5251064 5171042 4951027 4791013 4680995 4600978;
//  COLD 4931216 4701239 4501262 4391277 4251295;
//  STNRY 4151307 4001313 3851326;
//  STNRY 5251080 5241105 5271130 5301139;
//  STNRY 5301139 5331149 5401174 5451199 5531223 5631241;
//  TROF 2220879 2530886 2750886 2970879;
//  TROF 4581084 4441085 4251096;
//  TROF 3941043 3671043 3391055;
//  TROF 4600938 4350945 4160956 3940974 3760988 3630996 3511002;
//  3251012 2991024 2871026;
//  WARM 4161307 4211300 4261294;
//  TROF 5361348 5171317 4971300 4801292;
//  TROF 5241139 4991127 4721125;
//  TROF 3171112 2901103 2711092 2491077;

//  SURFACE PROG VALID 201912210000Z;
//  HIGHS 1035 3971077 1042 4900775 1023 3181216;
//  LOWS 1005 5011189 1005 4051297 1000 5271115 1021 4740914 1022 3420997;
//  COLD 4730916 4690932 4700953 4730971;
//  STNRY 2310757 2280774 2250791 2260806 2300825;

const QString UtilityWpcFronts::separator = "ABC123";
QVector<PressureCenter> UtilityWpcFronts::pressureCenters;
QVector<Fronts> UtilityWpcFronts::fronts;
DownloadTimer UtilityWpcFronts::timer = DownloadTimer("WPC FRONTS");

void UtilityWpcFronts::addColdFrontTriangles([[maybe_unused]] Fronts * front, [[maybe_unused]] const QStringList& tokens) {
    // size of triangle
    float length = 0.4;
    auto startIndex = 0;
    auto indexIncrement = 1;
    if (front->frontType == FrontTypeEnum::OCFNT) {
        startIndex = 1;
        indexIncrement = 2;
    }
    for (auto index = startIndex; index < tokens.size(); index += indexIncrement) {
        auto coordinates = parseLatLon(tokens[index]);
        if (index < (tokens.size() - 1)) {
            auto coordinates2 = parseLatLon(tokens[index + 1]);
            auto distance = UtilityMath::distanceOfLine(coordinates[0], coordinates[1], coordinates2[0], coordinates2[1]);
            int numberOfTriangles = floor(distance / length);
            // construct two lines which will consist of adding 4 points;
            for (auto pointNumber : UtilityList::range3(1, numberOfTriangles, 2)) {
                float x1 = coordinates[0] + ((coordinates2[0] - coordinates[0]) * length * pointNumber) / distance;
                float y1 = coordinates[1] + ((coordinates2[1] - coordinates[1]) * length * pointNumber) / distance;
                float x3 = coordinates[0] + ((coordinates2[0] - coordinates[0]) * length * (pointNumber + 1)) / distance;
                float y3 = coordinates[1] + ((coordinates2[1] - coordinates[1]) * length * (pointNumber + 1)) / distance;
                auto p2 = UtilityMath::computeTipPoint(x1, y1, x3, y3, true);
                float x2 = p2[0];
                float y2 = p2[1];
                front->coordinates.push_back(LatLon(x1, y1));
                front->coordinates.push_back(LatLon(x2, y2));
                front->coordinates.push_back(LatLon(x2, y2));
                front->coordinates.push_back(LatLon(x3, y3));
            }
        }
    }
}

void UtilityWpcFronts::addWarmFrontSemicircles([[maybe_unused]] Fronts * front, [[maybe_unused]] const QStringList& tokens) {
    float length = 0.4;
    auto startIndex = 0;
    auto indexIncrement = 1;
    if (front->frontType == FrontTypeEnum::OCFNT) {
        startIndex = 2;
        indexIncrement = 2;
        length = 0.2;
    }
    for (auto index : UtilityList::range3(startIndex, tokens.size(), indexIncrement)) {
        auto coordinates = parseLatLon(tokens[index]);
        if (index < (tokens.size() - 1)) {
            auto coordinates2 = parseLatLon(tokens[index + 1]);
            auto distance = UtilityMath::distanceOfLine(coordinates[0], coordinates[1], coordinates2[0], coordinates2[1]);
            int numberOfTriangles = floor(distance / length);
            // construct two lines which will consist of adding 4 points;
            for (auto pointNumber : UtilityList::range3(1, numberOfTriangles, 4)) {
                float x1 = coordinates[0] + ((coordinates2[0] - coordinates[0]) * length * pointNumber) / distance;
                float y1 = coordinates[1] + ((coordinates2[1] - coordinates[1]) * length * pointNumber) / distance;
                float center1 = coordinates[0] + ((coordinates2[0] - coordinates[0]) * length * (pointNumber + 0.5)) / distance;
                float center2 = coordinates[1] + ((coordinates2[1] - coordinates[1]) * length * (pointNumber + 0.5)) / distance;
                float x3 = coordinates[0] + ((coordinates2[0] - coordinates[0]) * length * (pointNumber + 1)) / distance;
                float y3 = coordinates[1] + ((coordinates2[1] - coordinates[1]) * length * (pointNumber + 1)) / distance;
                front->coordinates.push_back(LatLon(x1, y1));
                auto slices = 20;
                float step = M_PI / slices;
                float rotation = 1.0;
                float xDiff = x3 - x1;
                float yDiff = y3 - y1;
                float angle = atan2(yDiff, xDiff) * 180.0 / M_PI;
                auto sliceStart = static_cast<int>((slices * angle) / 180.0);
                for (auto i : UtilityList::range2(sliceStart, slices + sliceStart + 1)) {
                    float x = rotation * length * cos(step * i) + center1;
                    float y = rotation * length * sin(step * i) + center2;
                    front->coordinates.push_back(LatLon(x, y));
                    front->coordinates.push_back(LatLon(x, y));
                }
                front->coordinates.push_back(LatLon(x3, y3));
            }
        }
    }
}

void UtilityWpcFronts::addFrontDataStationaryWarm(Fronts * front, const QStringList& tokens) {
    for (auto index : UtilityList::range(tokens.size())) {
        auto coordinates = parseLatLon(tokens[index]);
        if (index != 0 && index != (tokens.size() - 1)) {
            front->coordinates.push_back(LatLon(coordinates[0], coordinates[1]));
        }
    }
}

void UtilityWpcFronts::addFrontDataTrof(Fronts * front, const QStringList& tokens) {
    float fraction = 0.8;
    for (auto index : UtilityList::range(tokens.size() - 1)) {
        auto coordinates = parseLatLon(tokens[index]);
        if (coordinates.size() > 1) {
            front->coordinates.push_back(LatLon(coordinates[0], coordinates[1]));
        }
        auto oldCoordinates = parseLatLon(tokens[index + 1]);
        if (coordinates.size() > 1) {
            auto coord = UtilityMath::computeMiddlePoint(coordinates[0], coordinates[1], oldCoordinates[0], oldCoordinates[1], fraction);
            front->coordinates.push_back(LatLon(coord[0], coord[1]));
        }
    }
}

void UtilityWpcFronts::addFrontData(Fronts * front, const QStringList& tokens) {
    for (auto index : UtilityList::range(tokens.size())) {
        auto coordinates = parseLatLon(tokens[index]);
        if (coordinates.size() > 1) {
            front->coordinates.push_back(LatLon(coordinates[0], coordinates[1]));
            if (index != 0 && index != (tokens.size() - 1)) {
                front->coordinates.push_back(LatLon(coordinates[0], coordinates[1]));
            }
        }
    }
}

QVector<float> UtilityWpcFronts::parseLatLon(const QString& stringValue) {
    if (stringValue.size() != 7) {
        return {};
    } else {
        float lat = To::Float(UtilityString::substring(stringValue, 0, 2) + "." + UtilityString::substring(stringValue, 2, 3));
        float lon = 0.0;
        if (stringValue[3] == '0') { // QT5 was "0"
            lon = To::Float(UtilityString::substring(stringValue, 4, 6) + "." + UtilityString::substring(stringValue, 6, 7));
        } else {
            lon = To::Float(UtilityString::substring(stringValue, 3, 6) + "." + UtilityString::substring(stringValue, 6, 7));
        }
        return {lat, lon};
    }
}

void UtilityWpcFronts::get() {
    if (timer.isRefreshNeeded()) {
        pressureCenters.clear();
        fronts.clear();
        auto urlBlob = GlobalVariables::nwsWPCwebsitePrefix + "/basicwx/coded_srp.txt";
        auto html = UtilityIO::getHtml(urlBlob);
        html = html.replace(GlobalVariables::newline, separator);
        auto timestamp = UtilityString::parse(html, "SURFACE PROG VALID ([0-9]{12}Z)");
        Utility::writePref("WPC_FRONTS_TIMESTAMP", timestamp);
        html = UtilityString::parse(html, "SURFACE PROG VALID [0-9]{12}Z(.*?)" + separator + " " + separator);
        html = html.replace(separator, GlobalVariables::newline);
        auto lines = html.split(GlobalVariables::newline);
        for (auto index : UtilityList::range(lines.size())) {
            auto data = lines[index];
            if (index < lines.size() - 1) {
                int charIndex = 0;
                if (lines[index + 1][charIndex] != 'H' // QT5 all were "H" not 'H'
                        && lines[index + 1][charIndex] != 'L'
                        && lines[index + 1][charIndex] != 'C'
                        && lines[index + 1][charIndex] != 'S'
                        && lines[index + 1][charIndex] != 'O'
                        && lines[index + 1][charIndex] != 'T'
                            && lines[index + 1][charIndex] != 'W') {
                    data += lines[index + 1];
                    if (index < lines.size() - 2 && lines[index + 2][charIndex] != 'H'
                            && lines[index + 2][charIndex] != 'L'
                            && lines[index + 2][charIndex] != 'C'
                            && lines[index + 2][charIndex] != 'S'
                            && lines[index + 2][charIndex] != 'O'
                            && lines[index + 2][charIndex] != 'T'
                                && lines[index + 2][charIndex] != 'W') {
                        data += lines[index + 2];
                    }
                }
            }
            auto tokens = data.trimmed().split(" ");
            if (tokens.size() > 1) {
                auto type = tokens[0];
                tokens.removeFirst();
                if (type == "HIGHS") {
                    for (auto index2 : UtilityList::range3(0, tokens.size(), 2)) {
                        if (index2 + 1 < tokens.size()) {
                            auto coordinates = parseLatLon(tokens[index2 + 1]);
                            pressureCenters.push_back(PressureCenter(PressureCenterTypeEnum::HIGH, tokens[index2], coordinates[0], coordinates[1]));
                        }
                    }
                } else if (type == "LOWS") {
                    for (auto index2 : UtilityList::range3(0, tokens.size(), 2)) {
                        if (index2 + 1 < tokens.size()) {
                            auto coordinates = parseLatLon(tokens[index2 + 1]);
                            pressureCenters.push_back(PressureCenter(PressureCenterTypeEnum::LOW, tokens[index2], coordinates[0], coordinates[1]));
                        }
                    }
                } else if (type == "COLD") {
                    auto front = Fronts(FrontTypeEnum::COLD);
                    addFrontData(&front, tokens);
                    addColdFrontTriangles(&front, tokens);
                    fronts.push_back(front);
                } else if (type == "STNRY") {
                    auto front = Fronts(FrontTypeEnum::STNRY);
                    addFrontData(&front, tokens);
                    fronts.push_back(front);
                    auto frontStWarm = Fronts(FrontTypeEnum::STNRY_WARM);
                    addFrontDataStationaryWarm(&frontStWarm, tokens);
                    fronts.push_back(frontStWarm);
                } else if (type == "WARM") {
                    auto front = Fronts(FrontTypeEnum::WARM);
                    addFrontData(&front, tokens);
                    addWarmFrontSemicircles(&front, tokens);
                    fronts.push_back(front);
                } else if (type == "TROF") {
                    auto front = Fronts(FrontTypeEnum::TROF);
                    addFrontDataTrof(&front, tokens);
                    fronts.push_back(front);
                } else if (type == "OCFNT") {
                    auto front = Fronts(FrontTypeEnum::OCFNT);
                    addFrontData(&front, tokens);
                    addColdFrontTriangles(&front, tokens);
                    addWarmFrontSemicircles(&front, tokens);
                    fronts.push_back(front);
                }
            }
        }
    }
}
