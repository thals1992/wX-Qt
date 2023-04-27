// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "DownloadText.h"
#include "../common/GlobalVariables.h"
#include "../misc/UtilityHourly.h"
#include "../objects/WString.h"
#include "../radar/UtilityNwsRadarMosaic.h"
#include "../settings/Location.h"
#include "../vis/UtilityGoes.h"
#include "To.h"
#include "UtilityIO.h"
#include "UtilityString.h"

bool DownloadText::useNwsApi{false};

string DownloadText::byProduct(const string& produ) {
    if (WString::startsWith(produ, "http")) {
        return UtilityIO::getHtml(produ);
    }
    string text;
    string no;
    string textUrl;
    auto prod = WString::toUpper(produ);
    if (prod == "AFDLOC") {
        const auto tmp = Location::office();
        text = byProduct("afd" + WString::toLower(tmp));
    } else if (prod == "HWOLOC") {
        const auto tmp = Location::office();
        text = byProduct("hwo" + WString::toLower(tmp));
    } else if (prod == "WFO_TEXT") {
        text = DownloadText::byProduct("AFD" + Location::office());
    } else if (prod == "HOURLY") {
        text = UtilityHourly::get(Location::getCurrentLocation());
    } else if (prod == "SWPC3DAY") {
        text = UtilityIO::getHtml("https://services.swpc.noaa.gov/text/3-day-forecast.txt");
    } else if (prod == "SWPC27DAY") {
        text = UtilityIO::getHtml("https://services.swpc.noaa.gov/text/27-day-outlook.txt");
    } else if (prod == "SWPCWWA") {
        text = UtilityIO::getHtml("https://services.swpc.noaa.gov/text/advisory-outlook.txt");
    } else if (prod == "SWPCHIGH") {
        text = UtilityIO::getHtml("https://services.swpc.noaa.gov/text/weekly.txt");
    } else if (prod == "SWPCDISC") {
        text = UtilityIO::getHtml("https://services.swpc.noaa.gov/text/discussion.txt");
    } else if (prod == "SWPC3DAYGEO") {
        text = UtilityIO::getHtml("https://services.swpc.noaa.gov/text/3-day-geomag-forecast.txt");
    } else if (WString::contains(prod, "MIAPWS") || WString::contains(prod, "MIAHS") || WString::contains(prod, "MIATCP") || WString::contains(prod, "MIATCM") || WString::contains(prod, "HFOTWOCP")) {
        textUrl = GlobalVariables::nwsNhcWebsitePrefix + "/text/" + prod + ".shtml";
        text = UtilityIO::getHtml(textUrl);
        text = UtilityString::extractPreLsr(text);
    } else if (WString::contains(prod, "MIAT")) {
        auto url = GlobalVariables::nwsNhcWebsitePrefix + "/ftp/pub/forecasts/discussion/" + prod;
        text = UtilityIO::getHtml(url);
    } else if (WString::contains(prod, "SPCMCD")) {
        no = WString::replace(prod, "SPCMCD", "");
        textUrl = GlobalVariables::nwsSPCwebsitePrefix + "/products/md/md" + no + ".html";
        text = UtilityIO::getHtml(textUrl);
        text = UtilityString::parseNwsPre(text);
        text = UtilityString::removeHtml(text);
    } else if (WString::contains(prod, "SPCWAT")) {
        no = WString::replace(prod, "SPCWAT", "");
        textUrl = GlobalVariables::nwsSPCwebsitePrefix + "/products/watch/ww" + no + ".html";
        text = UtilityIO::getHtml(textUrl);
        text = UtilityString::parseNwsPre(text);
        text = UtilityString::removeHtml(text);
        // text = UtilityString::parse(text, GlobalVariables::pre2Pattern);
    } else if (WString::contains(prod, "WPCMPD")) {
        no = WString::replace(prod, "WPCMPD", "");
        textUrl = GlobalVariables::nwsWPCwebsitePrefix + "/metwatch/metwatch_mpd_multi.php?md=" + no;
        text = UtilityIO::getHtml(textUrl);
        text = UtilityString::parseNwsPre(text);
    } else if (prod == "QPF94E") {
        text = string("https://www.wpc.Ncep.noaa.gov/qpf/ero.php?opt=curr&day=") + "1";
        text = UtilityIO::getHtml(text);
        text = UtilityString::extractPreLsr(text);
        text = UtilityString::removeHtml(text);
    } else if (prod == "QPF98E") {
        text = string("https://www.wpc.Ncep.noaa.gov/qpf/ero.php?opt=curr&day=") + "2";
        text = UtilityIO::getHtml(text);
        text = UtilityString::extractPreLsr(text);
        text = UtilityString::removeHtml(text);
    } else if (prod == "QPF99E") {
        text = string("https://www.wpc.Ncep.noaa.gov/qpf/ero.php?opt=curr&day=") + "3";
        text = UtilityIO::getHtml(text);
        text = UtilityString::extractPreLsr(text);
        text = UtilityString::removeHtml(text);
    } else if (WString::contains(prod, "FWDDY1")) {
        text = GlobalVariables::nwsSPCwebsitePrefix + "/products/fire_wx/fwdy1.html";
        text = UtilityIO::getHtml(text);
        text = UtilityString::extractPreLsr(text);
        text = UtilityString::removeHtml(text);
    } else if (WString::contains(prod, "FWDDY2")) {
        text = GlobalVariables::nwsSPCwebsitePrefix + "/products/fire_wx/fwdy2.html";
        //  text = url.getHtml();
        //  text = text.extractPre().removeLineBreaks().removeHtml().removeDuplicateSpaces();
        text = UtilityIO::getHtml(text);
        text = UtilityString::extractPreLsr(text);
        text = UtilityString::removeHtml(text);
    } else if (WString::contains(prod, "FWDDY38")) {
        text = GlobalVariables::nwsSPCwebsitePrefix + "/products/exper/fire_wx/";
        text = UtilityIO::getHtml(text);
        text = UtilityString::extractPreLsr(text);
        text = UtilityString::removeHtml(text);
    } else {
        // exmaple URL https://api.weather.gov/products/types/AFD/locations/DTX
        // product
        const auto t1 = UtilityString::substring(prod, 0, 3);
        // site
        auto t2 = UtilityString::substring(prod, 3, 6);
        t2 = WString::replace(t2, "%", "");
        // Feb 8 2020 Sat
        // The NWS API for text products has been unstable Since Wed Feb 5
        // resorting to alternatives
        if (useNwsApi) {
            const auto urlToGet = GlobalVariables::nwsApiUrl + "/products/types/" + t1 + "/locations/" + t2;
            //  print(urlToGet);
            const auto htmlFuture = UtilityIO::getHtml(urlToGet);
            const auto urlProd = GlobalVariables::nwsApiUrl + string("/products/") + UtilityString::parse(htmlFuture, "\"id\": \"(.*?)\"");
            const auto prodHtmlFuture = UtilityIO::getHtml(urlProd);
            text = UtilityString::parse(prodHtmlFuture, "\"productText\": \"(.*?)\\$");
            if (!WString::startsWith(prod, "RTP")) {
                text = WString::replace(text, "\\n\\n", "\n");
                text = WString::replace(text, "\\n", " ");
            } else {
                text = WString::replace(text, "\\n", "\n");
            }
        } else {
            if (prod == "SWODY1") {
                const string url = "https://www.spc.noaa.gov/products/outlook/day1otlk.html";
                const auto html = UtilityIO::getHtml(url);
                text = UtilityString::parseNwsPre(html);
                text = UtilityString::removeHtml(text);
                return text;
            } else if (prod == "SWODY2") {
                const string url = "https://www.spc.noaa.gov/products/outlook/day2otlk.html";
                const auto html = UtilityIO::getHtml(url);
                text = UtilityString::parseNwsPre(html);
                text = UtilityString::removeHtml(text);
                return text;
            } else if (prod == "SWODY3") {
                const string url = "https://www.spc.noaa.gov/products/outlook/day3otlk.html";
                const auto html = UtilityIO::getHtml(url);
                text = UtilityString::parseNwsPre(html);
                text = UtilityString::removeHtml(text);
                return text;
            } else if (prod == "SWOD48") {
                const string url = "https://www.spc.noaa.gov/products/exper/day4-8/";
                const auto html = UtilityIO::getHtml(url);
                text = UtilityString::parseNwsPre(html);
                text = UtilityString::removeHtml(text);
                return text;
            } else if (prod == "PMDSPD" || prod == "PMDEPD" || prod == "PMDHMD" || prod == "PMDHI" || prod == "PMDAK" || prod == "QPFERD" || prod == "QPFHSD") {
                const string url = "https://www.wpc.ncep.noaa.gov/discussions/hpcdiscussions.php?disc=" + WString::toLower(prod);
                const auto html = UtilityIO::getHtml(url);
                text = UtilityString::parseNwsPre(html);
                text = UtilityString::removeHtml(text);
                return text;
            } else if (prod == "QPFHSD") {
                const string url = "https://www.wpc.ncep.noaa.gov/discussions/hpcdiscussions.php?disc=fxsa20";
                const auto html = UtilityIO::getHtml(url);
                text = UtilityString::parseNwsPre(html);
                return text;
            } else if (prod == "PMDCA") {
                const string url = "https://www.wpc.ncep.noaa.gov/discussions/hpcdiscussions.php?disc=fxca20";
                const auto html = UtilityIO::getHtml(url);
                text = UtilityString::parseNwsPre(html);
                return text;
            }
            const auto url = "https://forecast.weather.gov/product.php?site=" + t2 + "&issuedby=" + t2 + "&product=" + t1 + "&format=txt&version=1&glossary=0";
            const auto html = UtilityIO::getHtml(url);
            text = UtilityString::extractPreLsr(html);
        }
    }
    return text;
}

string DownloadText::getTextProductWithVersion(const string& product, int version) {
    const auto prodLocal = WString::toUpper(product);
    const auto t1 = UtilityString::substring(prodLocal, 0, 3);
    const auto t2 = UtilityString::substring(prodLocal, 3, 6);
    const auto textUrl = "https://forecast.weather.gov/product.php?site=NWS&product=" + t1 + "&issuedby=" + t2 + "&version=" + To::string(version);
    auto text = UtilityIO::getHtml(textUrl);
    text = UtilityString::extractPreLsr(text);
    text = WString::replace(text, "Graphics available at <a href=\"/basicwx/basicwxwbg.php\"><u>www.wpc.ncep.noaa.gov/basicwx/basicwxwbg.php</u></a>", "");
    return text;
}

string DownloadText::getRadarStatusMessage(const string& radarSite) {
    string ridSmall;
    if (radarSite.size() == 4) {
        ridSmall = UtilityString::substring(radarSite, 1);
    } else {
        ridSmall = radarSite;
    }
    const auto prodLocal = "FTM" + WString::toUpper(ridSmall);
    const auto t1 = UtilityString::substring(prodLocal, 0, 3);
    const auto t2 = UtilityString::substring(prodLocal, 3);
    const auto url = "https://forecast.weather.gov/product.php?site=NWS&issuedby=" + t2 + "&product=" + t1 + "&format=CI&version=2&glossary=0";
    auto text = UtilityIO::getHtml(url);
    text = UtilityString::extractPreLsr(text);
//    text = UtilityString::parse(text, GlobalVariables::prePattern);
    text = WString::replace(text, "^<br>", "");
    return text;
}
