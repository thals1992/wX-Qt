// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "nhc/UtilityNhc.h"

const QStringList UtilityNhc::urlEnds = {
    "_5day_cone_with_line_and_wind_sm2.png",
    "_key_messages.png",
    // "WPCQPF_sm2.gif",
    "_earliest_reasonable_toa_34_sm2.png",
    "_most_likely_toa_34_sm2.png",
    "_wind_probs_34_F120_sm2.png",
    "_wind_probs_50_F120_sm2.png",
    "_wind_probs_64_F120_sm2.png"
};

const QStringList UtilityNhc::stormtextProducts = {
    "MIATCP: Public Advisory",
    "MIATCM: Forecast Advisory",
    "MIATCD: Forecast Discussion",
    "MIAPWS: Wind Speed Probababilities"
};

const QStringList UtilityNhc::textProductCodes = {
    "MIATWOAT",
    "MIATWDAT",
    "MIATWSAT",
    "MIATWOEP",
    "MIATWDEP",
    "MIATWSEP",
    "HFOTWOCP"
};

const QStringList UtilityNhc::textProductLabels = {
    "ATL Tropical Weather Outlook",
    "ATL Tropical Weather Discussion",
    "ATL Monthly Tropical Summary",
    "EPAC Tropical Weather Outlook",
    "EPAC Tropical Weather Discussion",
    "EPAC Monthly Tropical Summary",
    "CPAC Tropical Weather Outlook"
};

const QStringList UtilityNhc::imageType = {
    "vis: Visible",
    "wv: Water Vapor",
    "swir: Shortwave IR",
    "ir: Unenhanced IR",
    "avn: AVN",
    "bd: Dvorak",
    "jsl: JSL",
    "rgb: RGB",
    "ft: Funktop",
    "rb: Rainbow"
};

const QStringList UtilityNhc::imageTitles = {
    "EPAC Daily Analysis",
    "ATL Daily Analysis",
    "EPAC 7-Day Analysis",
    "ATL 7-Day Analysis",
    "EPAC SST Anomaly",
    "ATL SST Anomaly"
};

const QStringList UtilityNhc::imageUrls = {
    "https://www.ssd.noaa.gov/PS/TROP/DATA/RT/SST/PAC/20.jpg",
    "https://www.ssd.noaa.gov/PS/TROP/DATA/RT/SST/ATL/20.jpg",
    "https://www.nhc.noaa.gov/tafb/pac_anal.gif",
    "https://www.nhc.noaa.gov/tafb/atl_anal.gif",
    "https://www.nhc.noaa.gov/tafb/pac_anom.gif",
    "https://www.nhc.noaa.gov/tafb/atl_anom.gif"
};
