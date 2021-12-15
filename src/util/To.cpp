// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/To.h"
#include <iostream>
#include <sstream>

int To::Int(QString s) {
    return s.toInt();
}

double To::Double(QString s) {
    return s.toDouble();
}

float To::Float(QString s) {
    return s.toFloat();
}

QString To::String(int i) {
    return QString::number(i);
}

QString To::String(float f) {
    return QString::number(f);
}

QString To::String(double d) {
    return QString::number(d);
}

QString To::String(bool b) {
    std::ostringstream ss;
    ss << std::boolalpha << b;
    return QString::fromStdString(ss.str());
}

QString To::StringPadLeft(QString s, int padAmount) {
    return s.leftJustified(padAmount, ' ');
}

QString To::StringPadLeftZeros(QString s, int padAmount) {
    return s.rightJustified(padAmount, '0');
}

QString To::StringPadLeftZeros(int s, int padAmount) {
    return To::String(s).rightJustified(padAmount, '0');
}
