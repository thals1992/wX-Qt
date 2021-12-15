// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef TO_H
#define TO_H

#include <QStringList>

class To {
public:
    static int Int(QString);
    static double Double(QString);
    static float Float(QString);
    static QString String(int);
    static QString String(float);
    static QString String(double);
    static QString String(bool);
    static QString StringPadLeft(QString, int);
    static QString StringPadLeftZeros(QString, int);
    static QString StringPadLeftZeros(int, int);
};

#endif  // TO_H
