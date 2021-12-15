// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ObjectCardAlertDetail.h"
#include "misc/AlertsDetail.h"
#include "radar/Nexrad.h"

ObjectCardAlertDetail::ObjectCardAlertDetail(QWidget * parent, CapAlertXml cap): HBox(parent) {
    this->parent = parent;
    this->cap = cap;

    boxText = VBox(parent);

    topLine = Text(parent, cap.title);
    topLine.setBold();
    topLine.setWordWrap(false);

    startTimeLine = Text(parent);
    QRegularExpression re(":00-0[0-9]:00");
    auto startTime = cap.effective.replace(re, "");
    startTime = startTime.replace("T", " ");
    startTimeLine.setText(startTime);

    endTimeLine = Text(parent);
    auto endTime = cap.expires.replace(re, "");
    endTime = endTime.replace("T", " ");
    endTimeLine.setText(endTime);

    middleLine = Text(parent, cap.area);
    middleLine.setGray();

    boxText.addWidget(topLine.get());
    boxText.addWidget(middleLine.get());
    boxText.addWidget(startTimeLine.get());
    boxText.addWidget(endTimeLine.get());

    buttonDetails = Button(parent, "Show Details");
    QWidget * parent1 = this->parent;
    buttonDetails.connect([parent1, cap] { new AlertsDetail(parent1, cap.url); });
    buttonRadar = Button(parent, "Show Radar - " + radarSite);

    radarSite = cap.getClosestRadar();
    if (radarSite != "") {
        auto radarSite = this->radarSite;
        QWidget * parent = this->parent;
        buttonRadar.setText("Show Radar - " + radarSite);
        buttonRadar.connect([parent, radarSite] { new Nexrad(parent, 1, true, radarSite, false); });
    } else {
        buttonRadar.setVisible(false);
    }
    boxText.addStretch();

    addWidget(buttonDetails.get(), Qt::AlignTop);
    addWidget(buttonRadar.get());
    addLayout(boxText.get());
}
