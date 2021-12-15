// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef CAPALERTXML_H
#define CAPALERTXML_H

#include <QStringList>

class CapAlertXml {
public:
    CapAlertXml();
    explicit CapAlertXml(const QString&);
    QString getClosestRadar() const;
    QString url;
    QString title;
    QString summary;
    QString instructions;
    QString area;
    QString effective;
    QString expires;
    QString event;
    QString vtec;
    QString zones;
    QString polygon;
    QString text;
    QStringList points;
};

#endif  // CAPALERTXML_H
