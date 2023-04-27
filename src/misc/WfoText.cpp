// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/WfoText.h"
#include "common/GlobalArrays.h"
#include "misc/UtilityWfoText.h"
#include "objects/FutureText.h"
#include "objects/WString.h"
#include "settings/Location.h"
#include "util/UtilityList.h"
#include "util/UtilityUI.h"

WfoText::WfoText(QWidget * parent)
    : Window{parent}
    , sw{ ScrolledWindow{this, box} }
    , comboboxProduct{ ComboBox{this, UtilityWfoText::wfoProdList} }
    , comboboxSector{ ComboBox{this, GlobalArrays::wfos} }
    , sector{ Location::office() }
{
    setTitle("WFO Text");
    maximize();

    box.addMargins();
    comboboxProduct.setIndexByValue("AFD");
    comboboxProduct.connect([this] { changeProduct(); });
    boxH.addWidget(comboboxProduct);

    comboboxSector.setIndexByValue(sector);
    comboboxSector.connect([this] { changeSector(); });

    boxH.addWidget(comboboxSector);
    box.addLayout(boxH);
    box.addLayout(boxText);

    if (UtilityUI::isMobile()) {
        productCount = 1;
    }
    for ([[maybe_unused]] auto unused : range(productCount)) {
        textList.emplace_back(this);
        textList.back().setFixedWidth();
        boxText.addWidget(textList.back());
    }
    reload();
}

void WfoText::changeProduct() {
    product = WString::split(comboboxProduct.getValue(), ":")[0];
    reload();
}

void WfoText::changeSector() {
    sector = WString::split(comboboxSector.getValue(), ":")[0];
    reload();
}

void WfoText::reload() {
    const vector<string> products{product, "HWO", "LSR"};
    for (auto i : range(productCount)) {
        new FutureText{this, products[i] + sector, [this, i] (const auto& s) { textList[i].setText(s); }};
    }
}
