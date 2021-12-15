// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYIO_H
#define UTILITYIO_H

#include <QObject>
#include <QStringList>
#include "objects/MemoryBuffer.h"

class UtilityIO: public QObject {

    // Q_OBJECT

public:
    static MemoryBuffer * uncompress(char *, int);
    static QString getHtml(const QString&);
    static QString readTextFile(const QString&);
    static QStringList rawFileToStringArray(const QString&);
    static QByteArray downloadAsByteArray(const QString&);
};

#endif  // UTILITYIO_H
