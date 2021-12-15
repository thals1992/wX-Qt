// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef GLOBALDICTIONARIES_H
#define GLOBALDICTIONARIES_H

#include <QHash>
#include <cstdint>

class GlobalDictionaries {
public:
    static const QHash<QString, QString> nexradProductString;
    static const QHash<QString, int16_t> radarProductStringToShortInt;
};

#endif  // GLOBALDICTIONARIES_H
