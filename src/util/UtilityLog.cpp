// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/UtilityLog.h"
#include <iostream>
#include "objects/ObjectDateTime.h"
#include "objects/WString.h"

void UtilityLog::d(const string& s) {
    // TODO FIXME
    auto timeStringList = WString::split(ObjectDateTime::getCurrentLocalTimeAsString(), " ");
    if (!timeStringList.empty()) {
        std::cout << timeStringList[1] << " " << s << std::endl;
    }
}
