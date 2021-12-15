// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef CITYEXT_H
#define CITYEXT_H

#include <QString>

class CityExt {
public:
    CityExt();
    CityExt(const QString&, float, float);
    QString name;
    float latitude;
    float longitude;
};

#endif  // CITYEXT_H
