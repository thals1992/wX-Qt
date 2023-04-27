// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/SpcCompMap.h"
#include <algorithm>
#include "objects/FutureBytes.h"
#include "spc/UtilitySpcCompmap.h"
#include "util/Utility.h"
#include "util/UtilityList.h"

SpcCompMap::SpcCompMap(QWidget * parent)
    : Window{parent}
    , photo{ Photo{this, Full} }
    , comboboxProduct{ ComboBox{this, UtilitySpcCompmap::labels} }
    , buttonBack{ Button{this, Left, ""} }
    , buttonForward{ Button{this, Right, ""} }
    , product{ Utility::readPref(prefToken, "0") }
    , index{ indexOf(UtilitySpcCompmap::urlIndices, product) }
{
    setTitle("SPC Compmap");
    buttonBack.connect([this] {
        index -= 1;
        index = std::max(index, 0);
        comboboxProduct.setIndex(index);
        reload();
    });
    buttonForward.connect([this] {
        index += 1;
        index = std::min(index, static_cast<int>(UtilitySpcCompmap::urlIndices.size()) - 1);
        comboboxProduct.setIndex(index);
        reload();
    });
    comboboxProduct.setIndex(index);
    comboboxProduct.connect([this] { changeProduct(); });
    buttonBox.addWidget(buttonBack);
    buttonBox.addWidget(buttonForward);
    buttonBox.addWidget(comboboxProduct);
    box.addLayout(buttonBox);
    box.addWidgetAndCenter(photo);
    box.getAndShow(this);
    reload();
}

void SpcCompMap::reload() {
    Utility::writePref(prefToken, product);
    auto url = UtilitySpcCompmap::getImage(product);
    setTitle("SPC Compmap - " + comboboxProduct.getValue());
    new FutureBytes{this, url, [this] (const auto& ba) { photo.setBytes(ba); }};
}

void SpcCompMap::changeProduct() {
    index = comboboxProduct.getIndex();
    product = UtilitySpcCompmap::urlIndices[index];
    reload();
}
