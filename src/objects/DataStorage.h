// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QString>

class DataStorage {
public:
    DataStorage();
    explicit DataStorage(const QString&);
    void update();
    QString getValue() const;
    void setValue(const QString&);

private:
    QString preference;
    QString val;
};

#endif  // DATASTORAGE_H
