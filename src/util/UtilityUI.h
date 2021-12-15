// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYUI_H
#define UTILITYUI_H

#include <QByteArray>
#include <QImage>
#include <QLabel>
#include <QLayout>
#include <QVector>

class UtilityUI {
public:
    static QVector<int> getScreenBounds();
    static int getImageWidth(int);
    static void updateImage(QLabel *, const QByteArray&, int);
    static void removeChildren(QLayout *);
};

#endif  // UTILITYUI_H
