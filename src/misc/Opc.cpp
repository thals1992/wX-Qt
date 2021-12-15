// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/Opc.h"
#include "objects/FutureBytes.h"
#include "misc/UtilityOpcImages.h"
#include "util/Utility.h"

Opc::Opc(QWidget * parent) : Window(parent) {
    setTitle("OPC");
    maximize();

    index = Utility::readPrefInt(prefToken, 0);
    photo = Photo(this, PhotoSizeEnum::full);
    box = VBox(this);

    comboboxProduct = ComboBox(this, UtilityOpcImages::labels);
    comboboxProduct.setIndexByValue(UtilityOpcImages::labels[index]);
    comboboxProduct.connect([this] { changeProduct(); });

    box.addWidget(comboboxProduct.get());
    box.addWidgetAndCenter(photo.get());
    box.getAndShow(this);

    reload();
}

void Opc::reload() {
    url = UtilityOpcImages::urls[index];
    Utility::writePrefInt(prefToken, index);
    new FutureBytes(this, url, [this] (const auto& ba) { photo.setBytes(ba); });
}

void Opc::changeProduct() {
    index = comboboxProduct.getIndex();
    reload();
}
