// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/WfoText.h"
#include "common/GlobalArrays.h"
#include "misc/UtilityWfoText.h"
#include "objects/FutureText.h"
#include "settings/Location.h"
#include "util/UtilityList.h"

WfoText::WfoText(QWidget * parent) : Window(parent) {
    setWindowTitle("WFO Text");
    maximize();

    boxH = HBox(this);
    box = VBox(this);
    boxText = HBox(this);

    box.addMargins();
    text = Text(this, "");

    sector = Location::office();

    comboboxProduct = ComboBox(this, UtilityWfoText::wfoProdList);
    comboboxProduct.setIndexByValue("AFD");
    comboboxProduct.connect([this] { changeProduct(); });
    boxH.addWidget(comboboxProduct.get());

    comboboxSector = ComboBox(this, GlobalArrays::wfos);
    comboboxSector.setIndexByValue(sector);
    comboboxSector.connect([this] { changeSector(); });
    boxH.addWidget(comboboxSector.get());

    box.addLayout(boxH.get());
    box.addLayout(boxText.get());
    for ([[maybe_unused]] auto unused : UtilityList::range(3)) {
        textList.push_back(Text(this, ""));
        textList.back().setFixedWidth();
        boxText.addWidget(textList.back().get());
    }
    sw = ScrolledWindow(this, box);
    reload();
}

void WfoText::changeProduct() {
    product = comboboxProduct.getValue().split(":")[0];
    reload();
}

void WfoText::changeSector() {
    sector = comboboxSector.getValue().split(":")[0];
    reload();
}

void WfoText::reload() {
    auto i = 0;
    QStringList products = {product, "HWO", "LSR"};
    for (const auto& product : products) {
        new FutureText(this, product + sector, [this, i] (const auto& s) { textList[i].setText(s); });
        i += 1;
    }
}
