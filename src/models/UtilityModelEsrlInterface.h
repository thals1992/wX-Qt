// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYMODELESRLINTERFACE_H
#define UTILITYMODELESRLINTERFACE_H

#include <QStringList>

class UtilityModelEsrlInterface {
public:
    static const QStringList models;
    static const QStringList sectorsHrrr;
    static const QStringList sectorsHrrrAk;
    static const QStringList modelHrrrParams;
    static const QStringList modelHrrrLabels;
    static const QStringList sectorsRap;
    static const QStringList modelRapParams;
    static const QStringList modelRapLabels;
};

#endif  // UTILITYMODELESRLINTERFACE_H
