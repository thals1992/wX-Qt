// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "nhc/NhcStormDetails.h"
#include "objects/WString.h"
#include "nhc/UtilityNhc.h"
#include "util/UtilityIO.h"
#include "util/UtilityString.h"

NhcStormDetails::NhcStormDetails(
    const string& name,
    const string& movementDir,
    const string& movementSpeed,
    const string& pressure,
    const string& binNumber,
    const string& stormId,
    [[maybe_unused]] const string& lastUpdate,
    const string& classification,
    const string& lat,
    const string& lon,
    const string& intensity,
    const string& status)
    : name{ name }
    , movementDir{ movementDir }
    , movementSpeed{ movementSpeed }
    , pressure{ pressure }
    , binNumber{ binNumber }
    , stormId{ stormId }
    , classification{ classification }
    , lat{ lat }
    , lon{ lon }
    , intensity{ intensity }
    , status{ status }
    , center{ lat + " " + lon }
    , goesUrl{ "https://cdn.star.nesdis.noaa.gov/FLOATER/data/" + WString::toUpper(stormId) + "/GEOCOLOR/latest.jpg" }
    , movement{ movementDir + " at " + movementSpeed + " mph" }
    , modBinNumber{ WString::replace(WString::toUpper(UtilityString::substring(stormId, 0, 4)), "AL", "AT") }
    , baseUrl{ "https://www.nhc.noaa.gov/storm_graphics/" + modBinNumber + "/" + WString::toUpper(stormId) }
    , coneBytes{ UtilityIO::downloadAsByteArray(baseUrl + UtilityNhc::urlEnds[0]) }
{}

string NhcStormDetails::getUpdateTime() const {
    auto lastUpdateLocal = lastUpdate;
    lastUpdateLocal = WString::replace(lastUpdateLocal, "T", " ");
    lastUpdateLocal = WString::replace(lastUpdateLocal, ":00.000Z", "Z");
    return lastUpdateLocal;
}

string NhcStormDetails::forTopHeader() const {
    return movement + ", " + pressure + " mb, " + intensity + " mph";
}
