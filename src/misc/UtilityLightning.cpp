// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/UtilityLightning.h"

const QStringList UtilityLightning::sectors = {
    "Australia",
    "Florida",
    "OK / KS",
    "New Zealand",
    "North America",
    "South America",
    "Texas",
    "US",
};

const QStringList UtilityLightning::times = {
    "15 MIN",
    "2 HR",
    "12 HR",
    "24 HR",
    "48 HR"
};

QString UtilityLightning::getImageUrl(const QString& sector, const QString& period) {
    QString url = "";
    const QString baseUrl = "https://images.lightningmaps.org/blitzortung/america/index.php?map=";
    const QString baseUrlOceania = "https://images.lightningmaps.org/blitzortung/oceania/index.php?map=";
    if (sector.contains("australia") || sector.contains("new_zealand")) {
        url = baseUrlOceania + sector + "&period=" + period;
    } else {
        url = baseUrl + sector + "&period=" + period;
    }
    return url;
}

QString UtilityLightning::getSectorPretty(const QString& code) {
    if (code == "usa_big") {
        return "US";
    } else if (code == "florida_big") {
        return "Florida";
    } else if (code == "texas_big") {
        return "Texas";
    } else if (code == "oklahoma_kansas_big") {
        return "OK / KS";
    } else if (code == "north_middle_america") {
        return "North America";
    } else if (code == "south_america") {
        return "South America";
    } else if (code == "australia_big") {
        return "Australia";
    } else if (code == "new_zealand_big") {
        return "New Zealand";
    }
    return "";
}

QString UtilityLightning::getSector(const QString& sector) {
    if (sector == "US") {
        return "usa_big";
    } else if (sector == "Florida") {
        return "florida_big";
    } else if (sector == "Texas") {
        return "texas_big";
    } else if (sector == "OK / KS") {
        return "oklahoma_kansas_big";
    } else if (sector == "North America") {
        return "north_middle_america";
    } else if (sector == "South America") {
        return "south_america";
    } else if (sector == "Australia") {
        return "australia_big";
    } else if (sector == "New Zealand") {
        return "new_zealand_big";
    }
    return "";
}

QString UtilityLightning::getTimePretty(const QString& period) {
    if (period == "0.25") {
        return "15 MIN";
    } else if (period == "2") {
        return "2 HR";
    } else if (period == "12") {
        return "12 HR";
    } else if (period == "24") {
        return "24 HR";
    } else if (period == "48") {
        return "48 HR";
    }
    return "";
}

QString UtilityLightning::getTime(const QString& periodPretty) {
    if (periodPretty == "15 MIN") {
        return "0.25";
    } else if (periodPretty == "2 HR") {
        return "2";
    } else if (periodPretty == "12 HR") {
        return "12";
    } else if (periodPretty == "24 HR") {
        return "24";
    } else if (periodPretty == "48 HR") {
        return "48";
    }
    return "";
}
