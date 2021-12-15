// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ObjectCardDashAlertItem.h"
#include "misc/AlertsDetail.h"
#include "radar/Nexrad.h"

ObjectCardDashAlertItem::ObjectCardDashAlertItem(QWidget * parent, const ObjectWarning& warning) : HBox(parent) {
    this->parent = parent;

    layoutVertical = VBox(parent);
    textLayout = VBox(parent);

    topLine = Text(parent, warning.event + " (" + warning.sender + ")");
    topLine.setBlue();

    auto data = warning.title;
    auto titleInfo = warning.sender + " " + data.replace("\\n", " ");
    titleLine = Text(parent, titleInfo);

    startTimeLine = Text(parent);
    auto startTime = warning.effective;
    startTime = startTime.replace("T", " ");
    startTimeLine.setText(startTime);

    endTimeLine = Text(parent);
    auto endTime = warning.expires;
    endTime = endTime.replace("T", " ");
    endTimeLine.setText(endTime);

    middleLine = Text(parent, warning.area);
    middleLine.setGray();

    textLayout.addWidget(topLine.get(), 0, Qt::AlignTop);
    textLayout.addWidget(titleLine.get(), 0, Qt::AlignTop);
    textLayout.addWidget(middleLine.get(), 0, Qt::AlignTop);
    textLayout.addWidget(startTimeLine.get(), 0, Qt::AlignTop);
    textLayout.addWidget(endTimeLine.get(), 0, Qt::AlignTop);
    textLayout.addStretch();

    buttonDetails = Button(parent, "Show Details");
    auto url = warning.getUrl();
    auto parent1 = parent;
    buttonDetails.connect([url, parent1] { new AlertsDetail(parent1, url); });

    auto radar = warning.getClosestRadar();
    buttonRadar = Button(parent, "Show Radar - &" + radar);
    buttonRadar.connect([radar, parent1] { new Nexrad(parent1, 1, true, radar, false); });

    addLayout(layoutVertical.get(), Qt::AlignTop);
    addLayout(textLayout.get(), Qt::AlignTop);

    layoutVertical.addWidget(buttonDetails.get());
    layoutVertical.addWidget(buttonRadar.get());
    layoutVertical.addStretch();
}
