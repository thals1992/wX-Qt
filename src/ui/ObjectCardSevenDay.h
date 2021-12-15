// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTCARDSEVENDAY_H
#define OBJECTCARDSEVENDAY_H

#include <QStringList>
#include <QVector>
#include <QWidget>
#include "ui/VBox.h"
#include "ui/SevenDayCard.h"

class ObjectCardSevenDay {
public:
    ObjectCardSevenDay();
    ObjectCardSevenDay(QWidget * parent, VBox&, const QStringList&, const QStringList&);
    void update(const QStringList&, const QStringList&);
    QVector<SevenDayCard> cards;
};

#endif  // OBJECTCARDSEVENDAY_H
