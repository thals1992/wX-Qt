// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/CardStormReportItem.h"
#include <QDesktopServices>
#include <QUrl>

CardStormReportItem::CardStormReportItem(QWidget * parent, const StormReport& stormReport)
    : topLine{ Text{parent, stormReport.state + ", " + stormReport.city + " " + stormReport.time} }
    , middleLine{ Text{parent, stormReport.address} }
    , endLine{ Text{parent, stormReport.magnitude + " - " + stormReport.damageReport} }
    , buttonDetails{ Button{parent, None, "Show on map"} }
{
    topLine.setBold();
    middleLine.setGray();

    textLayout.addWidget(topLine);
    textLayout.addWidget(middleLine);
    textLayout.addWidget(endLine);
    textLayout.addStretch();

    const auto lat = stormReport.lat;
    const auto lon = stormReport.lon;
    buttonDetails.connect([lat, lon] { launchMap(lat, lon); });

    addLayout(layoutButtons);
    addLayout(textLayout, Qt::AlignTop);
    layoutButtons.addWidget(buttonDetails);
}

void CardStormReportItem::launchMap(const string& lat, const string& lon) {
    // https://www.openstreetmap.org/?mlat=47.5433&mlon=-52.8734&zoom=12#map=12/47.5433/-52.8734;
    const auto url = QUrl{QString::fromStdString("https://www.openstreetmap.org/?mlat=" + lat + "&mlon=" + lon + "&zoom=12//map=12/" + lat + "/" + lon)};
    QDesktopServices::openUrl(url);
}
