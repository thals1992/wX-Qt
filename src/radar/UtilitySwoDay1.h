// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYSWODAY1_H
#define UTILITYSWODAY1_H

#include <QColor>
#include <QHash>
#include <QStringList>
#include <QVector>
#include "objects/DownloadTimer.h"

class UtilitySwoDay1 {
public:
    static DownloadTimer timer;
    static QHash<int, QVector<float>> hashSwo;
    static QVector<QColor> swoPaints;
    static QStringList threatList;
    static void get();
};

#endif  // UTILITYSWODAY1_H
