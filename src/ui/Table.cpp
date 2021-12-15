// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/Table.h"

Table::Table() {
}

Table::Table(QWidget * parent) {
    this->parent = parent;
    grid = new QFormLayout(parent);
}

void Table::addRow(const QString& label, QWidget * w) {
    grid->addRow(label, w);
}

QFormLayout * Table::get() {
    return grid;
}
