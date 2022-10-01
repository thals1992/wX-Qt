// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "nhc/ObjectCardNhcStormReportItem.h"
#include "objects/WString.h"
#include "misc/ImageViewer.h"
#include "nhc/NhcStorm.h"
#include "util/UtilityMath.h"

ObjectCardNhcStormReportItem::ObjectCardNhcStormReportItem(QWidget * parent, const ObjectNhcStormDetails& stormData)
    : HBox()
    , stormData{ stormData }
    , parent{ parent }
    , button{ Button{parent, None, "Show Details - &" + stormData.name} }
    , image{ Image{parent} }
    , topLine{ Text{parent, stormData.name + " (" + stormData.classification + ") " + stormData.center} }
    , lastUpdateLine{ Text{parent, stormData.getUpdateTime()} }
    , startTimeLine{ Text{parent, "Moving " + UtilityMath::convertWindDir(stormData.movementDir) + " at " + stormData.movementSpeed + " mph"} }
    , endTimeLine{ Text{parent, "Min pressure: " + stormData.pressure + " mb"} }
    , maxWindLine{ Text{parent, "Max sustained: " + stormData.intensity + " mph"} }
    , middleLine{ Text{parent, stormData.status + " " + stormData.binNumber + " " + WString::toUpper(stormData.stormId)} }
{
    topLine.setBold();
    button.connect([this] { launch(); });

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
    textLayout.addStretch();
    addLayout(textLayout.get(), 1);
}

void ObjectCardNhcStormReportItem::launch() {
    new NhcStorm{parent, stormData};
}

void ObjectCardNhcStormReportItem::launchImage() {
    new ImageViewer{parent, stormData.coneBytes};
}
