// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/SpcCompMap.h"
#include "objects/FutureBytes.h"
#include "spc/UtilitySpcCompmap.h"
#include "util/Utility.h"

SpcCompMap::SpcCompMap(QWidget * parent) : Window(parent) {
    setTitle("SPC Compmap");
    maximize();
    product = Utility::readPref(prefToken, "0");
    photo = Photo(this, PhotoSizeEnum::full);

    comboboxProduct = ComboBox(this, UtilitySpcCompmap::labels);
    comboboxProduct.setIndex(UtilitySpcCompmap::urlIndices.indexOf(product));
    comboboxProduct.connect([this] { changeProduct(); });

    box = VBox(this);
    box.addWidget(comboboxProduct.get());
    box.addWidgetAndCenter(photo.get());
    box.getAndShow(this);

    reload();
}

void SpcCompMap::reload() {
    Utility::writePref(prefToken, product);
    auto url = UtilitySpcCompmap::getImage(product);
    new FutureBytes(this, url, [this] (const auto& ba) { photo.setBytes(ba); });
}

void SpcCompMap::changeProduct() {
    product = UtilitySpcCompmap::urlIndices[comboboxProduct.getIndex()];
    reload();
}
