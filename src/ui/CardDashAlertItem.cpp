// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/CardDashAlertItem.h"
#include "objects/WString.h"
#include "misc/AlertsDetail.h"
#include "radar/Nexrad.h"

CardDashAlertItem::CardDashAlertItem(QWidget * parent, const ObjectWarning& warning)
    : HBox{}
    , topLine{ Text{parent, warning.event + " (" + warning.sender + ")"} }
    , titleLine{ Text{parent} }
    , startTimeLine{ Text{parent} }
    , endTimeLine{ Text{parent} }
    , middleLine{ Text{parent, warning.area} }
    , buttonDetails{ Button{parent, None, "Show Details"} }
    , buttonRadar{ Button{parent, None, "Show Radar - &"} }
{
    topLine.setBlue();

    const auto data = warning.title;
    const auto titleInfo = warning.sender + " " + WString::replace(data, "\\n", " ");
    titleLine.setText(titleInfo);

    auto startTime = warning.effective;
    startTime = WString::replace(startTime, "T", " ");
    startTimeLine.setText(startTime);

    auto endTime = warning.expires;
    endTime = WString::replace(endTime, "T", " ");
    endTimeLine.setText(endTime);

    middleLine.setGray();
    boxText.addWidget(topLine, 0, Qt::AlignTop);
    boxText.addWidget(titleLine, 0, Qt::AlignTop);
    boxText.addWidget(middleLine, 0, Qt::AlignTop);
    boxText.addWidget(startTimeLine, 0, Qt::AlignTop);
    boxText.addWidget(endTimeLine, 0, Qt::AlignTop);
    boxText.addStretch();

    const auto url = warning.getUrl();
    const auto parent1 = parent;
    buttonDetails.connect([url, parent1] { new AlertsDetail{parent1, url}; });

    const auto radar = warning.getClosestRadar();
    buttonRadar.setText("Show Radar - &" + radar);
    buttonRadar.connect([radar, parent1] { new Nexrad{parent1, 1, true, radar}; });

    addLayout(layoutVertical, Qt::AlignTop);
    addLayout(boxText, Qt::AlignTop);
    addStretch();

    layoutVertical.addWidget(buttonDetails);
    layoutVertical.addWidget(buttonRadar);
    layoutVertical.addStretch();
}
