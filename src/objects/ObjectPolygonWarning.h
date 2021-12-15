// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTPOLYGONWARNING_H
#define OBJECTPOLYGONWARNING_H

#include <QHash>
#include "objects/DataStorage.h"
#include "objects/DownloadTimer.h"
#include "radar/PolygonType.h"

class ObjectPolygonWarning {
public:
    static const QString pVtec;
    static const QString baseUrl;
    static const QHash<PolygonType, int> defaultColors;
    static const QHash<PolygonType, QString> longName;
    static const QVector<PolygonType> polygonList;
    static const QStringList namesByEnumId;
    static QHash<PolygonType, ObjectPolygonWarning *> polygonDataByType;
    static bool areAnyEnabled();
    static void load();
    ObjectPolygonWarning();
    explicit ObjectPolygonWarning(const PolygonType&);
    void download();
    QString getData();
    void enable();
    void disable();
    QString typeName() const;
    QString getTypeName() const;
    QString prefTokenEnabled() const;
    QString prefTokenStorage() const;
    QString prefTokenColor() const;
    int color() const;
    QString name() const;
    QString urlToken() const;
    QString url() const;
    QString getUrl() const;
    int getCount() const;
    DownloadTimer timer;
    PolygonType type1;
    bool isEnabled;
    DataStorage storage;
};

#endif  // OBJECTPOLYGONWARNING_H
