// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYCOLORPALETTE_H
#define UTILITYCOLORPALETTE_H

#include <QStringList>

class UtilityColorPalette {
public:
    static QStringList getColorMapStringFromDisk(int, const QString&);
};

#endif  // UTILITYCOLORPALETTE_H
