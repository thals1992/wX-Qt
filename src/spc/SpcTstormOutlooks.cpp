// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/SpcTstormOutlooks.h"
#include "objects/FutureBytes.h"
#include "spc/UtilitySpc.h"
#include "util/UtilityList.h"

SpcTstormOutlooks::SpcTstormOutlooks(QWidget * parent) : Window(parent) {
    setTitle("SPC Thunderstorm Outlooks");
    maximize();
    box = HBox(this);
    urls = UtilitySpc::getTstormOutlookUrls();
    box.addImageRow(urls, images);
    box.getAndShow(this);
    for (auto index : UtilityList::range(urls.size())) {
        const auto url = urls[index];
        new FutureBytes(this, url, [this, index] (const auto& ba) { images[index].setBytes(ba); });
    }
}
