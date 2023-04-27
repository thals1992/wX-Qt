// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/Rtma.h"
#include "misc/UtilityRtma.h"
#include "objects/FutureBytes.h"
#include "objects/ObjectDateTime.h"
#include "settings/Location.h"
#include "ui/PhotoSizeEnum.h"
#include "util/Utility.h"
#include <iostream>

Rtma::Rtma(QWidget * parent)
    : Window{parent}
    , photo{ Photo{this, Full} }
    , comboboxProduct{ ComboBox{this, UtilityRtma::labels} }
    , comboboxSector{ ComboBox{this, UtilityRtma::sectors} }
    , comboboxTimes{ ComboBox{this, UtilityRtma::getTimes()} } // distinct
    , indexProduct{ Utility::readPrefInt(prefToken, 0) }
{
    setTitle("RTMA");
    comboboxProduct.setIndexByValue(UtilityRtma::labels[indexProduct]);
    comboboxProduct.connect([this] { changeProduct(); });
    comboboxSector.setIndexByValue(UtilityRtma::getNearest(Location::getLatLonCurrent()));
    comboboxSector.connect([this] { changeSector(); });
    comboboxTimes.setIndex(0);
    comboboxTimes.connect([this] { changeTime(); });
    hbox.addWidget(comboboxProduct);
    hbox.addWidget(comboboxSector);
    hbox.addWidget(comboboxTimes);
    box.addLayout(hbox);
    box.addWidgetAndCenter(photo);
    box.getAndShow(this);
    reload();
}

void Rtma::reload() {
    const auto url = UtilityRtma::getUrl(indexProduct, comboboxSector.getIndex(), comboboxTimes.getValue());
    Utility::writePrefInt(prefToken, indexProduct);
    const auto utcTime = comboboxTimes.getValue();
    auto objectDateTime = ObjectDateTime::parse(utcTime, "yyyyMMdd HH' UTC'");
    objectDateTime.utcToLocal();
    const auto timeString = objectDateTime.format("yyyyMMdd HH");
    setTitle(timeString);
    new FutureBytes{this, url, [this] (const auto& ba) { photo.setBytes(ba); }};
}

void Rtma::changeProduct() {
    indexProduct = comboboxProduct.getIndex();
    reload();
}

void Rtma::changeSector() {
    reload();
}

void Rtma::changeTime() {
    reload();
}
