// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef TEXTVIEWMETAL_H
#define TEXTVIEWMETAL_H

#include <QString>

class TextViewMetal {
public:
    TextViewMetal();
    void setText(const QString&);
    void setPadding(float, float);
    QString text;
    int xPos;
    int yPos;

    static float fontSize;
};

#endif  // TEXTVIEWMETAL_H
