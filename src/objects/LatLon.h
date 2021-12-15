// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef LATLON_H
#define LATLON_H

#include <QString>
#include "external/ExternalPoint.h"
#include "util/ProjectionNumbers.h"

class LatLon {
public:
    LatLon();
    LatLon(double, double);
    LatLon(float, float);
    LatLon(const QString&, const QString&);
    explicit LatLon(const QVector<float>&);
    explicit LatLon(const QString&);
    float dist(LatLon) const;
    QString printSpaceSeparated() const;
    ExternalPoint asPoint() const;
    QVector<float> asList() const;
    QString latForNws() const;
    QString lonForNws() const;
    QString printPretty() const;
    QString latString;
    QString lonString;
    double lat;
    double lon;
    int distance;
    static LatLon fromList(QVector<float>);
    static LatLon fromRadarSite(const QString&);
    static QString storeWatchMcdLatLon(const QString&);
    static LatLon getLatLonFromString(const QString&);
    static QString getLatLon(const QString&);
    static QVector<float> latLonListToListOfDoubles(const QVector<LatLon>&, const ProjectionNumbers&);
    static QVector<LatLon> parseStringToLatLons(const QString&, float = 1.0, bool = true);
    static QVector<LatLon> parseStringToLatLonsForMcdLongPress(const QString&, float = 1.0, bool = true);
};

#endif  // LATLON_H
