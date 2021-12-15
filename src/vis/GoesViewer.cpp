// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "vis/GoesViewer.h"
#include <QCloseEvent>
#include "objects/FutureBytes.h"
#include "settings/Location.h"
#include "ui/Icon.h"
#include "vis/UtilityGoes.h"

GoesViewer::GoesViewer(QWidget * parent, QString url, QString product, QString sector) : Window(parent) {
    setTitle("GOES Viewer");
    maximize();

    goesFloater = false;
    goesFloaterUrl = "";
    if (url != "") {
        goesFloater = true;
        goesFloaterUrl = url;
    }

    box = VBox(this);
    boxH = HBox(this);
    photo = Photo(this, PhotoSizeEnum::full);

    animateButton = ButtonToggle(this, Icon::Play, "Animate ctrl-A");
    objectAnimate = new ObjectAnimate(this, &photo, &UtilityGoes::getAnimation, [this] { reload(); }, &animateButton);

    // objectAnimate->sector = UtilityGoes::getNearestGoesLocation(Location::getLatLonCurrent());
    // objectAnimate->product = "GEOCOLOR";

    if (sector == "") {
        objectAnimate->sector = UtilityGoes::getNearestGoesLocation(Location::getLatLonCurrent());
    } else {
        objectAnimate->sector = sector;
    }
    if (product == "") {
        objectAnimate->product = "GEOCOLOR";
    } else {
        objectAnimate->product = product;
    }

    animateButton.connect([this] { objectAnimate->animateClicked(); });

    if (goesFloater) {
        objectAnimate->getFunction = &UtilityGoes::getAnimationGoesFloater;
        objectAnimate->sector = goesFloaterUrl;
    }

    comboboxSector = ComboBox(this, UtilityGoes::sectors);
    comboboxSector.setIndexByValue(objectAnimate->sector);
    comboboxSector.connect([this] { changeSector(); });

    comboboxProduct = ComboBox(this, UtilityGoes::labels);
    comboboxProduct.connect([this] { changeProduct(); });

    if (!goesFloater) {
        boxH.addWidget(comboboxSector.get());
    }
    boxH.addWidget(comboboxProduct.get());
    boxH.addWidget(animateButton.get());
    box.addLayout(boxH.get());
    box.addWidgetAndCenter(photo.get());
    box.getAndShow(this);

    shortcutAnimate = Shortcut(QKeySequence("Ctrl+A"), this);
    shortcutAnimate.connect([this] { objectAnimate->animateClicked(); });

    reload();
}

void GoesViewer::reload() {
    objectAnimate->stopAnimate();
    if (!goesFloater) {
        new FutureBytes(this, UtilityGoes::getImage(objectAnimate->product, objectAnimate->sector), [this] (const auto& ba) { photo.setBytes(ba); });
    } else {
        new FutureBytes(this, UtilityGoes::getImageGoesFloater(goesFloaterUrl, objectAnimate->product), [this] (const auto& ba) { photo.setBytes(ba); });
    }
}

void GoesViewer::changeSector() {
    objectAnimate->sector = UtilityGoes::sectors[comboboxSector.getIndex()];
    objectAnimate->sector = objectAnimate->sector.split(":")[0];
    reload();
}

void GoesViewer::changeProduct() {
    objectAnimate->product = UtilityGoes::codes[comboboxProduct.getIndex()];
    reload();
}

void GoesViewer::closeEvent(QCloseEvent * event) {
    objectAnimate->stopAnimate();
    event->accept();
}
