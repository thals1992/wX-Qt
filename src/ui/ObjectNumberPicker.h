// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTNUMBERPICKER_H
#define OBJECTNUMBERPICKER_H

#include <QBoxLayout>
#include <QSpinBox>
#include <QString>
#include "ui/HBox.h"
#include "ui/Text.h"

class ObjectNumberPicker : public QObject {

    Q_OBJECT

public:
    ObjectNumberPicker();
    ObjectNumberPicker(QWidget * parent, const QString& label, const QString& pref, int defaultValue, int low, int up, int step);
    void updateNp(const QString& newValue);
    int getCurrentValue();
    QBoxLayout * get();

private:
    QWidget * parent;
    QSpinBox * qSpinBox;
    HBox box;
    Text text;
    QString pref;
    int defaultValue;
};

#endif  // OBJECTNUMBERPICKER_H
