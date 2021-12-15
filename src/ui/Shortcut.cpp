// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/Shortcut.h"

Shortcut::Shortcut() {
}

Shortcut::Shortcut(const QKeySequence& key, QWidget * parent) {
    this->parent = parent;
    qshortcut = new QShortcut(key, parent);
}

QShortcut * Shortcut::get() {
    return qshortcut;
}

void Shortcut::connect(std::function<void()> f) {
    QObject::connect(get(), &QShortcut::activated, parent, f);
}
