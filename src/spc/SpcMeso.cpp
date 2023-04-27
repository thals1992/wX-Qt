// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/SpcMeso.h"
#include <algorithm>
#include "objects/FutureBytes.h"
#include "spc/UtilitySpcMeso.h"
#include "spc/UtilitySpcMesoInputOutput.h"
#include "util/Utility.h"
#include "util/UtilityList.h"

SpcMeso::SpcMeso(QWidget * parent)
    : Window{parent}
    , photo{ Photo{this, Full} }
    , comboboxSector{ ComboBox{this, UtilitySpcMeso::sectors} }
    , buttonBack{ Button{this, Left, ""} }
    , buttonForward{ Button{this, Right, ""} }
    , animateButton{ ButtonToggle{this, Play, "Animate ctrl-A"} }
    , objectAnimate{ ObjectAnimate{this, &photo, &UtilitySpcMesoInputOutput::getAnimation, [this] { reload(); }, &animateButton} }
    , shortcutAnimate{ Shortcut{QKeySequence{"A"}, this} }
    , shortcutLeft{ Shortcut{Qt::Key_Left, this} }
    , shortcutRight{ Shortcut{Qt::Key_Right, this} }
{
    setTitle("SPC Mesoanalysis");
    buttonBack.connect([this] { moveLeftClicked(); });
    buttonForward.connect([this] { moveRightClicked(); });

    objectAnimate.product = Utility::readPref(prefTokenProduct, "pmsl");
    objectAnimate.sector = Utility::readPref(prefTokenSector, "19");
    animateButton.connect([this] { objectAnimate.animateClicked(); });
    index = findex(objectAnimate.product, UtilitySpcMeso::products);

    comboboxSector.setIndex(findex(objectAnimate.sector, UtilitySpcMeso::sectorCodes));
    comboboxSector.connect([this] { changeSector(); });

    boxFav.addWidget(comboboxSector);
    boxFav.addWidget(animateButton);
    boxH.addWidget(buttonBack);
    boxH.addWidget(buttonForward);
    box.addLayout(boxH);

    auto j = 0;
    for (const auto& item : UtilitySpcMeso::favList) {
        buttons.emplace_back(this, None, "");
        buttons.back().setText(item);
        buttons.back().connect([this, j] { changeProductForFav(j); });
        boxFav.addWidget(buttons.back());
        j += 1;
    }
    boxFav.addStretch();

    imageLayout.addLayout(boxFav);
    imageLayout.addWidget(photo);
    box.addLayout(imageLayout);
    box.getAndShow(this);

    auto itemsSoFar = 0;
    for (auto& menu : UtilitySpcMeso::titles) {
        menu.setList(UtilitySpcMeso::labels, itemsSoFar);
        itemsSoFar += menu.count;
    }
    for (auto& menuTitle : UtilitySpcMeso::titles) {
        popoverMenus.emplace_back(this, menuTitle.title, menuTitle.get(), [this] (const auto& s) { changeProductByCode(s); });
        boxH.addWidget(popoverMenus.back());
    }
    shortcutAnimate.connect([this] { objectAnimate.animateClicked(); });
    shortcutLeft.connect([this] { moveLeftClicked(); });
    shortcutRight.connect([this] { moveRightClicked(); });
    reload();
}

void SpcMeso::moveLeftClicked() {
    index -= 1;
    index = std::max(index, 0);
    objectAnimate.product = UtilitySpcMeso::products[index];
    reload();
}

void SpcMeso::moveRightClicked() {
    index += 1;
    index = std::min(index, static_cast<int>(UtilitySpcMeso::products.size()) - 1);
    objectAnimate.product = UtilitySpcMeso::products[index];
    reload();
}

void SpcMeso::reload() {
    objectAnimate.stopAnimate();
    Utility::writePref(prefTokenProduct, objectAnimate.product);
    Utility::writePref(prefTokenSector, objectAnimate.sector);
    index = indexOf(UtilitySpcMeso::products, objectAnimate.product);
    setTitle(UtilitySpcMeso::labels[index]);
    new FutureBytes{this, getUrl(), [this] (const auto& ba) { photo.setBytes(ba); }};
}

void SpcMeso::changeProductForFav(int indexB) {
    const auto& b = UtilitySpcMeso::favList[indexB];
    index = findex(b, UtilitySpcMeso::products);
    objectAnimate.product = UtilitySpcMeso::products[index];
    reload();
}

void SpcMeso::changeProductByCode(const string& label) {
    index = findex(label, UtilitySpcMeso::labels);
    objectAnimate.product = UtilitySpcMeso::products[index];
    reload();
}

void SpcMeso::changeSector() {
    objectAnimate.sector = UtilitySpcMeso::sectorCodes[comboboxSector.getIndex()];
    reload();
}

string SpcMeso::getUrl() const {
    string gifUrl = ".gif";
    // if (UtilitySpcMeso::imgSf.contains(objectAnimate.product)) {
    if (contains(UtilitySpcMeso::imgSf, objectAnimate.product)) {
        gifUrl = "_sf.gif";
    }
    return "https://www.spc.noaa.gov/exper/mesoanalysis/s" + objectAnimate.sector + "/" + objectAnimate.product + "/" + objectAnimate.product + gifUrl;
}

void SpcMeso::closeEvent(QCloseEvent * event) {
    objectAnimate.stopAnimate();
    event->accept();
}
