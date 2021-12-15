// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ObjectCardStormReportItem.h"
#include <QDesktopServices>
#include <QUrl>

ObjectCardStormReportItem::ObjectCardStormReportItem(QWidget * parent, const StormReport& stormReport) : VBox(parent) {

    layoutButtons = VBox(parent);
    textLayout = VBox(parent);

    topLine = Text(parent, stormReport.state + ", " + stormReport.city + " " + stormReport.time);
    topLine.setBold();

    middleLine = Text(parent, stormReport.address);
    middleLine.setGray();

    endLine = Text(parent, stormReport.magnitude + " - " + stormReport.damageReport);

    textLayout.addWidget(topLine.get());
    textLayout.addWidget(middleLine.get());
    textLayout.addWidget(endLine.get());
    textLayout.addStretch();

    buttonDetails = Button(parent, "Show on map");
    auto lat = stormReport.lat;
    auto lon = stormReport.lon;
    buttonDetails.connect([this, lat, lon] {launchMap(lat, lon);});

    addLayout(layoutButtons.get());
    addLayout(textLayout.get(), Qt::AlignTop);
    layoutButtons.addWidget(buttonDetails.get());
}

void ObjectCardStormReportItem::launchMap(const QString& lat, const QString& lon) {
    // https://www.openstreetmap.org/?mlat=47.5433&mlon=-52.8734&zoom=12#map=12/47.5433/-52.8734;
    auto url = QUrl("https://www.openstreetmap.org/?mlat=" + lat + "&mlon=" + lon + "&zoom=12//map=12/" + lat + "/" + lon);
    QDesktopServices::openUrl(url);
}
