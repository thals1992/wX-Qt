// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "vis/UtilityGoesFullDisk.h"

const QStringList UtilityGoesFullDisk::labels = {
    "Meteosat Infrared",
    "Meteosat Visible",
    "Meteosat India Ocean Infrared",
    "Meteosat India Ocean Visible",
    "Himawari-8 Infrared",
    "Himawari-8 IR, Ch. 4",
    "Himawari-8 Water Vapor",
    "Himawari-8 Water Vapor (Blue)",
    "Himawari-8 Visible",
    "Himawari-8 AVN Infrared",
    "Himawari-8 Funktop Infrared",
    "Himawari-8 RBTop Infrared, Ch. 4"
};

const QString UtilityGoesFullDisk::baseUrl = "https://www.goes.noaa.gov";

const QStringList UtilityGoesFullDisk::urls = {
    "https://www.goes.noaa.gov/FULLDISK/GMIR.JPG",
    "https://www.goes.noaa.gov/FULLDISK/GMVS.JPG",
    "https://www.goes.noaa.gov/FULLDISK/GIIR.JPG",
    "https://www.goes.noaa.gov/FULLDISK/GIVS.JPG",
    "https://www.goes.noaa.gov/dimg/jma/fd/rb/10.gif",
    "https://www.goes.noaa.gov/dimg/jma/fd/ir4/10.gif",
    "https://www.goes.noaa.gov/dimg/jma/fd/wv/10.gif",
    "https://www.goes.noaa.gov/dimg/jma/fd/wvblue/10.gif",
    "https://www.goes.noaa.gov/dimg/jma/fd/vis/10.gif",
    "https://www.goes.noaa.gov/dimg/jma/fd/avn/10.gif",
    "https://www.goes.noaa.gov/dimg/jma/fd/ft/10.gif",
    "https://www.goes.noaa.gov/dimg/jma/fd/rbtop/10.gif"
};
