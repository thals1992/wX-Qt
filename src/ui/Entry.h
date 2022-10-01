// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef ENTRY_H
#define ENTRY_H

#include <functional>
#include <string>
#include <QLineEdit>

using std::function;
using std::string;

class Entry {
public:
    explicit Entry(QWidget *);
    void connect(const function<void()>&);
    void setText(const string&);
    string getText();
    QLineEdit * get();

private:
    QWidget * parent;
    QLineEdit * entry;
};

#endif  // ENTRY_H
