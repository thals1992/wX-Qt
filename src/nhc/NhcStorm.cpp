// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "nhc/NhcStorm.h"
#include "objects/FutureBytes.h"
#include "objects/FutureText.h"
#include "objects/WString.h"
#include "nhc/UtilityNhc.h"
#include "util/UtilityList.h"
#include "vis/GoesViewer.h"

NhcStorm::NhcStorm(QWidget * parent, const NhcStormDetails& stormData)
    : Window{parent}
    , parent{ parent }
    , stormData{ stormData }
    , sw{ TwoWidgetScroll{this, boxImages, boxText} }
    , comboboxProduct{ ComboBox{this, UtilityNhc::stormTextProducts} }
    , goesButton{ Button{this, None, "GOES"} }
    , text{ Text{this} }
    , goesUrl{ stormData.goesUrl }
    , product{ "MIATCP" + stormData.binNumber }
{
    setTitle("NHC Storm " + stormData.forTopHeader());
    goesButton.connect([this] { launchGoes(); });
    for (const auto& url : UtilityNhc::urlEnds) {
        urls.push_back(stormData.baseUrl + url);
    }
    comboboxProduct.setIndex(0);
    comboboxProduct.connect([this] { changeProduct(); });
    boxText.addWidget(goesButton);
    boxText.addWidget(comboboxProduct);
    boxText.addWidget(text);
    for ([[maybe_unused]] const auto& unused : urls) {
        images.emplace_back(this, Scaled);
        boxImages.addWidget(images.back());
    }
    for (auto index : range(urls.size())) {
        new FutureBytes{this, urls[index], [this, index] (const auto& ba) { images[index].setBytes(ba); }};
    }
    reload();
}

void NhcStorm::reload() {
    new FutureText{this, product, [this] (const auto& s) { text.setText(s); }};
}

void NhcStorm::changeProduct() {
    product = WString::split(comboboxProduct.getValue(), ":")[0] + stormData.binNumber;
    reload();
}

void NhcStorm::launchGoes() {
    new GoesViewer{parent, goesUrl};
}
