// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "nhc/NhcRegionSummary.h"
#include "common/GlobalVariables.h"

NhcRegionSummary::NhcRegionSummary(const NhcOceanEnum& region) {
    if (region == ATL) {
        const vector<string> titlesTmp{
            "Atlantic Tropical Cyclones and Disturbances ",
            "ATL: Two-Day Graphical Tropical Weather Outlook",
            "ATL: Five-Day Graphical Tropical Weather Outlook"};
        const vector<string> urlsTmp{
            GlobalVariables::nwsNhcWebsitePrefix + "/xgtwo/two_atl_0d0.png",
            GlobalVariables::nwsNhcWebsitePrefix + "/xgtwo/two_atl_2d0.png",
            GlobalVariables::nwsNhcWebsitePrefix + "/xgtwo/two_atl_5d0.png"};
        baseUrl = GlobalVariables::nwsNhcWebsitePrefix + "/nhc_at";
        titles = titlesTmp;
        urls = urlsTmp;
    } else if (region == EPAC) {
        const vector<string> titlesTmp{
            "EPAC Tropical Cyclones and Disturbances ",
            "EPAC: Two-Day Graphical Tropical Weather Outlook",
            "EPAC: Five-Day Graphical Tropical Weather Outlook"};
        const vector<string> urlsTmp{
            GlobalVariables::nwsNhcWebsitePrefix + "/xgtwo/two_pac_0d0.png",
            GlobalVariables::nwsNhcWebsitePrefix + "/xgtwo/two_pac_2d0.png",
            GlobalVariables::nwsNhcWebsitePrefix + "/xgtwo/two_pac_5d0.png"};
        baseUrl = GlobalVariables::nwsNhcWebsitePrefix + "/nhc_ep";
        titles = titlesTmp;
        urls = urlsTmp;
    } else if (region == CPAC) {
        const vector<string> titlesTmp{
            "CPAC Tropical Cyclones and Disturbances ",
            "CPAC: Two-Day Graphical Tropical Weather Outlook",
            "CPAC: Five-Day Graphical Tropical Weather Outlook"};
        const vector<string> urlsTmp{
            GlobalVariables::nwsNhcWebsitePrefix + "/xgtwo/two_cpac_0d0.png",
            GlobalVariables::nwsNhcWebsitePrefix + "/xgtwo/two_cpac_2d0.png",
            GlobalVariables::nwsNhcWebsitePrefix + "/xgtwo/two_cpac_5d0.png"};
        baseUrl = "";
        titles = titlesTmp;
        urls = urlsTmp;
    }
}
