// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTCOLORPALETTELINE_H
#define OBJECTCOLORPALETTELINE_H

#include <QStringList>

class ObjectColorPaletteLine {
public:
    ObjectColorPaletteLine();
    explicit ObjectColorPaletteLine(const QStringList&);
    ObjectColorPaletteLine(int, const QString&, const QString&, const QString&);
    int asInt() const;
    int dbz;
    int red;
    int green;
    int blue;
};

#endif  // OBJECTCOLORPALETTELINE_H
