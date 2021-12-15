// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef RID_H
#define RID_H

#include "objects/LatLon.h"

class RID {
public:
    RID();
    RID(const QString&, const LatLon&);
    QString name;
    LatLon location;
    int distance;
    bool operator <(const LatLon&);
};

#endif  // RID_H
