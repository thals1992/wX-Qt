// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ObjectCardAlertDetail.h"
#include "misc/AlertsDetail.h"
#include "radar/Nexrad.h"

ObjectCardAlertDetail::ObjectCardAlertDetail(QWidget * parent, const CapAlertXml& cap)
    : HBox{}
    , parent{ parent }
    , topLine{ Text{parent, cap.title} }
    , startTimeLine{ Text{parent} }
    , endTimeLine{ Text{parent} }
    , middleLine{ Text{parent, cap.area} }
    , buttonDetails{ Button{parent, None, "Show Details"} }
    , buttonRadar{ Button{parent, None, ""} }
{
    topLine.setBold();
    topLine.setWordWrap(false);

    // FIXME TODO
//    auto re = QRegularExpression(":00-0[0-9]:00");
//    auto capEffective = cap.effective;
//    auto startTime = capEffective.replace(re, "");
//    startTime = startTime.replace("T", " ");
    startTimeLine.setText(cap.effective);

//    auto capExpires = cap.expires;
//    auto endTime = capExpires.replace(re, "");
//    endTime = endTime.replace("T", " ");
    endTimeLine.setText(cap.expires);

    middleLine.setGray();

    boxText.addWidget(topLine.get());
    boxText.addWidget(middleLine.get());
    boxText.addWidget(startTimeLine.get());
    boxText.addWidget(endTimeLine.get());

    const auto parent1 = this->parent;
    buttonDetails.connect([parent1, cap] { new AlertsDetail{parent1, cap.url}; });
    buttonRadar.setText("Show Radar - " + radarSite);

    radarSite = cap.getClosestRadar();
    if (!radarSite.empty()) {
        const auto radarSite = this->radarSite;
        buttonRadar.setText("Show Radar - " + radarSite);
        buttonRadar.connect([parent1, radarSite] { new Nexrad{parent1, 1, true, radarSite}; });
    } else {
        buttonRadar.setVisible(false);
    }
    boxText.addStretch();

    addWidget(buttonDetails.get(), Qt::AlignTop);
    addWidget(buttonRadar.get());
    addLayout(boxText.get());
    addStretch();
}
