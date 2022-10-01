// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/SpcSwoSummary.h"
#include "objects/FutureBytes.h"
#include "spc/SpcSwoDay1.h"
#include "spc/UtilitySpcSwo.h"
#include "util/To.h"
#include "util/UtilityList.h"

SpcSwoSummary::SpcSwoSummary(QWidget * parent)
    : Window{parent}
    , sw{ ScrolledWindow{this, box} }
{
    setTitle("SPC Convective Outlooks");
    const auto numberAcross = 4;
    for (const auto& day : day1to3List) {
        const auto items = UtilitySpcSwo::getImageUrls(day);
        urls.push_back(items[0]);
    }
    for (const auto& day : day4To8List) {
        urls.push_back(UtilitySpcSwo::getImageUrlsDays48(day));
    }
    box.addImageRows(this, urls, images, numberAcross);
    box.addStretch();
    for (auto index : range(urls.size())) {
        images[index].connect([this, index] { new SpcSwoDay1{this, To::string(index + 1)}; });
        images[index].setNumberAcross(numberAcross);
        new FutureBytes{this, urls[index], [this, index] (const auto& ba) { images[index].setBytes(ba); }};
    }
    for (auto index : range(urls.size() + 1)) {
        shortcuts.emplace_back(QKeySequence{"Ctrl+" + QString::fromStdString(To::string(index))}, this);
        shortcuts.back().connect([this, index] { new SpcSwoDay1{this, To::string(index)}; });
    }
}
