// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTNUMBERPICKER_H
#define OBJECTNUMBERPICKER_H

#include <string>
#include <QBoxLayout>
#include <QSpinBox>
#include <QString>
#include "ui/HBox.h"
#include "ui/Text.h"

using std::string;

class NumberPicker : public QObject {

    Q_OBJECT

public:
    NumberPicker(QWidget *, const string&, const string&, int, int, int, int);
    void updateNp(const QString&);
    int getCurrentValue();
    QBoxLayout * get();

private:
    QWidget * parent;
    string pref;
    int defaultValue;
    Text text;
    QSpinBox * qSpinBox;
    HBox box;
};

#endif  // OBJECTNUMBERPICKER_H
