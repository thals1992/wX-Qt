// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "nhc/ObjectCardNhcStormReportItem.h"
#include "misc/ImageViewer.h"
#include "nhc/NhcStorm.h"
#include "util/UtilityMath.h"

ObjectCardNhcStormReportItem::ObjectCardNhcStormReportItem(QWidget * parent, const ObjectNhcStormDetails& stormData) : HBox(parent) {
    this->parent = parent;
    this->stormData = stormData;

    textLayout = VBox(parent);

    topLine = Text(parent, stormData.name + " (" + stormData.classification + ") " + stormData.center);
    topLine.setBold();
    lastUpdateLine = Text(parent, stormData.getUpdateTime());
    startTimeLine = Text(parent, "Moving " + UtilityMath::convertWindDir(stormData.movementDir) + " at " + stormData.movementSpeed + " mph");
    endTimeLine = Text(parent, "Min pressure: " + stormData.pressure + " mb");
    maxWindLine = Text(parent, "Max sustained: " + stormData.intensity + " mph");
    middleLine = Text(parent, stormData.status + " " + stormData.binNumber + " " + stormData.id.toUpper());

    button = Button(parent, "Show Details - &" + stormData.name);
    button.connect([this] { launch(); });

    image = Image::withIndex(parent, 0);
    image.imageSize = 250;
    image.connect([this] { launchImage(); });
    image.setBytes(stormData.coneBytes);

    addWidget(image.get());

    textLayout.addWidget(button.get());
    textLayout.addWidget(topLine.get());
    textLayout.addWidget(lastUpdateLine.get());
    textLayout.addWidget(startTimeLine.get());
    textLayout.addWidget(endTimeLine.get());
    textLayout.addWidget(maxWindLine.get());
    textLayout.addWidget(middleLine.get());

    addLayout(textLayout.get());
}

void ObjectCardNhcStormReportItem::launch() {
    auto window = new NhcStorm(parent, stormData);
    window->show();
}

void ObjectCardNhcStormReportItem::launchImage() {
    new ImageViewer(parent, stormData.coneBytes);
}
