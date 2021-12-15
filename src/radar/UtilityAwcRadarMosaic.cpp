// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/UtilityAwcRadarMosaic.h"
#include "util/UtilityIO.h"
#include "util/UtilityString.h"

QString UtilityAwcRadarMosaic::getNearestMosaic(const LatLon& location) {
    float shortestDistance = 1000.00;
    QString bestIndex;
    for (const auto& s : sectorToLatLon.keys()) {
        const auto latLon = sectorToLatLon[s];
        const auto currentDistance = location.dist(latLon);
        if (currentDistance < shortestDistance) {
            shortestDistance = currentDistance;
            bestIndex = s;
        }
    }
    if (bestIndex == "") {
        return "BLAH";
    }
    const auto index = sectorLabels.indexOf(bestIndex);
    return sectors[index];
}

QString UtilityAwcRadarMosaic::get(const QString& product, const QString& sector) {
    QString baseAddOn = "radar/";
    QString imageType = ".gif";
    if (product.contains("sat_")) {
        baseAddOn = "sat/us/";
        imageType = ".jpg";
    }
    return baseUrl + baseAddOn + product + "_" + sector + imageType;
}

QStringList UtilityAwcRadarMosaic::getAnimation(const QString& productF, const QString& sector, [[maybe_unused]] int notUsed) {
    // image_url[14] = "/data/obs/radar/20190131/22/20190131_2216_rad_rala_dtw.gif";;
    // https://www.aviationweather.gov/satellite/plot?region=us&type=wv;
    auto product = productF;
    QString baseAddOn = "radar/";
    QString baseAddOnTopUrl = "radar/";
    QString imageType = ".gif";
    QString topUrlAddOn = "";
    if (product.contains("sat_")) {
        baseAddOnTopUrl = "satellite/";
        baseAddOn = "sat/us/";
        imageType = ".jpg";
        topUrlAddOn = "&type=" + product.replace("sat_", "");
    } else if (product.startsWith("rad_")) {
        topUrlAddOn = "&type=" + product.replace("rad_", "") + "&date=";
    }
    const auto productUrl = "https://www.aviationweather.gov/" + baseAddOnTopUrl + "plot?region=" + sector + topUrlAddOn;
    const auto html = UtilityIO::getHtml(productUrl);
    const auto regexp = "image_url.[0-9]{1,2}. = ./data/obs/" + baseAddOn + "([0-9]{8}/[0-9]{2}/[0-9]{8}_[0-9]{4}_" + productF + "_" + sector + imageType + ").";
    const auto urls = UtilityString::parseColumn(html, regexp);
    QStringList finalUrls;
    for (const auto& url : urls) {
        finalUrls.push_back(baseUrl + baseAddOn + url);
    }
    return finalUrls;
}

const QString UtilityAwcRadarMosaic::baseUrl = "https://www.aviationweather.gov/data/obs/";

const QStringList UtilityAwcRadarMosaic::products = {
    "rad_rala",
    "rad_cref",
    "rad_tops-18",
    "sat_irbw",
    "sat_ircol",
    "sat_irnws",
    "sat_vis",
    "sat_wv"
};

const QStringList UtilityAwcRadarMosaic::productLabels = {
    "Reflectivity",
    "Composite Reflectivity",
    "Echo Tops",
    "Infrared (BW)",
    "Infrared (Col)",
    "Infrared (NWS)",
    "Visible",
    "Water Vapor"
};

const QStringList UtilityAwcRadarMosaic::sectors = {
    "us",
    "alb",
    "bwi",
    "clt",
    "tpa",
    "dtw",
    "evv",
    "mgm",
    "msp",
    "lit",
    "pir",
    "ict",
    "aus",
    "cod",
    "den",
    "abq",
    "lws",
    "wmc",
    "las"
};

const QStringList UtilityAwcRadarMosaic::sectorLabels = {
    "CONUS US",
    "Albany NY",
    "Baltimore MD",
    "Charlotte NC",
    "Tampa FL",
    "Detroit MI",
    "Evansville IN",
    "Montgomery AL",
    "Minneapolis MN",
    "Little Rock AR",
    "Pierre SD",
    "Wichita KS",
    "Austin TX",
    "Cody WY",
    "Denver CO",
    "Albuquerque NM",
    "Lewiston ID",
    "Winnemuca NV",
    "Las Vegas NV"
};

QHash<QString, LatLon> UtilityAwcRadarMosaic::sectorToLatLon = {
    {"Albany NY", LatLon(42.65, -73.75)},
    {"Baltimore MD", LatLon(39.29, -76.60)},
    {"Charlotte NC", LatLon(35.22, -80.84)},
    {"Tampa FL", LatLon(27.96, -82.45)},
    {"Detroit MI", LatLon(42.33, -83.04)},
    {"Evansville IN", LatLon(37.97, -87.55)},
    {"Montgomery AL", LatLon(32.36, -86.29)},
    {"Minneapolis MN", LatLon(44.98, -93.25)},
    {"Little Rock AR", LatLon(34.74, -92.28)},
    {"Pierre SD", LatLon(44.36, -100.33)},
    {"Wichita KS", LatLon(37.69, -97.31)},
    {"Austin TX", LatLon(30.28, -97.73)},
    {"Cody WY", LatLon(44.52, -109.05)},
    {"Denver CO", LatLon(39.74, -104.99)},
    {"Albuquerque NM", LatLon(35.10, -106.62)},
    {"Lewiston ID", LatLon(46.41, -117.01)},
    {"Winnemuca NV", LatLon(40.97, -117.73)},
    {"Las Vegas NV", LatLon(36.11, -115.17)}
};
