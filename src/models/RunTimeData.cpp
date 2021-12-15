// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "models/RunTimeData.h"

RunTimeData::RunTimeData() {
    imageCompleteInt = 0;
}

void RunTimeData::appendListRun(const QString& value) {
    listRun.push_back(value);
}

void RunTimeData::appendListRun(const QStringList& values) {
    listRun += values;
}
