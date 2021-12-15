// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/UtilityLog.h"
#include <iostream>
#include <QStringList>
#include "util/UtilityTime.h"

void UtilityLog::d(const QString& s) {
    auto timeStringList = UtilityTime::getCurrentLocalTimeAsString().split(" ");
    if (timeStringList.size() > 0) {
        std::cout << timeStringList[1].toStdString() << " " << s.toStdString() << std::endl;
    }
}
