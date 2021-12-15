// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/SpcSwoSummary.h"
#include "objects/FutureBytes.h"
#include "spc/SpcSwoDay1.h"
#include "spc/UtilitySpcSwo.h"
#include "util/To.h"
#include "util/UtilityList.h"

SpcSwoSummary::SpcSwoSummary(QWidget * parent) : Window(parent) {
    setTitle("SPC Convective Outlooks");
    maximize();
    box = VBox(this);
    int numberAcross = 4;

    for (const auto& day : day1to3List) {
        auto items = UtilitySpcSwo::getImageUrls(day);
        urls.push_back(items[0]);
    }
    for (const auto& day : day4To8List) {
        urls.push_back(UtilitySpcSwo::getImageUrlsDays48(day));
    }
    box.addImageRows(urls, images, numberAcross);
    box.addStretch();
    sw = ScrolledWindow(this, box);
    for (auto index : UtilityList::range(urls.size())) {
        const auto url = urls[index];
        images[index].connect([this, index] { launch(index); });
        images[index].setNumberAcross(numberAcross);
        new FutureBytes(this, url, [this, index] (const auto& ba) { images[index].setBytes(ba); });
    }

    for (auto index : UtilityList::range(urls.size() + 1)) {
        shortcuts.push_back(Shortcut(QKeySequence("Ctrl+" + To::String(index)), this));
        shortcuts.back().connect([this, index] { launch(index - 1); });
    }
}

void SpcSwoSummary::launch(int index) {
    qDebug() << index;
    new SpcSwoDay1(this, To::String(index + 1));
}
