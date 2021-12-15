// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SEVEREWARNING_H
#define SEVEREWARNING_H

#include <QStringList>
#include <QVector>
#include "objects/ObjectWarning.h"
#include "radar/PolygonType.h"

class SevereWarning {
public:
    SevereWarning();
    explicit SevereWarning(PolygonType);
    void generateString();
    QString getName() const;
    QString getCount() const;
    QString getShortName() const;
    void download();
    PolygonType type;
    QString text;
    QVector<ObjectWarning> warningList;
};

#endif  // SEVEREWARNING_H
