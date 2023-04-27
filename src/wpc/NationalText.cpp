// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "wpc/NationalText.h"
#include <algorithm>
#include "objects/FutureText.h"
#include "objects/WString.h"
#include "ui/Icon.h"
#include "util/Utility.h"
#include "util/UtilityList.h"
#include "wpc/UtilityWpcText.h"

NationalText::NationalText(QWidget * parent, const string& prod)
    : Window{parent}
    , sw{ ScrolledWindow{this, box} }
    , text { Text{parent} }
    , buttonBack{ Button{this, Left, ""} }
    , buttonForward{ Button{this, Right, ""} }
{
    setTitle("National Text Products");
    if (prod.empty()) {
        product = "PMDSPD";
        product = Utility::readPref(prefTokenProduct, product);
        savePref = true;
    } else {
        product = WString::toLower(prod);
        savePref = false;
    }
    buttonBack.connect([this] {
        index -= 1;
        index = std::max(index, 0);
        product = WString::split(UtilityWpcText::labels[index], ":")[0];
        reload();
    });
    buttonForward.connect([this] {
        index += 1;
        index = std::min(index, static_cast<int>(UtilityWpcText::labels.size()) - 1);
        product = WString::split(UtilityWpcText::labels[index], ":")[0];
        reload();
    });
    hbox.addWidget(buttonBack);
    hbox.addWidget(buttonForward);
    box.addLayout(hbox);
    box.addWidget(text);
    box.addStretch();

    auto itemsSoFar = 0;
    for (auto& menu : UtilityWpcText::titles) {
        menu.setList(UtilityWpcText::labels, itemsSoFar);
        itemsSoFar += menu.count;
    }
    for (auto& objectMenuTitle : UtilityWpcText::titles) {
        popoverMenus.emplace_back(this, objectMenuTitle.title, objectMenuTitle.get(), [this] (const auto& s) { changeProductByCode(s); });
        hbox.addWidget(popoverMenus.back());
    }
    reload();
}

void NationalText::reload() {
    if (savePref) {
        Utility::writePref(prefTokenProduct, product);
    }
    index = findex(product, UtilityWpcText::labels);
    setTitle(UtilityWpcText::labels[index]);
    new FutureText{this, product, [this] (const auto& s) { text.setText(s); }};
}

void NationalText::changeProductByCode(const string& s) {
    product = WString::split(s, ":")[0];
    reload();
}
