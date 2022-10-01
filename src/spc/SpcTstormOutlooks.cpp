// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/SpcTstormOutlooks.h"
#include "objects/FutureBytes.h"
#include "spc/UtilitySpc.h"
#include "util/UtilityList.h"

SpcTstormOutlooks::SpcTstormOutlooks(QWidget * parent) : Window{parent} {
    setTitle("SPC Thunderstorm Outlooks");
    const auto urls = UtilitySpc::getTstormOutlookUrls();
    box.addImageRow(this, urls, images);
    box.getAndShow(this);
    for (auto index : range(urls.size())) {
        new FutureBytes{this, urls[index], [this, index] (const auto& ba) { images[index].setBytes(ba); }};
    }
}
