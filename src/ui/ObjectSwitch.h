// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTSWITCH_H
#define OBJECTSWITCH_H

#include <QCheckBox>
#include <QString>
#include "objects/PrefBool.h"

class ObjectSwitch : public QObject {

    Q_OBJECT

public:
    ObjectSwitch();
    ObjectSwitch(QWidget * parent, const QString& label, const QString& pref, bool defaultValue);
    static ObjectSwitch * fromPrefBool(QWidget * parent, const PrefBool& prefBool);
    bool isTrue();
    void toggle();
    QWidget * get();

private:
    QWidget * parent;
    QCheckBox * checkBox;
    QString pref;
    bool defaultValue;
    QString defaultValueAsString;
};

#endif  // OBJECTSWITCH_H
