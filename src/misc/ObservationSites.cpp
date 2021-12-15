// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/ObservationSites.h"
#include <QDesktopServices>
#include <QUrl>
#include "settings/Location.h"

ObservationSites::ObservationSites(QWidget * parent) : Window(parent) {
    setWindowTitle("Observation web sites - " + Location::name());
    resize(700, 700);

    box = HBox(centralWidget);

    button1 = Button(this, Location::wfo() + ": nearby current observations");
    auto url = "https://www.wrh.noaa.gov/map/?obs=true&wfo=" + Location::wfo().toLower();
    button1.connect([this, url] {launchAlert(url);});

    button2 = Button(this, Location::getObs() + ": recent observations");
    auto url2 = "https://www.wrh.noaa.gov/mesowest/timeseries.php?sid=" + Location::getObs();
    button2.connect([this, url2] {launchAlert(url2);});

    box.addWidget(button1.get());
    box.addWidget(button2.get());

    box.getAndShow(this);
}

void ObservationSites::launchAlert(const QString& url) {
    auto qUrl = QUrl(url);
    QDesktopServices::openUrl(qUrl);
}
