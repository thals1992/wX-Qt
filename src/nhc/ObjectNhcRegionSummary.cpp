// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "nhc/ObjectNhcRegionSummary.h"
#include "common/GlobalVariables.h"

ObjectNhcRegionSummary::ObjectNhcRegionSummary(const NhcOceanEnum& region) {
    if (region == NhcOceanEnum::ATL) {
        QStringList titlesTmp = {
            "Atlantic Tropical Cyclones and Disturbances ",
            "ATL: Two-Day Graphical Tropical Weather Outlook",
            "ATL: Five-Day Graphical Tropical Weather Outlook"};
        QStringList urlsTmp = {
            QString(GlobalVariables::nwsNhcWebsitePrefix + "/xgtwo/two_atl_0d0.png"),
            QString(GlobalVariables::nwsNhcWebsitePrefix + "/xgtwo/two_atl_2d0.png"),
            QString(GlobalVariables::nwsNhcWebsitePrefix + "/xgtwo/two_atl_5d0.png")};
        replaceString = "NHC Atlantic Wallet";
        baseUrl = GlobalVariables::nwsNhcWebsitePrefix + "/nhc_at";
        titles = titlesTmp;
        urls = urlsTmp;
    } else if (region == NhcOceanEnum::EPAC) {
        QStringList titlesTmp = {
            "EPAC Tropical Cyclones and Disturbances ",
            "EPAC: Two-Day Graphical Tropical Weather Outlook",
            "EPAC: Five-Day Graphical Tropical Weather Outlook"};
        QStringList urlsTmp = {
            QString(GlobalVariables::nwsNhcWebsitePrefix + "/xgtwo/two_pac_0d0.png"),
            QString(GlobalVariables::nwsNhcWebsitePrefix + "/xgtwo/two_pac_2d0.png"),
            QString(GlobalVariables::nwsNhcWebsitePrefix + "/xgtwo/two_pac_5d0.png")};
        replaceString = "NHC Eastern Pacific Wallet";
        baseUrl = GlobalVariables::nwsNhcWebsitePrefix + "/nhc_ep";
        titles = titlesTmp;
        urls = urlsTmp;
    } else if (region == NhcOceanEnum::CPAC) {
        QStringList titlesTmp = {
            "CPAC Tropical Cyclones and Disturbances ",
            "CPAC: Two-Day Graphical Tropical Weather Outlook",
            "CPAC: Five-Day Graphical Tropical Weather Outlook"};
        QStringList urlsTmp = {
            QString(GlobalVariables::nwsNhcWebsitePrefix + "/xgtwo/two_cpac_0d0.png"),
            QString(GlobalVariables::nwsNhcWebsitePrefix + "/xgtwo/two_cpac_2d0.png"),
            QString(GlobalVariables::nwsNhcWebsitePrefix + "/xgtwo/two_cpac_5d0.png")};
        replaceString = "";
        baseUrl = "";
        titles = titlesTmp;
        urls = urlsTmp;
    }
}
