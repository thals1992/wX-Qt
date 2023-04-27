// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/RadarMosaicNws.h"
#include <QCloseEvent>
#include <string>
#include "objects/FutureBytes.h"
#include "radar/UtilityNwsRadarMosaic.h"
#include "settings/Location.h"
#include "settings/UIPreferences.h"
#include "util/Utility.h"
#include "util/UtilityList.h"

using std::string;

RadarMosaicNws::RadarMosaicNws(QWidget * parent)
    : Window{parent}
    , photo{ Photo{this, Full} }
    , comboboxSector{ ComboBox{this, UtilityNwsRadarMosaic::sectors} }
    , animateButton{ ButtonToggle{this, Play, "Animate"} }
    , objectAnimate{ ObjectAnimate{this, &photo, &UtilityNwsRadarMosaic::getAnimation, [this] { reload(); }, &animateButton} }
    , shortcutAnimate{ Shortcut{QKeySequence{"A"}, this} }
{
    setTitle("Radar Mosaics");
    if (!UIPreferences::rememberMosaic) {
        objectAnimate.sector = UtilityNwsRadarMosaic::getNearest(Location::getLatLonCurrent());
    } else {
        objectAnimate.sector = Utility::readPref("REMEMBER_MOSAIC_SECTOR", UtilityNwsRadarMosaic::getNearest(Location::getLatLonCurrent()));
    }
    animateButton.connect([this] { objectAnimate.animateClicked(); });
    comboboxSector.setIndex(findex(objectAnimate.sector, UtilityNwsRadarMosaic::sectors));
    comboboxSector.connect([this] { changeSector(); });
    boxH.addWidget(comboboxSector);
    boxH.addWidget(animateButton);
    box.addLayout(boxH);
    box.addWidgetAndCenter(photo);
    box.getAndShow(this);
    shortcutAnimate.connect([this] { objectAnimate.animateClicked(); });
    reload();
}

void RadarMosaicNws::reload() {
    Utility::writePref("REMEMBER_MOSAIC_SECTOR", objectAnimate.sector);
    const auto url = UtilityNwsRadarMosaic::get(objectAnimate.sector);
    new FutureBytes{this, url, [this] (const auto& ba) { photo.setBytes(ba); }};
}

void RadarMosaicNws::changeSector() {
    objectAnimate.sector = UtilityNwsRadarMosaic::sectors[comboboxSector.getIndex()];
    objectAnimate.stopAnimate();
    reload();
}

void RadarMosaicNws::closeEvent(QCloseEvent * event) {
    objectAnimate.stopAnimate();
    event->accept();
}
