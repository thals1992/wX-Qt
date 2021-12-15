// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/SpcMcdWatchMpdViewer.h"
#include "objects/FutureBytes.h"
#include "objects/FutureText.h"
#include "objects/LatLon.h"
#include "objects/ObjectPolygonWatch.h"
#include "radar/Nexrad.h"
#include "settings/UtilityLocation.h"

SpcMcdWatchMpdViewer::SpcMcdWatchMpdViewer(QWidget * parent, const QString& url) : Window(parent) {
    this->parent = parent;
    this->url = url;
    maximize();
    boxText = VBox(this);
    text = Text(this,"");
    photo = Photo(this, PhotoSizeEnum::normal);

    auto items = url.split("/");
    token = items.back();
    token = token.replace(".gif", "");
    token = token.toUpper();
    if (url.contains("www.wpc.ncep.noaa.gov")) {
        token = "WPCMPD" + token.right(4);
    } else if (url.contains("www.spc.noaa.gov") && url.contains("mcd")) {
        token = "SPCMCD" + token.right(4);
    } else {
        auto items1 = url.split("/");
        token = items1.back();
        token = token.replace("_radar.gif", "");
        token = token.replace("ww", "");
        token = "SPCWAT" + token.right(4);
    }
    setTitle(token);
    auto product = token;
    button = Button(this, "Radar");
    boxText.addWidget(button.get());
    boxText.addWidget(text.get());
    sw = ObjectTwoWidgetScroll(this, photo.get(), boxText.get());

    new FutureBytes(this, url, [this] (const auto& ba) { photo.setBytes(ba); });
    new FutureText(this, product, [this] (const auto& s) { updateText(s); });
}

void SpcMcdWatchMpdViewer::updateText(QString html) {
    text.setText(html);
    auto textWithLatLon = html;
    if (token.contains("SPCWAT")) {
        textWithLatLon = ObjectPolygonWatch::getLatLon(token.right(4));
    }
    auto stringOfLatLon = LatLon::storeWatchMcdLatLon(textWithLatLon);
    stringOfLatLon = stringOfLatLon.replace(":", "");
    auto latLonList = LatLon::parseStringToLatLons(stringOfLatLon, -1.0, false);
    auto center = UtilityLocation::getCenterOfPolygon(latLonList);
    auto radarSite = UtilityLocation::getNearestRadarSites(center, 1, false)[0];
    auto buttonRadarText = "Show Radar - " + radarSite.name;
    button.setText(buttonRadarText);
    button.connect([this, radarSite] { new Nexrad(this->parent, 1, true, radarSite.name, false); });
}
