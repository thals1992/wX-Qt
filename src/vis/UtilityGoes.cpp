// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "vis/UtilityGoes.h"
#include "common/GlobalVariables.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"

QString UtilityGoes::getImageSize(const QString& sector) {
    // const QString size = "1200x1200";  // was latest;
    const QString size = "latest";
    // if (UIPreferences.goesUseFullResolutionImages {
    //    return size;
    // else {
    return sizeMap.value(sector, size);
}

QString UtilityGoes::getImageGoesFloater(QString url, QString product) {
    auto urlFinal = url;
    urlFinal = urlFinal.replace("GEOCOLOR", product);
    return urlFinal;
}

QString UtilityGoes::getImage(const QString& product, const QString& sector) {
    auto sectorLocal = "SECTOR/" + sector;
    if (sector == "FD" || sector == "CONUS" || sector == "CONUS-G17") {
        sectorLocal = sector;
    }
    QString satellite = "GOES16";
    if (sectorsInGoes17.contains(sector)) {
        satellite = "GOES17";
        if (sector == "CONUS-G17") {
            sectorLocal = "CONUS";
        }
        if (sector == "FD-G17") {
            sectorLocal = "FD";
        }
    }
    // https://cdn.star.nesdis.noaa.gov/GOES16/ABI/SECTOR/cgl/03/;
    // https://cdn.star.nesdis.noaa.gov/GOES16/ABI/SECTOR/cgl/12/latest.jpg;
    // https://cdn.star.nesdis.noaa.gov/GOES17/ABI/CONUS/GEOCOLOR/1250x750.jpg;
    // https://cdn.star.nesdis.noaa.gov/GOES16/ABI/CONUS/GEOCOLOR/1250x750.jpg;
    // If GLM is selected  and  and  user switches to sector w/o GLM show default instead;
    QString url = GlobalVariables::goes16Url + "/" + satellite + "/ABI/" + sectorLocal + "/" + product + "/" + getImageSize(sector) + ".jpg";
    if (product == "GLM") {
        url = url.replace("ABI", "GLM");
        url = url.replace(sectorLocal + "/GLM", sectorLocal + "/EXTENT3");
    }
    return url;
}

// https://www.star.nesdis.noaa.gov/GOES/sector_band.php?sat=G17&sector=ak&band=GEOCOLOR&length=12;
// https://www.star.nesdis.noaa.gov/GOES/sector_band.php?sat=G16&sector=cgl&band=GEOCOLOR&length=12;
QStringList UtilityGoes::getAnimation(const QString& product, const QString& sector, int frameCount) {
    auto baseUrl = getImage(product, sector);
    auto items = baseUrl.split("/");
    items.pop_back();
    items.pop_back();
    baseUrl = items.join("/") + "/" + product + "/";
    auto html = UtilityIO::getHtml(baseUrl);
    auto urlList = UtilityString::parseColumn(html.replace("\r\n", " "), "<a href=\"([^\\s]*?1200x1200.jpg)\">");
    QStringList returnList;
    if (urlList.size() > frameCount) {
        for ([[maybe_unused]] auto t : UtilityList::range(frameCount)) {
            auto u = urlList.takeLast();
            returnList.push_front(baseUrl + u);
        }
    }
    return returnList;
    // <a href="20211842100_GOES16-ABI-FL-GEOCOLOR-AL052021-1000x1000.jpg">
}

QStringList UtilityGoes::getAnimationGoesFloater(const QString& product, const QString& url, int frameCount) {
    auto baseUrl = url;
    baseUrl = baseUrl.replace("GEOCOLOR", product);
    baseUrl = baseUrl.replace("latest.jpg", "");
    auto html = UtilityIO::getHtml(baseUrl);
    auto urlList = UtilityString::parseColumn(html, "<a href=\"([^\\s]*?1000x1000.jpg)\">");
    QStringList returnList;
    // takeLast
    // push_front
    if (urlList.size() > frameCount) {
        for ([[maybe_unused]] auto t : UtilityList::range(frameCount)) {
            auto u = urlList.takeLast();
            returnList.push_front(baseUrl + u);
        }
    }
    return returnList;
}


QString UtilityGoes::getNearestGoesLocation(const LatLon& location) {
    float shortestDistance = 1000.00;
    QString bestIndex;
    for (const auto& s : sectorToLatLon.keys()) {
        auto latLon = sectorToLatLon[s];
        const auto currentDistance = location.dist(latLon);
        if (currentDistance < shortestDistance) {
            shortestDistance = currentDistance;
            bestIndex = s;
        }
    }
    if (bestIndex == "") {
        return "BLAH";
    }
    return bestIndex;
}

const QHash<QString, QString> UtilityGoes::sizeMap = {
    {"CONUS", "2500x1500"},
    {"CONUS-G17", "2500x1500"},
    {"FD", "1808x1808"},
    {"FD-G17", "1808x1808"},
    {"gm", "1000x1000"},
    {"car", "1000x1000"},
    {"eus", "1000x1000"},
    {"eep", "1800x1080"},
    {"wus", "2000x2000"},
    {"tpw", "1800x1080"},
    {"taw", "1800x1080"},
    {"can", "1125x560"},
    {"mex", "1000x1000"},
    {"nsa", "1800x1080"},
    {"ssa", "1800x1080"},
    {"np", "1800x1080"},
    {"cam", "1000x1000"},
    {"np", "1800x1080"},
    {"ak", "1000x1000"},
    {"cak", "1200x1200"},
    {"sea", "1200x1200"},
    {"hi", "1200x1200"},
    {"cgl", "1200x1200"},
};

const QStringList UtilityGoes::sectors = {
    "FD: GOES-EAST Full Disk",
    "FD-G17: GOES-WEST Full Disk",
    "CONUS: GOES-EAST US",
    "CONUS-G17: GOES-WEST US",
    "pnw: Pacific Northwest",
    "nr: Northern Rockies",
    "umv: Upper Mississippi Valley",
    "cgl: Central Great Lakes",
    "ne: Northeast",
    "psw: Pacific Southwest",
    "sr: Southern Rockies",
    "sp: Southern Plains",
    "smv: Southern Mississippi Valley",
    "se: Southeast",
    "gm: Gulf of Mexico",
    "car: Caribbean",
    "eus: U.S. Atlantic Coast",
    "pr: Puerto Rico",
    "taw: Tropical Atlantic: wide view",
    "ak: Alaska",
    "cak: Central Alaska",
    "sea: Southeastern Alaska",
    "hi: Hawaii",
    "tpw: US Pacific Coast",
    "wus: Tropical Pacific",
    "eep: Eastern Pacific",
    "np: Northern Pacific",
    "can: Canada",
    "mex: Mexico",
    "nsa: South America (north)",
    "ssa: South America (south)"
};

const QStringList UtilityGoes::sectorsWithAdditional = {
    "CONUS",
    "CONUS-G17",
    "FD",
    "FD-G17"
};

const QStringList UtilityGoes::sectorsInGoes17 = {
    "CONUS-G17",
    "FD-G17",
    "ak",
    "cak",
    "sea",
    "hi",
    "pnw",
    "psw",
    "tpw",
    "wus",
    "np"
};

const QStringList UtilityGoes::labels = {
    "true color daytime, multispectral IR at night",
    "00.47 um (Band 1) Blue - Visible",
    "00.64 um (Band 2) Red - Visible",
    "00.86 um (Band 3) Veggie - Near IR",
    "01.37 um (Band 4) Cirrus - Near IR",
    "01.6 um (Band 5) Snow/Ice - Near IR",
    "02.2 um (Band 6) Cloud Particle - Near IR",
    "03.9 um (Band 7) Shortwave Window - IR",
    "06.2 um (Band 8) Upper-Level Water Vapor - IR",
    "06.9 um (Band 9) Mid-Level Water Vapor - IR",
    "07.3 um (Band 10) Lower-level Water Vapor - IR",
    "08.4 um (Band 11) Cloud Top - IR",
    "09.6 um (Band 12) Ozone - IR",
    "10.3 um (Band 13) Clean Longwave Window - IR",
    "11.2 um (Band 14) Longwave Window - IR",
    "12.3 um (Band 15) Dirty Longwave Window - IR",
    "13.3 um (Band 16) CO2 Longwave - IR",
    "AirMass - RGB composite based on the data from IR  and  and  WV",
    "Sandwich RGB - Bands 3  and  and  13 combo",
    "Day Cloud Phase",
    "Night Microphysics",
    "Fire Temperature",
    "Dust RGB",
    "GLM FED+GeoColor",
    "DMW"
};

const QStringList UtilityGoes::codes = {
    "GEOCOLOR",
    "01",
    "02",
    "03",
    "04",
    "05",
    "06",
    "07",
    "08",
    "09",
    "10",
    "11",
    "12",
    "13",
    "14",
    "15",
    "16",
    "AirMass",
    "Sandwich",
    "DayCloudPhase",
    "NightMicrophysics",
    "FireTemperature",
    "Dust",
    "GLM",
    "DMW"
};

QHash<QString, LatLon> UtilityGoes::sectorToLatLon = {
    {"cgl", LatLon(39.123405, -82.532938)},   // cgl wellston, Oh;
    {"ne", LatLon(39.360611, -74.431877)},    // ne Atlantic City, NJ;
    {"umv", LatLon(40.622777, -93.934116)},   // umv  Lamoni, IA;
    {"pnw", LatLon(41.589703, -119.858865)},  // pnw Vya, NV;
    {"psw", LatLon(38.524448, -118.623611)},  // psw Hawthorne, NV;
    {"nr", LatLon(41.139980, -104.820244)},   // nr   Cheyenne, Wy;
    {"sr", LatLon(34.653376, -108.677852)},   // sr Fence Lake, NM;
    {"sp", LatLon(31.463787, -96.058022)},    // sp Buffalo, TX;
    {"smv", LatLon(31.326460, -89.289658)},   // smv Hattiesburg, MS;
    {"se", LatLon(30.332184, -81.655647)},    // se Jacksonville, FL;
};
