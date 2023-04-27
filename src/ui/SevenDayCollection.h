// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SEVENDAYCOLLECTION_H
#define SEVENDAYCOLLECTION_H

#include <string>
#include <vector>
#include <QWidget>
#include "ui/VBox.h"
#include "ui/SevenDayCard.h"
#include "util/SevenDay.h"

using std::string;
using std::vector;

class SevenDayCollection {
public:
    SevenDayCollection();  // MainWindow
    SevenDayCollection(QWidget * parent, VBox&, SevenDay *);
    void update();
    vector<SevenDayCard> sevenDayCard;

private:
    SevenDay * sevenDay;
};

#endif  // SEVENDAYCOLLECTION_H
