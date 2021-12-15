// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/Observations.h"
#include "misc/UtilityObservations.h"
#include "objects/FutureBytes.h"
#include "ui/PhotoSizeEnum.h"
#include "util/Utility.h"

Observations::Observations(QWidget * parent) : Window(parent) {
    setTitle("Observations");
    maximize();
    index = Utility::readPrefInt(prefToken, 0);
    url = UtilityObservations::urls[index];

    photo = Photo(this, PhotoSizeEnum::full);
    box = VBox(this);

    comboboxProduct = ComboBox(this, UtilityObservations::labels);
    comboboxProduct.setIndexByValue(UtilityObservations::labels[index]);
    comboboxProduct.connect([this] { changeProduct(); });

    box.addWidget(comboboxProduct.get());
    box.addWidgetAndCenter(photo.get());
    box.getAndShow(this);

    reload();
}

void Observations::reload() {
    auto url = UtilityObservations::urls[index];
    Utility::writePrefInt(prefToken, index);
    new FutureBytes(this, url, [this] (const auto& ba) { photo.setBytes(ba); });
}

void Observations::changeProduct() {
    index = comboboxProduct.getIndex();
    reload();
}
