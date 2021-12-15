// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "nhc/NhcStorm.h"
#include "objects/FutureBytes.h"
#include "objects/FutureText.h"
#include "nhc/UtilityNhc.h"
#include "util/UtilityList.h"
#include "vis/GoesViewer.h"

NhcStorm::NhcStorm(QWidget * parent, const ObjectNhcStormDetails& stormData) : Window(parent) {
    this->stormData = stormData;
    this->parent = parent;
    setTitle("NHC Storm " + stormData.forTopHeader());
    maximize();
    goesUrl = stormData.goesUrl;
    product = "";
    boxImages = VBox(this);
    goesButton = Button(this, "GOES");
    goesButton.connect([this] { launchGoes(); });
    text = Text(this, "");
    for (const auto& url : UtilityNhc::urlEnds) {
        urls.push_back(stormData.baseUrl + url);
    }

    product = "MIATCP" + stormData.binNumber;

    comboboxProduct = ComboBox(this, UtilityNhc::stormtextProducts);
    comboboxProduct.setIndex(0);
    comboboxProduct.connect([this] { changeProduct(); });

    boxText.addWidget(goesButton.get());
    boxText.addWidget(comboboxProduct.get());
    boxText.addWidget(text.get());

    imageVBox = VBox(this);
    for ([[maybe_unused]] const auto& unused : urls) {
        images.push_back(Photo(this, PhotoSizeEnum::scaled));
        boxImages.addWidget(images.back().get());
    }

    sw = ObjectTwoWidgetScroll(this, boxImages.get(), boxText.get());

    for (auto index : UtilityList::range(urls.size())) {
        new FutureBytes(this, urls[index], [this, index] (const auto& ba) { images[index].setBytes(ba); });
    }
    reload();
}

void NhcStorm::reload() {
    new FutureText(this, product, [this] (const auto& s) { text.setText(s); });
}

void NhcStorm::changeProduct() {
    product = comboboxProduct.getValue().split(":")[0] + stormData.binNumber;
    reload();
}

void NhcStorm::launchGoes() {
    new GoesViewer(parent, goesUrl);
}
