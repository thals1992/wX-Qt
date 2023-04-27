// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/ObservationSites.h"
#include <QDesktopServices>
#include <QUrl>
#include "objects/WString.h"
#include "settings/Location.h"

ObservationSites::ObservationSites(QWidget * parent)
    : Window{parent}
    , button1{ Button{this, None, Location::wfo() + ": nearby current observations"} }
    , button2{ Button{this, None, Location::getObs() + ": recent observations"} }
{
    setTitle("Observation web sites - " + Location::name());
    setSize(700, 700);

    const auto url = "https://www.wrh.noaa.gov/map/?obs=true&wfo=" + WString::toLower(Location::wfo());
    const auto url2 = "https://www.weather.gov/wrh/timeseries?site=" + Location::getObs();
    button1.connect([url] { launchAlert(url); });
    button2.connect([url2] { launchAlert(url2); });

    box.addWidget(button1);
    box.addWidget(button2);
    box.addStretch();

    box.getAndShow(this);
}

void ObservationSites::launchAlert(const string& url) {
    QDesktopServices::openUrl(QUrl{ QString::fromStdString(url) });
}
