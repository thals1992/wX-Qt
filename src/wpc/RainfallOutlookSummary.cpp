// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "wpc/RainfallOutlookSummary.h"
#include "objects/FutureBytes.h"
#include "util/UtilityList.h"
#include "wpc/RainfallOutlook.h"
#include "wpc/UtilityWpcRainfallOutlook.h"

RainfallOutlookSummary::RainfallOutlookSummary(QWidget * parent) : Window{parent}  {
    setTitle("Excessive Rainfall Outlook");
    const auto urls = UtilityWpcRainfallOutlook::urls;
    box.addImageRow(this, urls, images);
    box.getAndShow(this);
    for (auto index : range(urls.size())) {
        images[index].connect([this, index] { new RainfallOutlook{this, index}; });
        images[index].setNumberAcross(5);
        new FutureBytes{this, urls[index], [this, index] (const auto& ba) { images[index].setBytes(ba); }};
    }
}
