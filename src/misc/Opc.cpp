// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/Opc.h"
#include "objects/FutureBytes.h"
#include "misc/UtilityOpcImages.h"
#include "util/Utility.h"

Opc::Opc(QWidget * parent)
    : Window{parent}
    , photo{ Photo{this, Full} }
    , comboboxProduct{ ComboBox{this, UtilityOpcImages::labels} }
    , index{ Utility::readPrefInt(prefToken, 0) }
{
    setTitle("OPC");
    comboboxProduct.setIndexByValue(UtilityOpcImages::labels[index]);
    comboboxProduct.connect([this] { changeProduct(); });
    box.addWidget(comboboxProduct);
    box.addWidgetAndCenter(photo);
    box.getAndShow(this);
    reload();
}

void Opc::reload() {
    const auto& url = UtilityOpcImages::urls[index];
    Utility::writePrefInt(prefToken, index);
    new FutureBytes{ this, url, [this] (const auto& ba) { photo.setBytes(ba); } };
}

void Opc::changeProduct() {
    index = comboboxProduct.getIndex();
    reload();
}
