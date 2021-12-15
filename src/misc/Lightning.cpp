// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/Lightning.h"
#include "objects/FutureBytes.h"
#include "misc/UtilityLightning.h"
#include "util/Utility.h"
#include "util/UtilityList.h"

Lightning::Lightning(QWidget * parent) : Window(parent) {
    setTitle("Lightning");
    maximize();

    boxH = HBox(this);
    box = VBox(this);
    photo = Photo(this, PhotoSizeEnum::full);

    sector = Utility::readPref(prefTokenSector, "usa_big");
    time = Utility::readPref(prefTokenPeriod, "0.25");

    comboboxSector = ComboBox(this, UtilityLightning::sectors);
    auto productIndex = UtilityList::findex(UtilityLightning::getSectorPretty(sector), UtilityLightning::sectors);
    comboboxSector.setIndex(productIndex);
    comboboxSector.connect([this] { changeSector(); });

    comboboxTime = ComboBox(this, UtilityLightning::times);
    auto timeIndex = UtilityList::findex(UtilityLightning::getTimePretty(time), UtilityLightning::times);
    comboboxTime.setIndex(timeIndex);
    comboboxTime.connect([this] { changeTime(); });

    boxH.addWidget(comboboxSector.get());
    boxH.addWidget(comboboxTime.get());
    box.addLayout(boxH.get());
    box.addWidgetAndCenter(photo.get());
    box.getAndShow(this);

    reload();
}

void Lightning::reload() {
    Utility::writePref(prefTokenSector, sector);
    Utility::writePref(prefTokenPeriod, time);
    auto url = UtilityLightning::getImageUrl(sector, time);
    new FutureBytes(this, url, [this] (const auto& ba) { photo.setBytes(ba); });
}

void Lightning::changeSector() {
    sector = UtilityLightning::getSector(UtilityLightning::sectors[comboboxSector.getIndex()]);
    reload();
}

void Lightning::changeTime() {
    time = UtilityLightning::getTime(UtilityLightning::times[comboboxTime.getIndex()]);
    reload();
}
