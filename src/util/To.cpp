// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/To.h"
#include <iostream>
#include <sstream>

int To::Int(const std::string& s) {
    return QString::fromStdString(s).toInt();
}

double To::Double(const std::string& s) {
    return QString::fromStdString(s).toDouble();
}

std::string To::string(int i) {
    return QString::number(i).toStdString();
}

std::string To::string(double d) {
    return QString::number(d).toStdString();
}

std::string To::string(bool b) {
    std::ostringstream ss;
    ss << std::boolalpha << b;
    return QString::fromStdString(ss.str()).toStdString();
}

std::string To::stringPadLeft(const std::string& s, int padAmount) {
    return QString::fromStdString(s).leftJustified(padAmount, ' ').toStdString();
}

std::string To::stringPadLeftZeros(const std::string& s, int padAmount) {
    return QString::fromStdString(s).rightJustified(padAmount, '0').toStdString();
}

std::string To::stringPadLeftZeros(int s, int padAmount) {
    return QString::fromStdString(To::string(s)).rightJustified(padAmount, '0').toStdString();
}
