// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/SevenDayCard.h"
#include "common/GlobalVariables.h"
#include "objects/WString.h"
#include "util/UtilityLocationFragment.h"

SevenDayCard::SevenDayCard(QWidget * parent, const string& row1, const string& row2, const string& icon)
    : firstRow{ Text{parent} }
    , secondRow{ Text{parent, row2} }
    , photo{ Photo{parent} }
{
    boxImage.setSpacing(0);
    boxText.setSpacing(0);

    firstRow.setBold();
    firstRow.setWordWrap(false);
    firstRow.setText(WString::replace(row1, "\"", "") + tempAndWind(row2));
    secondRow.setGray();
    photo.setNwsIcon(icon);

    boxImage.addWidget(photo, 0, Qt::AlignTop);
    boxImage.addStretch();
    boxText.addWidget(firstRow, 0, Qt::AlignTop);
    boxText.addWidget(secondRow, 0, Qt::AlignTop);
    boxText.addStretch();

    addLayout(boxImage, 0);
    addLayout(boxText, 1);
}

void SevenDayCard::update(const string& row1, const string& row2, const string& icon) {
    photo.setNwsIcon(icon);
    firstRow.setText(WString::replace(row1, "\"", "") + tempAndWind(row2));
    secondRow.setText(row2);
}

string SevenDayCard::tempAndWind(const string& row2) {
    const auto temperature = UtilityLocationFragment::extractTemp(row2) + GlobalVariables::degreeSymbol;
    const auto windDirection = UtilityLocationFragment::extractWindDirection(row2);
    const auto windSpeed = UtilityLocationFragment::extract7DayMetrics(row2);
    const auto tempAndWind = temperature + " " + windDirection + " " + windSpeed;
    return " (" + WString::strip(tempAndWind) + ")";
}
