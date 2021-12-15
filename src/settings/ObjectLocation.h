// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTLOCATION_H
#define OBJECTLOCATION_H

#include <QString>

class ObjectLocation {
public:
    ObjectLocation();
    explicit ObjectLocation(int);
    void saveToNewSlot(int);
    QString getLat() const;
    QString getLon() const;
    QString getName() const;
    QString getWfo() const;
    QString getRadarSite() const;
    int locationNumber;

// TODO FIXME make private
// private:
    QString locNumAsString;
    QString lat;
    QString lon;
    QString name;
    QString wfo;
    QString rid;
    QString state;
};

#endif  // OBJECTLOCATION_H
