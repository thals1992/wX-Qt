// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYMODELSNSSLWRFINTERFACE_H
#define UTILITYMODELSNSSLWRFINTERFACE_H

#include <QStringList>

class UtilityModelNsslWrfInterface {
public:
    static const QStringList models;
    static const QStringList paramsNsslWrf;
    static const QStringList labelsNsslWrf;
    static const QStringList paramsNsslFv3;
    static const QStringList labelsNsslFv3;
    static const QStringList paramsNsslHrrrv3;
    static const QStringList labelsNsslHrrrv3;
    static const QStringList sectorsLong;
    static const QStringList sectors;
};

#endif  // UTILITYMODELSNSSLWRFINTERFACE_H
