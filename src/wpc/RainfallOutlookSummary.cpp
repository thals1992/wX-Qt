// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "wpc/RainfallOutlookSummary.h"
#include "objects/FutureBytes.h"
#include "util/UtilityList.h"
#include "wpc/RainfallOutlook.h"
#include "wpc/UtilityWpcRainfallOutlook.h"

RainfallOutlookSummary::RainfallOutlookSummary(QWidget * parent) : Window(parent)  {
    setTitle("Excessive Rainfall Outlook");
    maximize();
    urls = UtilityWpcRainfallOutlook::urls;
    box = HBox(this);
    box.addImageRow(urls, images);
    box.getAndShow(this);
    for (auto index : UtilityList::range(urls.size())) {
        auto url = urls[index];
        images[index].connect([this, index] { launch(index); });
        new FutureBytes(this, url, [this, index] (const auto& ba) { images[index].setBytes(ba); });
    }
}

void RainfallOutlookSummary::launch(int index) {
    new RainfallOutlook(this, index);
}
