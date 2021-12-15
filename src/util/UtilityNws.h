// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYNWS_H
#define UTILITYNWS_H

#include <QBrush>
#include <QFont>
#include <QImage>
#include <QPen>
#include <QString>

class UtilityNws {
public:
    static QImage getIcon(const QString&);

private:
    static QImage parseBitmapString(const QString&);
    static QImage getBitmapWithOneNumber(const QString&);
    static QImage getDualBitmapWithNumbers(const QString&, const QString&);
    static const int dimensions;
    static const int numHeight;
    static const QFont font;
    static const QPen penForText;
    static const QBrush brushForBar;
};

#endif  // UTILITYNWS_H
