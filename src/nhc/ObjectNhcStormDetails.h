// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTNHCSTORMDETAILS_H
#define OBJECTNHCSTORMDETAILS_H

#include <QByteArray>
#include <QString>

class ObjectNhcStormDetails {
public:
    ObjectNhcStormDetails();
    ObjectNhcStormDetails(const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&);
    QString getUpdateTime() const;
    QString forTopHeader() const;
    QString name;
    QString movementDir;
    QString movementSpeed;
    QString pressure;
    QString binNumber;
    QString id;
    QString lastUpdate;
    QString classification;
    QString lat;
    QString lon;
    QString center;
    QString intensity;
    QString status;
    QString movement;
    QString baseUrl;
    QString goesUrl;
    QByteArray coneBytes;
};

#endif  // OBJECTNHCSTORMDETAILS_H
