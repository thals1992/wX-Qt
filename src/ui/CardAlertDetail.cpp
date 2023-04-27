// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/CardAlertDetail.h"
#include "misc/AlertsDetail.h"
#include "radar/Nexrad.h"

CardAlertDetail::CardAlertDetail(QWidget * parent, const CapAlertXml& cap)
    : HBox{}
    , topLine{ Text{parent, cap.title} }
    , startTimeLine{ Text{parent} }
    , endTimeLine{ Text{parent} }
    , middleLine{ Text{parent, cap.area} }
    , buttonDetails{ Button{parent, None, "Show Details"} }
    , buttonRadar{ Button{parent, None, ""} }
{
    topLine.setBold();
    topLine.setWordWrap(false);

    startTimeLine.setText(cap.effective);
    endTimeLine.setText(cap.expires);
    middleLine.setGray();

    boxText.addWidget(topLine, 0, Qt::AlignTop);
    boxText.addWidget(middleLine, 0, Qt::AlignTop);
    boxText.addWidget(startTimeLine, 0, Qt::AlignTop);
    boxText.addWidget(endTimeLine, 0, Qt::AlignTop);
    boxText.addStretch();

    buttonDetails.connect([parent, cap] { new AlertsDetail{parent, cap.url}; });

    const auto radarSite = cap.getClosestRadar();
    if (!radarSite.empty()) {
        buttonRadar.setText("Show Radar - " + radarSite);
        buttonRadar.connect([parent, radarSite] { new Nexrad{parent, 1, true, radarSite}; });
    } else {
        buttonRadar.setVisible(false);
    }

    addLayout(layoutVertical, Qt::AlignLeft);
    addLayout(boxText, Qt::AlignTop);
    addStretch();

    layoutVertical.addWidget(buttonDetails);
    layoutVertical.addWidget(buttonRadar);
    layoutVertical.addStretch();
}
