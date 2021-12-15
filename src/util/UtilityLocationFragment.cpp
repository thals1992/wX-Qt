// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/UtilityLocationFragment.h"
#include "util/UtilityString.h"

const QString UtilityLocationFragment::nws7dayTemp1 = "with a low around (-?[0-9]{1,3})\\.";
const QString UtilityLocationFragment::nws7dayTemp2 = "with a high near (-?[0-9]{1,3})\\.";
const QString UtilityLocationFragment::nws7dayTemp3 = "teady temperature around (-?[0-9]{1,3})\\.";
const QString UtilityLocationFragment::nws7dayTemp4 = "Low around (-?[0-9]{1,3})\\.";
const QString UtilityLocationFragment::nws7dayTemp5 = "High near (-?[0-9]{1,3})\\.";
const QString UtilityLocationFragment::nws7dayTemp6 = "emperature falling to around (-?[0-9]{1,3}) ";
const QString UtilityLocationFragment::nws7dayTemp7 = "emperature rising to around (-?[0-9]{1,3}) ";
const QString UtilityLocationFragment::nws7dayTemp8 = "emperature falling to near (-?[0-9]{1,3}) ";
const QString UtilityLocationFragment::nws7dayTemp9 = "emperature rising to near (-?[0-9]{1,3}) ";
const QString UtilityLocationFragment::nws7dayTemp10 = "High near (-?[0-9]{1,3}),";
const QString UtilityLocationFragment::nws7dayTemp11 = "Low around (-?[0-9]{1,3}),";
const QString UtilityLocationFragment::sevenDayWind1 = "wind ([0-9]*) to ([0-9]*) mph";
const QString UtilityLocationFragment::sevenDayWind2 = "wind around ([0-9]*) mph";
const QString UtilityLocationFragment::sevenDayWind3 = "with gusts as high as ([0-9]*) mph";
const QString UtilityLocationFragment::sevenDayWind4 = " ([0-9]*) to ([0-9]*) mph after";
const QString UtilityLocationFragment::sevenDayWind5 = " around ([0-9]*) mph after ";
const QString UtilityLocationFragment::sevenDayWind6 = " ([0-9]*) to ([0-9]*) mph in ";
const QString UtilityLocationFragment::sevenDayWind7 = "around ([0-9]*) mph";
const QString UtilityLocationFragment::sevenDayWind8 = "Winds could gust as high as ([0-9]*) mph\\.";
const QString UtilityLocationFragment::sevenDayWind9 = " ([0-9]*) to ([0-9]*) mph.";

const QHash<QString, QString> UtilityLocationFragment::windDir = {
    {"north", "N"},
    {"north northeast", "NNE"},
    {"northeast", "NE"},
    {"east northeast", "ENE"},
    {"east", "E"},
    {"east southeast", "ESE"},
    {"south southeast", "SSE"},
    {"southeast", "SE"},
    {"south", "S"},
    {"south southwest", "SSW"},
    {"southwest", "SW"},
    {"west southwest", "WSW"},
    {"west", "W"},
    {"west northwest", "WNW"},
    {"northwest", "NW"},
    {"north northwest", "NNW"}
};

QString UtilityLocationFragment::extract7DayMetrics(const QString& chunk) {
    QString spacing = " ";
    // wind 24 to 29 mph;
    auto wind = UtilityString::parseTwo(chunk, sevenDayWind1);
    // wind around 9 mph;
    auto wind2 = UtilityString::parse(chunk, sevenDayWind2);
    // 5 to 10 mph after;
    auto wind3 = UtilityString::parseTwo(chunk, sevenDayWind4);
    // around 5 mph after;
    auto wind4 = UtilityString::parse(chunk, sevenDayWind5);
    // 5 to 7 mph in;
    auto wind5 = UtilityString::parseTwo(chunk, sevenDayWind6);
    // around 6 mph.;
    auto wind7 = UtilityString::parse(chunk, sevenDayWind7);
    // with gusts as high as 21 mph;
    auto gust = UtilityString::parse(chunk, sevenDayWind3);
    // 5 to 7 mph.;
    auto wind9 = UtilityString::parseTwo(chunk, sevenDayWind9);
    // Winds could gusts as high as 21 mph.;
    if (gust == "") {
        gust = UtilityString::parse(chunk, sevenDayWind8);
    }
    if (gust != "") {
        gust = " G " + gust + " mph";
    } else {
        gust = " mph";
    }
    if (wind[0] != "" && wind[1] != "") {
        return spacing + wind[0] + "-" + wind[1] + gust;
    } else if (wind2 != "") {
        return spacing + wind2 + gust;
    } else if (wind3[0] != "" && wind3[1] != "") {
        return spacing + wind3[0] + "-" + wind3[1] + gust;
    } else if (wind4 != "") {
        return spacing + wind4 + gust;
    } else if (wind5[0] != "" && wind5[1] != "") {
        return spacing + wind5[0] + "-" + wind5[1] + gust;
    } else if (wind7 != "") {
        return spacing + wind7 + gust;
    } else if (wind9[0] != "" && wind9[1] != "") {
        return spacing + wind9[0] + "-" + wind9[1] + gust;
    } else {
        return "";
    }
}

QString UtilityLocationFragment::extractWindDirection(const QString& chunk) {
    const QStringList patterns = {
        "Breezy, with a[n]? (.*?) wind",
        "wind becoming (\\w+\\s?\\w*) around",
        "wind becoming (.*?) [0-9]",
        "\\. (\\w+\\s?\\w*) wind ",
        "Windy, with a[n]? (.*?) wind",
        "Blustery, with a[n]? (.*?) wind",
        "Light (.*?) wind"
    };
    QStringList windResults;
    for (const auto& pattern : patterns) {
        windResults.push_back(UtilityString::parse(chunk, pattern));
    }
    QString retStr = "";
    for (const auto& windToken : windResults) {
        if (windToken != "") {
            retStr = windToken;
            break;
        }
    }
    if (retStr == "") {
        return "";
    } else {
        auto ret = windDir[retStr.toLower()];
        return " " + ret + "";
    }
}

QString UtilityLocationFragment::extractTemp(const QString& blob) {
    const auto regexps = {
        nws7dayTemp1,
        nws7dayTemp2,
        nws7dayTemp3,
        nws7dayTemp4,
        nws7dayTemp5,
        nws7dayTemp6,
        nws7dayTemp7,
        nws7dayTemp8,
        nws7dayTemp9,
        nws7dayTemp10,
        nws7dayTemp11
    };
    for (const auto& regexp : regexps) {
        auto temp = UtilityString::parse(blob, regexp);
        if (temp != "") {
            return temp;
        }
    }
    return "";
}
