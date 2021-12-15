// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/Entry.h"

Entry::Entry() {
}

Entry::Entry(QWidget * parent) {
    this->parent = parent;
    entry = new QLineEdit(parent);
}

void Entry::connect(std::function<void()> f) {
    QObject::connect(get(), &QLineEdit::textChanged, parent, f);
}

void Entry::setText(const QString& s) {
    entry->setText(s);
}

QString Entry::getText() {
    return entry->text();
}

QLineEdit * Entry::get() {
    return entry;
}
