// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/Table.h"

Table::Table(QWidget * parent)
    : grid{ new QFormLayout{parent} }
{}

void Table::addRow(const string& label, Widget2& w) {
    grid->addRow(QString::fromStdString(label), w.getView());
}

QFormLayout * Table::getView() {
    return grid;
}
