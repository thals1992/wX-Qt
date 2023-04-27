// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTSWITCH_H
#define OBJECTSWITCH_H

#include <string>
#include <QCheckBox>
#include "objects/PrefBool.h"

using std::string;

class Switch : public QObject {

    Q_OBJECT

public:
    Switch(QWidget *, const string&, const string&, bool);
    static Switch * fromPrefBool(QWidget *, const PrefBool&);
    bool isTrue();
    void toggle();
    QWidget * get();

private:
    QWidget * parent;
    string pref;
    string defaultValueAsString;
    QCheckBox * checkBox;
};

#endif  // OBJECTSWITCH_H
