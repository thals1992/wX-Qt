// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SEVENDAYCARD_H
#define SEVENDAYCARD_H

#include <string>
#include <QWidget>
#include "ui/HBox.h"
#include "ui/Text.h"
#include "ui/Photo.h"
#include "ui/VBox.h"

using std::string;

class SevenDayCard : public HBox {
public:
    SevenDayCard(QWidget *, const string&, const string&, const string&);
    void update(const string&, const string&, const string&);

private:
    static string tempAndWind(const string&);
    VBox boxImage;
    VBox boxText;
    Text firstRow;
    Text secondRow;
    Photo photo;
};

#endif  // SEVENDAYCARD_H
