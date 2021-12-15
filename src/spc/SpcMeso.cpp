// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/SpcMeso.h"
#include "objects/FutureBytes.h"
#include "spc/UtilitySpcMeso.h"
#include "spc/UtilitySpcMesoInputOutput.h"
#include "ui/Icon.h"
#include "util/Utility.h"
#include "util/UtilityList.h"

SpcMeso::SpcMeso(QWidget * parent) : Window(parent) {
    setTitle("SPC Mesoanalysis");
    maximize();
    boxH = HBox(this);
    imageLayout = HBox(this);
    boxFav = VBox(this);
    box = VBox(this);
    photo = Photo(this, PhotoSizeEnum::full);

    buttonBack = Button(this, Icon::Left, "");
    buttonBack.connect([this] { moveLeftClicked(); });
    buttonForward = Button(this, Icon::Right, "");
    buttonForward.connect([this] { moveRightClicked(); });

    animateButton = ButtonToggle(this, Icon::Play, "Animate ctrl-A");
    objectAnimate = new ObjectAnimate(this, &photo, &UtilitySpcMesoInputOutput::getAnimation, [this] { reload(); }, &animateButton);
    objectAnimate->product = Utility::readPref(prefTokenProduct, "pmsl");
    objectAnimate->sector = Utility::readPref(prefTokenSector, "19");
    animateButton.connect([this] { objectAnimate->animateClicked(); });
    index = UtilityList::findex(objectAnimate->product, UtilitySpcMeso::products);
    indexSector = UtilityList::findex(objectAnimate->sector, UtilitySpcMeso::sectorCodes);

    comboboxSector = ComboBox(this, UtilitySpcMeso::sectors);
    comboboxSector.setIndex(UtilityList::findex(objectAnimate->sector, UtilitySpcMeso::sectorCodes));
    comboboxSector.connect([this] { changeSector(); });

    boxFav.addWidget(comboboxSector.get());
    boxFav.addWidget(animateButton.get());

    boxH.addWidget(buttonBack.get());
    boxH.addWidget(buttonForward.get());
    box.addLayout(boxH.get());

    auto j = 0;
    for (const auto& item : UtilitySpcMeso::favList) {
        auto button = Button(this, "");
        buttons.push_back(button);
        button.setText(item);
        button.connect([this, j]{ changeProductForFav(j); });
        boxFav.addWidget(button.get());
        j += 1;
    }
    boxFav.addStretch();

    imageLayout.addLayout(boxFav.get());
    imageLayout.addWidget(photo.get());
    box.addLayout(imageLayout.get());
    box.getAndShow(this);

    int itemsSoFar = 0;
    for (auto& menu : UtilitySpcMeso::titles) {
        menu.setList(UtilitySpcMeso::labels, itemsSoFar);
        itemsSoFar += menu.count;
    }
    for (auto& objectMenuTitle : UtilitySpcMeso::titles) {
        popoverMenus.push_back(PopoverMenu(this, objectMenuTitle.title, objectMenuTitle.get(), [this] (QString s) { changeProductByCode(s); }));
        boxH.addWidget(popoverMenus.back().get());
    }

    shortcutAnimate = Shortcut(QKeySequence("Ctrl+A"), this);
    shortcutAnimate.connect([this] { objectAnimate->animateClicked(); });

    shortcutLeft = Shortcut(Qt::CTRL | Qt::Key_Left, this);
    shortcutLeft.connect([this] { moveLeftClicked(); });

    shortcutRight = Shortcut(Qt::CTRL | Qt::Key_Right, this);
    shortcutRight.connect([this] { moveRightClicked(); });

    reload();
}

void SpcMeso::moveLeftClicked() {
    index -= 1;
    index = std::max(index, 0);
    objectAnimate->product = UtilitySpcMeso::products[index];
    reload(); 
}

void SpcMeso::moveRightClicked() {
    index += 1;
    index = std::min(index, static_cast<int>(UtilitySpcMeso::products.size()) - 1);
    objectAnimate->product = UtilitySpcMeso::products[index];
    reload(); 
}

void SpcMeso::reload() {
    objectAnimate->stopAnimate();
    Utility::writePref(prefTokenProduct, objectAnimate->product);
    Utility::writePref(prefTokenSector, objectAnimate->sector);
    url = getUrl();
    index = UtilityList::indexOf(UtilitySpcMeso::products, objectAnimate->product);
    setTitle(UtilitySpcMeso::labels[index]);
    new FutureBytes(this, url, [this] (const auto& ba) { photo.setBytes(ba); });
}

void SpcMeso::changeProductForFav(int indexB) {
    auto b = UtilitySpcMeso::favList[indexB];
    auto index = UtilityList::findex(b, UtilitySpcMeso::products);
    objectAnimate->product = UtilitySpcMeso::products[index];
    reload();
}

void SpcMeso::changeProductByCode(const QString& label) {
    index = UtilityList::findex(label, UtilitySpcMeso::labels);
    objectAnimate->product = UtilitySpcMeso::products[index];
    reload();
}

void SpcMeso::changeSector() {
    objectAnimate->sector = UtilitySpcMeso::sectorCodes[comboboxSector.getIndex()];
    reload();
}

QString SpcMeso::getUrl() {
    QString gifUrl = ".gif";
    if (UtilitySpcMeso::imgSf.contains(objectAnimate->product)) {
        gifUrl = "_sf.gif";
    }
    url = "https://www.spc.noaa.gov/exper/mesoanalysis/s" + objectAnimate->sector + "/" + objectAnimate->product + "/" + objectAnimate->product + gifUrl;
    return url;
}

void SpcMeso::closeEvent(QCloseEvent * event) {
    objectAnimate->stopAnimate();
    event->accept();
}
