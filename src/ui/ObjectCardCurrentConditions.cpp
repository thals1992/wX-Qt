// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ObjectCardCurrentConditions.h"

ObjectCardCurrentConditions::ObjectCardCurrentConditions() {
}

ObjectCardCurrentConditions::ObjectCardCurrentConditions(QWidget * parent, const ObjectCurrentConditions& cc) : HBox(parent) {
    boxText = VBox();
    boxText.setSpacing(0);

    topLine = Text(parent, cc.topLine);
    topLine.setWordWrap(false);
    topLine.setBold();

    middleLine = Text(parent, cc.middleLine.trimmed());
    middleLine.setWordWrap(false);

    bottomLine = Text(parent, cc.bottomLine);
    bottomLine.setWordWrap(false);

    photo = Photo(parent);
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
