// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/SpcFireSummary.h"
#include "objects/FutureBytes.h"
#include "spc/SpcFireWeatherOutlook.h"
#include "spc/UtilitySpcFireOutlook.h"
#include "util/UtilityList.h"

SpcFireSummary::SpcFireSummary(QWidget * parent)
    : Window{parent}
    , urls{ UtilitySpcFireOutlook::urls }
{
    setTitle("SPC Fire Weather Outlooks");
    box.addImageRow(this, urls, images);
    box.getAndShow(this);
    for (auto index : range(urls.size())) {
        images[index].connect([this, index] { new SpcFireWeatherOutlook{this, index}; });
        new FutureBytes{this, urls[index], [this, index] (const auto& ba) { images[index].setBytes(ba); }};
    }
}
