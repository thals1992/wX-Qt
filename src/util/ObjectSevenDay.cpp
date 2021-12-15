// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/ObjectSevenDay.h"
#include <QVector>
#include "settings/UIPreferences.h"
#include "util/ObjectForecast.h"
#include "util/Utility.h"
#include "util/UtilityDownloadNws.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"
#include "util/UtilityUS.h"

ObjectSevenDay::ObjectSevenDay() {
}

ObjectSevenDay::ObjectSevenDay(const LatLon& latLon) {
    this->latLon = latLon;
}

void ObjectSevenDay::process() {
    if (UIPreferences::useNwsApi) {
        const auto html = UtilityDownloadNws::get7DayData(latLon);
        QVector<ObjectForecast> forecasts;
        const auto names = UtilityString::parseColumn(html, "\"name\": \"(.*?)\",");
        const auto temperatures = UtilityString::parseColumn(html, "\"temperature\": (.*?),");
        const auto windSpeeds = UtilityString::parseColumn(html, "\"windSpeed\": \"(.*?)\",");
        const auto windDirections = UtilityString::parseColumn(html, "\"windDirection\": \"(.*?)\",");
        const auto detailedLocalForecasts = UtilityString::parseColumn(html, "\"detailedForecast\": \"(.*?)\"");
        icons = UtilityString::parseColumn(html, "\"icon\": \"(.*?)\",");
        const auto shortLocalForecasts = UtilityString::parseColumn(html, "\"shortForecast\": \"(.*?)\",");
        for (auto index : UtilityList::range(names.size())) {
            const auto name = Utility::safeGet(names, index);
            const auto temperature = Utility::safeGet(temperatures, index);
            const auto windSpeed = Utility::safeGet(windSpeeds, index);
            const auto windDirection = Utility::safeGet(windDirections, index);
            const auto icon = Utility::safeGet(icons, index);
            const auto shortForecast = Utility::safeGet(shortLocalForecasts, index);
            const auto detailedForecast = Utility::safeGet(detailedLocalForecasts, index);
            forecasts.push_back(ObjectForecast(name, temperature, windSpeed, windDirection, icon, shortForecast, detailedForecast));
        }
        for (const auto& forecast : forecasts) {
            detailedForecasts.push_back(forecast.name + ": " + forecast.detailedForecast);
            shortForecasts.push_back(forecast.name + ": " + forecast.shortForecast);
        }
    } else {
        const auto forecastStringList = UtilityUS::getCurrentConditionsUS(latLon.latString, latLon.lonString);
        const auto forecastString = forecastStringList[1];
        const auto iconString = forecastStringList[0];
        const auto forecasts = forecastString.split("\n");
        const auto iconList = UtilityString::parseColumn(iconString, "<icon-link>(.*?)</icon-link>");
        for (auto index : UtilityList::range(forecasts.size())) {
            if (forecasts[index] != "") {
                detailedForecasts.push_back(forecasts[index].trimmed());
                if (iconList.size() > index) {
                    icons.push_back(iconList[index]);
                } else {
                    icons.push_back("");
                }
            }
        }
    }
}
