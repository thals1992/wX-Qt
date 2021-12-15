// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/SevenDayCard.h"
#include "common/GlobalVariables.h"
#include "util/UtilityLocationFragment.h"

SevenDayCard::SevenDayCard() {
}

SevenDayCard::SevenDayCard(QWidget * parent, const QString& row1F, const QString& row2, const QString& icon) : HBox(parent) {
    auto row1 = row1F;
    boxImage = VBox(parent);
    boxText = VBox(parent);
    boxImage.setSpacing(0);
    boxText.setSpacing(0);

    firstRow = Text(parent);
    firstRow.setBold();
    firstRow.setWordWrap(false);
    firstRow.setText(row1.replace("\"", "") + tempAndWind(row2));

    secondRow = Text(parent, row2);
    secondRow.setGray();

    photo = Photo(parent);
    photo.setNwsIcon(icon);

    boxImage.addWidget(photo.get(), 0, Qt::AlignTop);
    boxImage.addStretch();

    boxText.addWidget(firstRow.get(), 0, Qt::AlignTop);
    boxText.addWidget(secondRow.get(), 0, Qt::AlignTop);
    boxText.addStretch();

    // addWidget(photo.get());
    addLayout(boxImage.get(), 0);
    addLayout(boxText.get(), 1);
}

void SevenDayCard::update(QString row1, const QString& row2, const QString& icon) {
    photo.setNwsIcon(icon);
    firstRow.setText(row1.replace("\"", "") + tempAndWind(row2));
    secondRow.setText(row2);
}

QString SevenDayCard::tempAndWind(const QString& row2) {
    auto temperature = UtilityLocationFragment::extractTemp(row2) + GlobalVariables::degreeSymbol;
    auto windDirection = UtilityLocationFragment::extractWindDirection(row2);
    auto windSpeed = UtilityLocationFragment::extract7DayMetrics(row2);
    auto tempAndWind = temperature + " " + windDirection + " " + windSpeed;
    return " (" + tempAndWind.trimmed() + ")";
}
