// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTWARNING_H
#define OBJECTWARNING_H

#include "objects/LatLon.h"

class ObjectWarning {
public:
    ObjectWarning();
    ObjectWarning(QString, QString, QString, QString, QString, QString, QString, QString, QString, QString);
    static QVector<ObjectWarning> parseJson(QString);
    QString getClosestRadar() const;
    QString getUrl() const;
    QVector<LatLon> getPolygonAsLatLons(int) const;
    QString url;
    QString title;
    QString area;
    QString effective;
    QString expires;
    QString event;
    QString sender;
    QString geometry;
    QString vtec;
    bool isCurrent;

private:
    QString polygon;
};

#endif  // OBJECTWARNING_H
