// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SEVERENOTICE_H
#define SEVERENOTICE_H

#include <QStringList>
#include "radar/PolygonType.h"

class SevereNotice {
public:
    SevereNotice();
    explicit SevereNotice(PolygonType);
    void getBitmaps();
    QString getShortName() const;
    QString getCount() const;
    PolygonType type;
    QStringList urls;
};

#endif  // SEVERENOTICE_H
