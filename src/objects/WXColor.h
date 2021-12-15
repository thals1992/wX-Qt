// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WXCOLOR_H
#define WXCOLOR_H

#include <QColor>
#include <QString>

class WXColor {
public:
    WXColor();
    WXColor(const QString&, const QString&, int, int, int);
    void setValue(int) const;
    QString styleSheetCurrent() const;
    QString uiLabel;
    QColor qcolor;
    QColor qcolorDefault;
    int red;
    int green;
    int blue;

private:
    QString prefVar;
    int defaultRed;
    int defaultGreen;
    int defaultBlue;
    int defaultcolorAsInt;
    int colorAsInt;
};

#endif  // WXCOLOR_H
