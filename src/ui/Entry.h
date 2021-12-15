// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef ENTRY_H
#define ENTRY_H

#include <functional>
#include <QLineEdit>

class Entry {
public:
    Entry();
    explicit Entry(QWidget * parent);
    void connect(std::function<void()>);
    void setText(const QString& s);
    QString getText();
    QLineEdit * get();

private:
    QWidget * parent;
    QLineEdit * entry;
};

#endif  // ENTRY_H
