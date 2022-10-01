// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "nhc/UtilityNhc.h"

const vector<string> UtilityNhc::urlEnds{
    "_5day_cone_with_line_and_wind_sm2.png",
    "_key_messages.png",
    // "WPCQPF_sm2.gif",
    "_earliest_reasonable_toa_34_sm2.png",
    "_most_likely_toa_34_sm2.png",
    "_wind_probs_34_F120_sm2.png",
    "_wind_probs_50_F120_sm2.png",
    "_wind_probs_64_F120_sm2.png"
};

const vector<string> UtilityNhc::stormTextProducts{
    "MIATCP: Public Advisory",
    "MIATCM: Forecast Advisory",
    "MIATCD: Forecast Discussion",
    "MIAPWS: Wind Speed Probabilities"
};
