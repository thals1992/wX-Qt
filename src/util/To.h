// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef TO_H
#define TO_H

#include <string>
#include <QStringList>

class To {
public:
    static int Int(const std::string&);
    static double Double(const std::string&);
    static std::string string(int);
    static std::string string(double);
    static std::string string(bool);
    static std::string stringPadLeft(const std::string&, int);
    static std::string stringPadLeftZeros(const std::string&, int);
    static std::string stringPadLeftZeros(int, int);
};

#endif  // TO_H
