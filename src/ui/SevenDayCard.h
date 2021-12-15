// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SEVENDAYCARD_H
#define SEVENDAYCARD_H

#include <QString>
#include <QWidget>
#include "ui/HBox.h"
#include "ui/Text.h"
#include "ui/Photo.h"
#include "ui/VBox.h"

class SevenDayCard : public HBox {
public:
    SevenDayCard();
    SevenDayCard(QWidget *, const QString&, const QString&, const QString&);
    void update(QString, const QString&, const QString&);

private:
    QString tempAndWind(const QString&);
    VBox boxImage;
    VBox boxText;
    Photo photo;
    Text firstRow;
    Text secondRow;
};

#endif  // SEVENDAYCARD_H
