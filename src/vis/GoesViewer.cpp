// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "vis/GoesViewer.h"
#include <QCloseEvent>
#include <vector>
#include "objects/FutureBytes.h"
#include "objects/WString.h"
#include "settings/Location.h"
#include "settings/UIPreferences.h"
#include "util/To.h"
#include "util/Utility.h"
#include "vis/UtilityGoes.h"

GoesViewer::GoesViewer(QWidget * parent, const string& url, const string& product, const string& sector)
    : Window{parent}
    , photo{ Photo{this, Full} }
    , comboboxSector{ ComboBox{this, UtilityGoes::sectors} }
    , comboboxProduct{ ComboBox{this, UtilityGoes::labels} }
    , comboboxCount{ ComboBox{this, {"6", "12", "18", "24"}} }
    , animateButton{ ButtonToggle{this, Play, "Animate ctrl-A"} }
    , objectAnimate{ ObjectAnimate{this, &photo, &UtilityGoes::getAnimation, [this] { reload(); }, &animateButton} }
    , goesFloater{ false }
    , shortcutAnimate{ Shortcut{QKeySequence{"A"}, this} }
{
    setTitle("GOES Viewer");
    if (!url.empty()) {
        goesFloater = true;
        goesFloaterUrl = url;
    }
    if (sector.empty()) {
        if (!UIPreferences::rememberGOES) {
            objectAnimate.sector = UtilityGoes::getNearest(Location::getLatLonCurrent());
        } else {
            objectAnimate.sector = Utility::readPref("REMEMBER_GOES_SECTOR", UtilityGoes::getNearest(Location::getLatLonCurrent()));
        }
    } else {
        objectAnimate.sector = sector;
    }
    if (product.empty()) {
        objectAnimate.product = "GEOCOLOR";
    } else {
        objectAnimate.product = product;
    }
    animateButton.connect([this] { objectAnimate.animateClicked(); });
    if (goesFloater) {
        objectAnimate.getFunction = &UtilityGoes::getAnimationGoesFloater;
        objectAnimate.sector = goesFloaterUrl;
    }
    comboboxSector.setIndexByValue(objectAnimate.sector);
    comboboxSector.connect([this] { changeSector(); });
    comboboxProduct.connect([this] { changeProduct(); });

    comboboxCount.setIndex(1);
    comboboxCount.connect([this] { changeCount(); });

    if (!goesFloater) {
        boxH.addWidget(comboboxSector);
    } else {
        comboboxSector.setVisible(false);
    }
    boxH.addWidget(comboboxProduct);
    boxH.addWidget(comboboxCount);
    boxH.addWidget(animateButton);
    box.addLayout(boxH);
    box.addWidgetAndCenter(photo);
    box.getAndShow(this);

    shortcutAnimate.connect([this] { objectAnimate.animateClicked(); });
    reload();
}

void GoesViewer::reload() {
    objectAnimate.stopAnimate();
    if (!goesFloater) {
        Utility::writePref("REMEMBER_GOES_SECTOR", objectAnimate.sector);
        new FutureBytes{this, UtilityGoes::getImage(objectAnimate.product, objectAnimate.sector), [this] (const auto& ba) { photo.setBytes(ba); }};
    } else {
        new FutureBytes{this, UtilityGoes::getImageGoesFloater(goesFloaterUrl, objectAnimate.product), [this] (const auto& ba) { photo.setBytes(ba); }};
    }
}

void GoesViewer::changeSector() {
    const auto tmp = comboboxSector.getValue();
    objectAnimate.sector = WString::split(tmp, ":")[0];
    reload();
}

void GoesViewer::changeProduct() {
    objectAnimate.product = UtilityGoes::codes[comboboxProduct.getIndex()];
    reload();
}

void GoesViewer::changeCount() {
    objectAnimate.frameCount = To::Int(comboboxCount.getValue());
}

void GoesViewer::closeEvent(QCloseEvent * event) {
    objectAnimate.stopAnimate();
    event->accept();
}
