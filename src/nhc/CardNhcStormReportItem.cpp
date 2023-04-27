// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "nhc/CardNhcStormReportItem.h"
#include "objects/WString.h"
#include "misc/ImageViewer.h"
#include "nhc/NhcStorm.h"
#include "util/UtilityMath.h"

CardNhcStormReportItem::CardNhcStormReportItem(QWidget * parent, const NhcStormDetails& stormData)
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

    addWidget(image);

    textLayout.addWidget(button);
    textLayout.addWidget(topLine);
    textLayout.addWidget(lastUpdateLine);
    textLayout.addWidget(startTimeLine);
    textLayout.addWidget(endTimeLine);
    textLayout.addWidget(maxWindLine);
    textLayout.addWidget(middleLine);
    textLayout.addStretch();
    addLayout(textLayout, 1);
}

void CardNhcStormReportItem::launch() {
    new NhcStorm{parent, stormData};
}

void CardNhcStormReportItem::launchImage() {
    new ImageViewer{parent, stormData.coneBytes};
}
