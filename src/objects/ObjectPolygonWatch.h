// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTPOLYGONWATCH_H
#define OBJECTPOLYGONWATCH_H

#include <QHash>
#include "objects/DataStorage.h"
#include "objects/DownloadTimer.h"
#include "objects/LatLon.h"
#include "radar/PolygonType.h"

class ObjectPolygonWatch {
public:
    ObjectPolygonWatch();
    ObjectPolygonWatch(PolygonType);
    void download();
    QString getData();
    QString getUrl();
    QString getPrefTokenEnabled();
    QString getPrefTokenStorage();
    QString getPrefTokenColor();
    QString getPrefTokenNumberList();
    QString getPrefTokenLatLon();
    QString getTypeName();
    static void load();
    static QString storeWatchMcdLatLon(QString);
    static LatLon getLatLonFromString(QString);
    static QString getLatLon(QString);
    static QHash<PolygonType, ObjectPolygonWatch *> polygonDataByType;
    static DataStorage watchLatlonCombined;
    const static QStringList namesByEnumId;
    const static QVector<PolygonType> polygonList;
    PolygonType type1;
    bool isEnabled;
    DataStorage storage;
    DataStorage latLonList;
    DataStorage numberList;
    DownloadTimer timer;
};

#endif  // OBJECTPOLYGONWATCH_H
