// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "UtilityModelGlcfsInterface.h"

const vector<string> UtilityModelGlcfsInterface::sectors{
    "Lake Superior",
    "Lake Michigan",
    "Lake Huron",
    "Lake Erie",
    "Lake Ontario",
    "All Lakes",
};

const vector<string> UtilityModelGlcfsInterface::params{
    "wv",
    "wn",
    "swt",
    "sfcur",
    "wl",
    "wl1d",
    "cl",
    "at",
};

const vector<string> UtilityModelGlcfsInterface::labels{
    "Wave height",
    "Wind speed",
    "Surface temperature",
    "Surface currents",
    "Water level displacement",
    "Water level displacement 1D",
    "Cloud cover (5 lake view only)",
    "Air temp (5 lake view only)"
};
