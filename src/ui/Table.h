// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef TABLE_H
#define TABLE_H

#include <QFormLayout>

class Table {
public:
    Table();
    explicit Table(QWidget * parent);
    void addRow(const QString&, QWidget *);
    QFormLayout * get();

private:
    QWidget * parent;
    QFormLayout * grid;
};

#endif  // TABLE_H
