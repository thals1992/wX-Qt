// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCUTILITYSPCMESO_H
#define SPCUTILITYSPCMESO_H

#include <QHash>
#include <QVector>
#include "ui/ObjectMenuTitle.h"

class UtilitySpcMeso {
public:
    static QVector<ObjectMenuTitle> titles;
    static const QString defaultSector;
    static const QStringList favList;
    static const QStringList imgSf;
    static const QStringList products;
    static const QStringList labels;
    static const QStringList paramSurface;
    static const QStringList paramUpperAir;
    static const QStringList paramCape;
    static const QStringList paramComp;
    static const QStringList paramShear;
    static const QStringList productShortList;
    static const QHash<QString, QString> sectorMap;
    static const QHash<QString, QString> sectorMapForTitle;
    static const QStringList sectorCodes;
    static const QStringList sectors;
};

#endif  // SPCUTILITYSPCMESO_H
