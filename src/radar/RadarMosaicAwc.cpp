// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/RadarMosaicAwc.h"
#include <QCloseEvent>
#include "objects/FutureBytes.h"
#include "settings/Location.h"
#include "radar/UtilityAwcRadarMosaic.h"
#include "ui/Icon.h"
#include "util/UtilityList.h"

RadarMosaicAwc::RadarMosaicAwc(QWidget * parent) : Window(parent) {
    setTitle("Radar Mosaics");
    maximize();
    box = VBox(this);
    boxH = HBox(this);
    photo = Photo(this, PhotoSizeEnum::full);
    animateButton = ButtonToggle(this , Icon::Play, "Animate");
    objectAnimate = new ObjectAnimate(this, &photo, &UtilityAwcRadarMosaic::getAnimation, [this] { reload(); }, &animateButton);
    objectAnimate->sector = UtilityAwcRadarMosaic::getNearestMosaic(Location::getLatLonCurrent());
    objectAnimate->product = "rad_rala";
    animateButton.connect([this] { objectAnimate->animateClicked(); });

    comboboxProduct = ComboBox(this, UtilityAwcRadarMosaic::products);
    comboboxProduct.setIndexByValue(objectAnimate->product);
    comboboxProduct.connect([this] { changeProduct(); });

    comboboxSector = ComboBox(this, UtilityAwcRadarMosaic::sectorLabels);
    comboboxSector.setIndex(UtilityList::findex(objectAnimate->sector, UtilityAwcRadarMosaic::sectors));
    comboboxSector.connect([this] { changeSector(); });

    boxH.addWidget(comboboxProduct.get());
    boxH.addWidget(comboboxSector.get());
    boxH.addWidget(animateButton.get());
    box.addLayout(boxH.get());
    box.addWidgetAndCenter(photo.get());
    box.getAndShow(this);

    shortcutAnimate = Shortcut(QKeySequence("Ctrl+A"), this);
    shortcutAnimate.connect([this] { objectAnimate->animateClicked(); });

    reload();
}

void RadarMosaicAwc::reload() {
    const auto url = UtilityAwcRadarMosaic::get(objectAnimate->product, objectAnimate->sector);
    new FutureBytes(this, url, [this] (const auto& ba) { photo.setBytes(ba); });
}

void RadarMosaicAwc::changeProduct() {
    objectAnimate->product = UtilityAwcRadarMosaic::products[comboboxProduct.getIndex()];
    objectAnimate->stopAnimate();
    reload();
}

void RadarMosaicAwc::changeSector() {
    objectAnimate->sector = UtilityAwcRadarMosaic::sectors[comboboxSector.getIndex()];
    objectAnimate->stopAnimate();
    reload();
}

void RadarMosaicAwc::closeEvent(QCloseEvent * event) {
    objectAnimate->stopAnimate();
    event->accept();
}
