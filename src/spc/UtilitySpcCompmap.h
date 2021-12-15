// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCUTILITYSPCCOMPMAP_H
#define SPCUTILITYSPCCOMPMAP_H

#include <QStringList>

class UtilitySpcCompmap {
public:
    static QString getImage(const QString&);
    static const QStringList labels;
    static const QStringList urlIndices;
};

#endif  // SPCUTILITYSPCCOMPMAP_H
