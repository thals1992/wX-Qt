// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <QFormLayout>

using std::string;

class Table {
public:
    explicit Table(QWidget *);
    void addRow(const string&, QWidget *);
    QFormLayout * get();

private:
    QFormLayout * grid;
};

#endif  // TABLE_H
