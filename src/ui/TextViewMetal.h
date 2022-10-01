// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef TEXTVIEWMETAL_H
#define TEXTVIEWMETAL_H

#include <string>
#include <QString>

using std::string;

class TextViewMetal {
public:
    void setText(const string&);
    void setPadding(double, double);
    QString text;
    int xPos{};
    int yPos{};

    static float fontSize;
};

#endif  // TEXTVIEWMETAL_H
