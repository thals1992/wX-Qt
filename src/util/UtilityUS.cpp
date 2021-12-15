// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "common/GlobalVariables.h"
#include <QVector>
#include "util/UtilityUS.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"

//
// Legacy foreacast support
//
QStringList UtilityUS::getCurrentConditionsUS(const QString& x, const QString& y) {
    QStringList result;
    const auto html = getLocationHtml(x, y);
    const QStringList regexpList = {
        "<temperature type=.apparent. units=.Fahrenheit..*?>(.*?)</temperature>",
        "<temperature type=.dew point. units=.Fahrenheit..*?>(.*?)</temperature>",
        "<direction type=.wind.*?>(.*?)</direction>",
        "<wind-speed type=.gust.*?>(.*?)</wind-speed>",
        "<wind-speed type=.sustained.*?>(.*?)</wind-speed>",
        "<pressure type=.barometer.*?>(.*?)</pressure>",
        "<visibility units=.*?>(.*?)</visibility>",
        "<weather-conditions weather-summary=.(.*?)./>.*?<weather-conditions>",
        "<temperature type=.maximum..*?>(.*?)</temperature>",
        "<temperature type=.minimum..*?>(.*?)</temperature>",
        "<conditions-icon type=.forecast-NWS. time-layout=.k-p12h-n1[0-9]-1..*?>(.*?)</conditions-icon>",
        "<wordedForecast time-layout=.k-p12h-n1[0-9]-1..*?>(.*?)</wordedForecast>",
        "<data type=.current observations.>.*?<area-description>(.*)</area-description>.*?</location>",
        "<moreWeatherInformation applicable-location=.point1.>http://www.nws.noaa.gov/data/obhistory/(.*).html</moreWeatherInformation>",
        "<data type=.current observations.>.*?<start-valid-time period-name=.current.>(.*)</start-valid-time>",
        "<time-layout time-coordinate=.local. summarization=.12hourly.>.*?<layout-key>k-p12h-n1[0-9]-1</layout-key>(.*?)</time-layout>",
        "<time-layout time-coordinate=.local. summarization=.12hourly.>.*?<layout-key>k-p24h-n[678]-1</layout-key>(.*?)</time-layout>",
        "<time-layout time-coordinate=.local. summarization=.12hourly.>.*?<layout-key>k-p24h-n[678]-2</layout-key>(.*?)</time-layout>",
        "<weather time-layout=.k-p12h-n1[0-9]-1.>.*?<name>.*?</name>(.*)</weather>", // 3 to [0-9] 3 places
        "<hazards time-layout.*?>(.*)</hazards>.*?<wordedF",
        "<data type=.forecast.>.*?<area-description>(.*?)</area-description>",
        "<humidity type=.relative..*?>(.*?)</humidity>"
    };
    const auto rawData = UtilityString::parseXmlExt(regexpList, html);
    result.push_back(rawData[10]);
    result.push_back(get7DayExt(rawData));
    return result;
}

QString UtilityUS::getLocationHtml(const QString& x, const QString& y) {
    return UtilityIO::getHtml("https://forecast.weather.gov/MapClick.php?lat=" + x + "&lon=" + y + "&unit=0&lg=english&FcstType=dwml");
}

QString UtilityUS::get7DayExt(const QStringList& rawData) {
    auto timeP12n13List = QVector<QString>(14);
    const auto forecast = UtilityString::parseXml(rawData[11], "text");
    timeP12n13List = UtilityString::parseColumn(rawData[15], GlobalVariables::utilUsPeriodNamePattern, true);
    timeP12n13List.insert(0, "");
    QString forecastString = "";
    for (auto j : UtilityList::range2(1, forecast.size())) {
        forecastString += timeP12n13List[j];
        forecastString += ": ";
        forecastString += forecast[j];
    }
    return forecastString;
}
