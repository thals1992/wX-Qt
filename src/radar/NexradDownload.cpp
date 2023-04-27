// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/NexradDownload.h"
#include "common/GlobalDictionaries.h"
#include "common/GlobalVariables.h"
#include "objects/DownloadParallel.h"
#include "objects/WString.h"
#include "radar/NexradUtil.h"
#include "util/To.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"

const string NexradDownload::pattern1{">(sn.[0-9]{4})</a>"};
const string NexradDownload::pattern2{".*?([0-9]{2}-[A-Za-z]{3}-[0-9]{4} [0-9]{2}:[0-9]{2}).*?"};
const string NexradDownload::nwsRadarPub{"https://tgftp.nws.noaa.gov/"};
const vector<string> NexradDownload::pacRids{"HKI", "HMO", "HKM", "HWA", "APD", "ACG", "AIH", "AHG", "AKC", "ABC", "AEC", "GUA"};

string NexradDownload::getRidPrefix(const string& radarSite, bool isTdwr) {
    if (isTdwr) {
        return "";
    } else {
        if (radarSite == "JUA") {
            return "t";
        } else if (contains(pacRids, radarSite)) {
            return "p";
        } else {
            return "k";
        }
    }
}

string NexradDownload::getRadarDirectoryUrl(const string& radarSite, const string& product, const string& ridPrefix) {
    const auto& productString = GlobalDictionaries::nexradProductString.at(product);
    return GlobalVariables::tgftpSitePrefix + "/SL.us008001/DF.of/DC.radar/" + productString + "/SI." + ridPrefix + WString::toLower(radarSite) + "/";
}

string NexradDownload::getRadarFileUrl(const string& radarSite, const string& product, bool isTdwr) {
    const auto ridPrefix = getRidPrefix(radarSite, isTdwr);
    const auto& productString = GlobalDictionaries::nexradProductString.at(product);
    return nwsRadarPub + "SL.us008001/DF.of/DC.radar/" + productString + "/SI." + ridPrefix + WString::toLower(radarSite) + "/sn.last";
}

void NexradDownload::getRadarFilesForAnimation(QWidget * parent, int frameCount, const string& product, const string& radarSite, FileStorage * fileStorage) {
    const auto ridPrefix = getRidPrefix(radarSite, NexradUtil::isProductTdwr(product));
    vector<string> listOfFiles;
    auto html = UtilityIO::getHtml(getRadarDirectoryUrl(radarSite, product, ridPrefix));
    auto snFiles = UtilityString::parseColumn(html, pattern1);
    auto snDates = UtilityString::parseColumn(html, pattern2);
    if (snDates.empty()) {
        html = UtilityIO::getHtml(getRadarDirectoryUrl(radarSite, product, ridPrefix));
        snFiles = UtilityString::parseColumn(html, pattern1);
        snDates = UtilityString::parseColumn(html, pattern2);
    }
    string mostRecentSn;
    const auto mostRecentTime = snDates.back();
    for (auto index : range(snDates.size() - 1)) {
        if (snDates[index] == mostRecentTime) {
            mostRecentSn = snFiles[index];
        }
    }
    const auto seq = To::Int(WString::replace(mostRecentSn, "sn.", ""));
    auto index = seq - frameCount + 1;
    for ([[maybe_unused]] auto unused : range(frameCount)) {
        int tmpK = index;
        if (tmpK < 0) {
            tmpK += 251;
        }
        listOfFiles.push_back("sn." + To::stringPadLeftZeros(tmpK, 4));
        index += 1;
    }
    vector<string> urlList;
    for (auto i : range(frameCount)) {
        urlList.push_back(getRadarDirectoryUrl(radarSite, product, ridPrefix) + listOfFiles[i]);
    }
    DownloadParallel{parent, fileStorage, urlList};
}
