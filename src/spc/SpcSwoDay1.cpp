// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/SpcSwoDay1.h"
#include "objects/FutureBytes.h"
#include "objects/FutureText.h"
#include "spc/UtilitySpcSwo.h"
#include "util/To.h"
#include "util/UtilityList.h"

SpcSwoDay1::SpcSwoDay1(QWidget * parent, const string& day)
    : Window{parent}
    , text{ Text{this} }
    , sw{ TwoWidgetScroll{this, imageVBox, text} }
{
    setTitle("SPC Convective Outlook Day " + day);
    if (To::Int(day) > 3) {
        urls = UtilitySpcSwo::getImageUrls("48");
    } else {
        urls = UtilitySpcSwo::getImageUrls(day);
    }
    for ([[maybe_unused]] const auto& unused : urls) {
        images.emplace_back(this);
        imageVBox.addWidget(images.back());
    }
    auto product = "SWODY" + day;
    if (day == "4" || day == "5" || day == "6" || day == "7" || day == "8" || day == "48") {
        product = "SWOD48";
    }
    new FutureText{this, product, [this] (const auto& s) { text.setText(s); }};
    for (auto index : range(urls.size())) {
        new FutureBytes{this, urls[index], [this, index] (const auto& ba) { images[index].setBytes(ba); }};
    }
}
