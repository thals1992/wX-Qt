// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/UtilityDownloadNws.h"
#include <QByteArray>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "common/GlobalVariables.h"
#include "util/UtilityIO.h"
#include "util/UtilityString.h"

QString UtilityDownloadNws::getHourlyData(const LatLon& latLon) {
    const auto pointsData = getLocationPointData(latLon);
    const auto hourlyUrl = UtilityString::parse(pointsData, "\"forecastHourly\": \"(.*?)\"");
    return UtilityIO::getHtml(hourlyUrl);
}

QString UtilityDownloadNws::get7DayData(const LatLon& latLon) {
    const auto pointsData = getLocationPointData(latLon);
    const auto forecastUrl = UtilityString::parse(pointsData, "\"forecast\": \"(.*?)\"");
    return UtilityIO::getHtml(forecastUrl);
}

QString UtilityDownloadNws::getLocationPointData(const LatLon& latLon) {
    return UtilityIO::getHtml((GlobalVariables::nwsApiUrl + "/points/" + latLon.latString + "," + latLon.lonString));
}

QString UtilityDownloadNws::getCap(const QString& sector) {
    if (sector == "us") {
        return getHtmlWithXml("https://api.weather.gov/alerts/active?region_type=land");
    } else {
        return getHtmlWithXml("https://api.weather.gov/alerts/active?state=" + sector.toUpper());
    }
}

QString UtilityDownloadNws::getHtmlWithXml(const QString& url) {
    QNetworkAccessManager manager;
    auto request = QNetworkRequest(QUrl(url));
    request.setHeader(QNetworkRequest::UserAgentHeader, GlobalVariables::appName + " " + GlobalVariables::appCreatorEmail);
    request.setRawHeader(QByteArray("Accept"), QByteArray("application/atom+xml"));
    QNetworkReply * response = manager.get(request);
    QEventLoop event;
    connect(response, &QNetworkReply::finished, &event, &QEventLoop::quit);
    event.exec();
    const QString html = response->readAll();
    delete response;
    return html;
}
