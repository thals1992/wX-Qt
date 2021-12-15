// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/SpcFireSummary.h"
#include "objects/FutureBytes.h"
#include "spc/SpcFireWeatherOutlook.h"
#include "spc/UtilitySpcFireOutlook.h"
#include "util/UtilityList.h"

SpcFireSummary::SpcFireSummary(QWidget * parent) : Window(parent) {
    setTitle("SPC Fire Weather Outlooks");
    maximize();
    urls = UtilitySpcFireOutlook::urls;
    box = HBox(this);
    box.addImageRow(urls, images);
    box.getAndShow(this);
    for (auto index : UtilityList::range(urls.size())) {
        images[index].connect([this, index] { launch(index); });
        auto url = urls[index];
        new FutureBytes(this, url, [this, index] (const auto& ba) { images[index].setBytes(ba); });
    }
}

void SpcFireSummary::launch(int index) {
    new SpcFireWeatherOutlook(this, index);
}
