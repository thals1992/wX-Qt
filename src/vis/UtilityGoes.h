// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef VISUTILITYGOES_H
#define VISUTILITYGOES_H

#include <QHash>
#include <QStringList>
#include "objects/LatLon.h"

class UtilityGoes {
public:
    static const QHash<QString, QString> sizeMap;
    static QString getImageSize(const QString&);
    static QString getImageGoesFloater(QString, QString);
    static QString getImage(const QString&, const QString&);
    static QStringList getAnimation(const QString&, const QString&, int);
    static QStringList getAnimationGoesFloater(const QString&, const QString&, int);
    static const QStringList sectors;
    static const QStringList sectorsWithAdditional;
    static const QStringList sectorsInGoes17;
    static const QStringList labels;
    static const QStringList codes;
    static QHash<QString, LatLon> sectorToLatLon;
    static QString getNearestGoesLocation(const LatLon&);
};

#endif  // VISUTILITYGOES_H
