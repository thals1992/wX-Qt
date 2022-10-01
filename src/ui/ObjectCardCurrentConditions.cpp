// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ObjectCardCurrentConditions.h"

ObjectCardCurrentConditions::ObjectCardCurrentConditions() = default;

ObjectCardCurrentConditions::ObjectCardCurrentConditions(QWidget * parent, const ObjectCurrentConditions& cc)
    : HBox{}
    , topLine{ Text{parent, cc.topLine} }
    , middleLine{ Text{parent, cc.middleLine} }
    , bottomLine{ Text{parent, cc.bottomLine} }
    , photo{ Photo{parent} }
{
    boxText.setSpacing(0);

    topLine.setWordWrap(false);
    topLine.setBold();
    middleLine.setWordWrap(false);
    bottomLine.setWordWrap(false);

    photo.setAlignment(Qt::AlignTop);
    photo.setNwsIcon(cc.iconUrl);

    boxText.addWidget(topLine.get(), 0, Qt::AlignTop);
    boxText.addWidget(middleLine.get(), 0, Qt::AlignTop);
    boxText.addWidget(bottomLine.get(), 0, Qt::AlignTop);

    addWidget(photo.get());
    addLayout(boxText.get());
}

void ObjectCardCurrentConditions::update(const ObjectCurrentConditions& cc) {
    topLine.setText(cc.topLine);
    middleLine.setText(cc.middleLine);
    bottomLine.setText(cc.bottomLine);
    photo.setNwsIcon(cc.iconUrl);
}
