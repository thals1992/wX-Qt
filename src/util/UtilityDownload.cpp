// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/UtilityDownload.h"
#include <iostream>
#include "common/GlobalVariables.h"
#include "misc/UtilityHourly.h"
#include "radar/UtilityAwcRadarMosaic.h"
#include "settings/Location.h"
#include "util/To.h"
#include "util/UtilityIO.h"
#include "util/UtilityString.h"
#include "vis/UtilityGoes.h"

QString UtilityDownload::getTextProduct(const QString& productOriginal) {
    if (productOriginal.startsWith("http")) {
        return UtilityIO::getHtml(productOriginal);
    }
    QString text;
    auto product = productOriginal.toUpper();
    QString html;
    QString url;
    if (product == "HOURLY") {
        text =  UtilityHourly::get(Location::currentLocationIndex);
    } else if (product == "WFO_TEXT") {
        text = getTextProduct("AFD" + Location::wfo());
    } else if (product == "SWPC3DAY") {
        text = UtilityIO::getHtml(GlobalVariables::nwsSwpcWebSitePrefix + "/text/3-day-forecast.txt");
    } else if (product == "SWPC27DAY") {
        text = UtilityIO::getHtml(GlobalVariables::nwsSwpcWebSitePrefix + "/text/27-day-outlook.txt");
    } else if (product == "SWPCWWA") {
        text = UtilityIO::getHtml(GlobalVariables::nwsSwpcWebSitePrefix + "/text/advisory-outlook.txt");
    } else if (product == "SWPCHIGH") {
        text = UtilityIO::getHtml(GlobalVariables::nwsSwpcWebSitePrefix + "/text/weekly.txt");
    } else if (product == "SWPCDISC") {
        text = UtilityIO::getHtml(GlobalVariables::nwsSwpcWebSitePrefix + "/text/discussion.txt");
    } else if (product == "SWPC3DAYGEO") {
        text = UtilityIO::getHtml(GlobalVariables::nwsSwpcWebSitePrefix + "/text/3-day-geomag-forecast.txt");
    } else if (product.contains("MIATCP") || product.contains("MIATCM") || product.contains("MIATCD") || product.contains("MIAPWS") || product.contains("MIAHS")) {
        url = "https://www.nhc.noaa.gov/text/" + product + ".shtml";
        text = UtilityIO::getHtml(url);
        text = UtilityString::parse(text, GlobalVariables::pre2Pattern);
        text = UtilityString::removeHtml(text);
    } else if (product.startsWith("MIAT") || product == "HFOTWOCP") {
        text = UtilityIO::getHtml("https://www.nhc.noaa.gov/ftp/pub/forecasts/discussion/" + product);
    } else if (product.contains("SPCMCD")) {
        auto no = product.right(4);
        url = GlobalVariables::nwsSPCwebsitePrefix + "/products/md/md" + no + ".html";
        text = UtilityIO::getHtml(url);
        text = UtilityString::parse(text, GlobalVariables::pre2Pattern);
    } else if (product.contains("WPCMPD")) {
        auto no = product.right(4);
        url = GlobalVariables::nwsWPCwebsitePrefix + "/metwatch/metwatch_mpd_multi.php?md=" + no;
        text = UtilityIO::getHtml(url);
        text = UtilityString::parse(text, GlobalVariables::pre2Pattern);
    } else if (product.contains("SPCWAT")) {
        auto no = product.right(4);
        url = GlobalVariables::nwsSPCwebsitePrefix + "/products/watch/ww" + no + ".html";
        text = UtilityIO::getHtml(url);
        text = UtilityString::parse(text, GlobalVariables::pre2Pattern);
    } else if (product.startsWith("SWOD")) {
        auto day = product.right(1);
        if (product == "SWOD48") {
            url = GlobalVariables::nwsSPCwebsitePrefix + "/products/exper/day4-8/";
        } else {
            url = GlobalVariables::nwsSPCwebsitePrefix + "/products/outlook/day" + day + "otlk.html";
        }
        html = UtilityIO::getHtml(url);
        text = UtilityString::extractPreLsr(html);
        text = UtilityString::removeHtml(text);
    } else if (product == "PMDSPD" || product == "PMDEPD" || product == "PMDHMD" || product == "PMDHI" || product == "PMDAK" || product == "QPFERD" || product == "QPFHSD") {
        url = GlobalVariables::nwsWPCwebsitePrefix + "/discussions/hpcdiscussions.php?disc=" + product.toLower();
        html = UtilityIO::getHtml(url);
        text = UtilityString::extractPreLsr(html);
        text = UtilityString::removeHtml(text);
    } else if (product == "PMDSA") {
        url = GlobalVariables::nwsWPCwebsitePrefix + "/discussions/hpcdiscussions.php?disc=fxsa21";
        html = UtilityIO::getHtml(url);
        text = UtilityString::extractPreLsr(html);
        text = UtilityString::removeHtml(text);
    } else if (product == "PMDCA") {
        url = GlobalVariables::nwsWPCwebsitePrefix + "/discussions/hpcdiscussions.php?disc=fxca20";
        html = UtilityIO::getHtml(url);
        text = UtilityString::extractPreLsr(html);
        text = UtilityString::removeHtml(text);
    } else if (product == "PMDMRD") {
        url = GlobalVariables::tgftpSitePrefix + "/data/raw/fx/fxus06.kwbc.pmd.mrd.txt";
        text = UtilityIO::getHtml(url);
    } else if (product.startsWith("FXCN01")) {
        url = "https://collaboration.cmc.ec.gc.ca/cmc/cmop/FXCN/";
        text = UtilityIO::getHtml(url);
        auto dateList = UtilityString::parseColumn(text, "href=\"([0-9]{8})/\"");
        auto dateString = dateList.back();
        auto daysAndRegion = product.replace("FXCN01_", "").toLower();
        url = "https://collaboration.cmc.ec.gc.ca/cmc/cmop/FXCN/" + dateString + "/fx_" + daysAndRegion + "_" + dateString + "00.html";
        text = UtilityIO::getHtml(url);
        text = UtilityString::removeHtml(text).replace(GlobalVariables::newline + GlobalVariables::newline, GlobalVariables::newline);
    } else if (product == "PMDTHR") {
        url = GlobalVariables::nwsCPCNcepWebsitePrefix + "/products/predictions/threats/threats.php";
        html = UtilityIO::getHtml(url);
        text = UtilityString::parse(html, "<div id=\"discDiv\">(.*?)</div>").replace("<br>", GlobalVariables::newline);
        text = UtilityString::removeHtml(text);
    } else if ("PMD30D" == product) {
        url = "https://tgftp.nws.noaa.gov/data/raw/fx/fxus07.kwbc.pmd.30d.txt";
        text = UtilityIO::getHtml(url);
    } else if ("PMD90D" == product) {
        url = "https://tgftp.nws.noaa.gov/data/raw/fx/fxus05.kwbc.pmd.90d.txt";
        text = UtilityIO::getHtml(url);
    } else if ("PMDHCO" == product) {
        url = "https://tgftp.nws.noaa.gov/data/raw/fx/fxhw40.kwbc.pmd.hco.txt";
        text = UtilityIO::getHtml(url);
    } else if ("USHZD37" == product) {
        url = "https://www.wpc.ncep.noaa.gov/threats/threats.php";
        html = UtilityIO::getHtml(url);
        text = UtilityString::parse(html, "<div class=.haztext.>(.*?)</div>");
        text = text.replace("<br>", "");
    } else if (product.startsWith("SCCNS")) {
        url = GlobalVariables::nwsWPCwebsitePrefix + "/discussions/nfd" + product.toLower().replace("ns", "") + ".html";
        text = UtilityIO::getHtml(url);
        text = UtilityString::extractPreLsr(text);
        text = UtilityString::removeHtml(text);
    } else if (product == "QPF94E") {
        url = "https://www.wpc.ncep.noaa.gov/qpf/ero.php?opt=curr&day=1";
        text = UtilityIO::getHtml(url);
        text = UtilityString::extractPreLsr(text);
        text = UtilityString::removeHtml(text);
    } else if (product == "QPF98E") {
        url = "https://www.wpc.ncep.noaa.gov/qpf/ero.php?opt=curr&day=2";
        text = UtilityIO::getHtml(url);
        text = UtilityString::extractPreLsr(text);
        text = UtilityString::removeHtml(text);
    } else if (product == "QPF99E") {
        url = "https://www.wpc.ncep.noaa.gov/qpf/ero.php?opt=curr&day=3";
        text = UtilityIO::getHtml(url);
        text = UtilityString::extractPreLsr(text);
        text = UtilityString::removeHtml(text);
    } else if (product == "FWDDY1") {
        url = GlobalVariables::nwsSPCwebsitePrefix + "/products/fire_wx/fwdy1.html";
        text = UtilityIO::getHtml(url);
        text = UtilityString::extractPreLsr(text);
        text = UtilityString::removeHtml(text);
    } else if (product == "FWDDY2") {
        url = GlobalVariables::nwsSPCwebsitePrefix + "/products/fire_wx/fwdy2.html";
        text = UtilityIO::getHtml(url);
        text = UtilityString::extractPreLsr(text);
        text = UtilityString::removeHtml(text);
    } else if (product == "FWDDY38") {
        url = GlobalVariables::nwsSPCwebsitePrefix + "/products/exper/fire_wx/";
        text = UtilityIO::getHtml(url);
        text = UtilityString::extractPreLsr(text);
        text = UtilityString::removeHtml(text);
    } else if (product.startsWith("NFD")) {
        text = UtilityIO::getHtml(GlobalVariables::nwsOpcWebsitePrefix + "/mobile/mobile_product.php?id=" + product.toUpper());
        text = UtilityString::removeHtml(text);
    } else if (product == ("MIMATN")) {
        text = UtilityIO::getHtml(GlobalVariables::nwsOpcWebsitePrefix + "/mobile/mobile_product.php?id=" + "NFDMIMATN");
        text = UtilityString::removeHtml(text);
    } else if (product == "FOCN45") {
        text = UtilityIO::getHtml(GlobalVariables::tgftpSitePrefix + "/data/raw/fo/focn45.cwwg..txt");
    } else if (product.startsWith("VFD")) {
        QString t2;
        text = UtilityIO::getHtml(GlobalVariables::nwsAWCwebsitePrefix + "/fcstdisc/data?cwa=K" + t2);
        text = UtilityString::parse(text, "<!-- raw data starts -->(.*?)<!-- raw data ends -->");
    } else if (product.startsWith("AWCN")) {
        text = UtilityIO::getHtml(GlobalVariables::tgftpSitePrefix + "/data/raw/aw/" + product.toLower() + ".cwwg..txt");
    } else if (product.startsWith("OFF") || product == "UVICAC" || product == "RWRMX" || product.startsWith("TPT")) {
        QString productType = "";
        QString site = "";
        if (product.size() == 5) {
            productType = UtilityString::substring(product, 0, 3);
            site = UtilityString::substring(product, 3, 5);
        } else {
            productType = UtilityString::substring(product, 0, 3);
            site = UtilityString::substring(product, 3, 6);
        }
        url = "https://forecast.weather.gov/product.php?site=NWS&issuedby=" + site + "&product=" + productType + "&format=txt&version=1&glossary=0";
        html = UtilityIO::getHtml(url);
        text = UtilityString::extractPreLsr(html);
    } else if (product.startsWith("GLF")) {
        auto productFull = product;
        product = UtilityString::substring(productFull, 0, 3);
        auto site = productFull.right(2).replace("%", "");
        url = "https://forecast.weather.gov/product.php?site=NWS&issuedby=" + site + "&product=" + product + "&format=txt&version=1&glossary=0";
        html = UtilityIO::getHtml(url);
        text = UtilityString::extractPreLsr(html);
    } else if (product == "SWOMCD") {
        url = "https://forecast.weather.gov/product.php?site=NWS&issuedby=MCD&product=SWO&format=txt&version=1&glossary=0";
        html = UtilityIO::getHtml(url);
        text = UtilityString::extractPreLsr(html);
    } else {
        auto t1 = product.left(3);
        auto t2 = product.right(3).replace("%", "");
        QString urlToGet = "https://forecast.weather.gov/product.php?site=" + t2 + "&issuedby=" + t2 + "&product=" + t1 + "&format=txt&version=1&glossary=0";
        auto prodHtmlFuture = UtilityIO::getHtml(urlToGet);
        text = UtilityString::extractPreLsr(prodHtmlFuture);
    }
    return text.trimmed();
}

QString UtilityDownload::getImageProduct(const QString& product) {
    QString url;
    if (product == "STRPT") {
        url = GlobalVariables::nwsSPCwebsitePrefix + "/climo/reports/today.gif";
    } else if (product == "USWARN") {
        url = "https://forecast.weather.gov/wwamap/png/US.png";
    } else if (product == "VISIBLE_SATELLITE") {
        QString sector = UtilityGoes::getNearestGoesLocation(Location::getLatLonCurrent());
        url = UtilityGoes::getImage("GEOCOLOR", sector);
    } else if (product == "ANALYSIS_RADAR_AND_WARNINGS") {
        url = GlobalVariables::nwsWPCwebsitePrefix + "/images/wwd/radnat/NATRAD_24.gif";
    } else if (product == "RADAR_MOSAIC") {
        auto radarMosaicSector = UtilityAwcRadarMosaic::getNearestMosaic(Location::getLatLonCurrent());
        url = UtilityAwcRadarMosaic::get("rad_rala", radarMosaicSector);
    }
    return url;
}

QString UtilityDownload::getTextProductWithVersion(const QString& product, int version) {
    const auto prodLocal = product.toUpper();
    const auto t1 = prodLocal.left(3);
    const auto t2 = prodLocal.right(3);
    const auto url = "https://forecast.weather.gov/product.php?site=NWS&product=" + t1 + "&issuedby=" + t2 + "&version=" + To::String(version);
    auto text = UtilityIO::getHtml(url);
    text = UtilityString::parse(text, GlobalVariables::prePattern);
    text = text.replace("Graphics available at <a href=\"/basicwx/basicwx_wbg.php\"><u>www.wpc.ncep.noaa.gov/basicwx/basicwx_wbg.php</u></a>", "");
    text = text.replace("^<br>", "");
    return text;
}

QString UtilityDownload::getRadarStatusMessage(const QString& radarSite) {
    QString ridSmall;
    if (radarSite.size() == 4) {
        ridSmall = radarSite.mid(1);
    } else {
        ridSmall = radarSite;
    }
    const auto prodLocal = "FTM" + ridSmall.toUpper();
    const auto t1 = prodLocal.left(3);
    const auto t2 = prodLocal.right(3);
    QString url = "https://forecast.weather.gov/product.php?site=NWS&issuedby=" + t2 + "&product=" + t1 + "&format=CI&version=2&glossary=0";
    auto text = UtilityIO::getHtml(url);
    text = UtilityString::parse(text, GlobalVariables::prePattern);
    text = text.replace("^<br>", "");
    return text;
}
