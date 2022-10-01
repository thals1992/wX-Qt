// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTCARDSEVENDAY_H
#define OBJECTCARDSEVENDAY_H

#include <string>
#include <vector>
#include <QWidget>
#include "ui/VBox.h"
#include "ui/SevenDayCard.h"

using std::string;
using std::vector;

class ObjectCardSevenDay {
public:
    ObjectCardSevenDay();  // MainWindow
    ObjectCardSevenDay(QWidget * parent, VBox&, const vector<string>&, const vector<string>&);
    void update(const vector<string>&, const vector<string>&);
    vector<SevenDayCard> sevenDayCard;
};

#endif  // OBJECTCARDSEVENDAY_H
