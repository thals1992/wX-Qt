// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/Entry.h"

Entry::Entry(QWidget * parent)
    : parent{ parent }
    , entry{ new QLineEdit{parent} }
{}

void Entry::connect(const function<void()>& fn) {
    QObject::connect(entry, &QLineEdit::textChanged, parent, fn);
}

void Entry::setText(const string& s) {
    entry->setText(QString::fromStdString(s));
}

string Entry::getText() {
    return entry->text().toStdString();
}

QLineEdit * Entry::getView() {
    return entry;
}
