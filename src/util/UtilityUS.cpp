// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/UtilityUS.h"
#include "common/GlobalVariables.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"

//
// Legacy forecast support
//
vector<string>  UtilityUS::getCurrentConditionsUS(const string& x, const string& y) {
    vector<string> result;
    const auto html = getLocationHtml(x, y);
    const vector<string> regexpList{
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
        "<moreWeatherInformation applicable-location=.point1.>https://www.nws.noaa.gov/data/obhistory/(.*).html</moreWeatherInformation>",
        "<data type=.current observations.>.*?<start-valid-time period-name=.current.>(.*)</start-valid-time>",
        "<time-layout time-coordinate=.local. summarization=.12hourly.>.*?<layout-key>k-p12h-n1[0-9]-1</layout-key>(.*?)</time-layout>",
        "<time-layout time-coordinate=.local. summarization=.12hourly.>.*?<layout-key>k-p24h-n[678]-1</layout-key>(.*?)</time-layout>",
        "<time-layout time-coordinate=.local. summarization=.12hourly.>.*?<layout-key>k-p24h-n[678]-2</layout-key>(.*?)</time-layout>",
        "<weather time-layout=.k-p12h-n1[0-9]-1.>.*?<name>.*?</name>(.*)</weather>",  // 3 to [0-9] 3 places
        "<hazards time-layout.*?>(.*)</hazards>.*?<wordedF",
        "<data type=.forecast.>.*?<area-description>(.*?)</area-description>",
        "<humidity type=.relative..*?>(.*?)</humidity>"
    };
    const auto rawData = UtilityString::parseXmlExt(regexpList, html);
    result.push_back(rawData[10]);
    result.push_back(get7DayExt(rawData));
    return result;
}

string UtilityUS::getLocationHtml(const string& x, const string& y) {
    return UtilityIO::getHtml("https://forecast.weather.gov/MapClick.php?lat=" + x + "&lon=" + y + "&unit=0&lg=english&FcstType=dwml");
}

string UtilityUS::get7DayExt(const vector<string> & rawData) {
    const auto forecast = UtilityString::parseXml(rawData[11], "text");
    auto timeP12n13List = UtilityString::parseColumn(rawData[15], GlobalVariables::utilUsPeriodNamePattern);
    timeP12n13List.insert(timeP12n13List.begin(), "");
    string forecastString;
    for (auto j : range2(1, forecast.size())) {
        forecastString += timeP12n13List[j];
        forecastString += ": ";
        forecastString += forecast[j];
    }
    return forecastString;
}
