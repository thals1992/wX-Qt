// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTMENUTITLE_H
#define OBJECTMENUTITLE_H

#include <QStringList>

class ObjectMenuTitle {
public:
    ObjectMenuTitle();
    ObjectMenuTitle(const QString&, int);
    void setList(const QStringList&, int);
    QStringList get();
    QStringList items;
    QString title;
    int count;
};

#endif  // OBJECTMENUTITLE_H
