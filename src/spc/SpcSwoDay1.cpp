// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/SpcSwoDay1.h"
#include "objects/FutureBytes.h"
#include "objects/FutureText.h"
#include "spc/UtilitySpcSwo.h"
#include "ui/PhotoSizeEnum.h"
#include "util/To.h"
#include "util/UtilityList.h"

SpcSwoDay1::SpcSwoDay1(QWidget * parent, const QString& day) : Window(parent) {
    setTitle("SPC Convective Outlook Day " + day);
    maximize();
    if (To::Int(day) > 3) {
        urls = UtilitySpcSwo::getImageUrls("48");
    } else {
        urls = UtilitySpcSwo::getImageUrls(day);
    }
    imageVBox = VBox(this);
    for ([[maybe_unused]] const auto& unused : urls) {
        images.push_back(Photo(this, PhotoSizeEnum::scaled));
        imageVBox.addWidget(images.back().get());
    }
    product = "";
    if (day == "4" || day == "5" || day == "6" || day == "7" || day == "8" || day == "48") {
        product = "SWOD48";
    } else {
        product = "SWODY" + day;
    }
    text = Text(this, "");
    sw = ObjectTwoWidgetScroll(this, imageVBox.get(), text.get());
    new FutureText(this, product, [this] (const auto& s) { text.setText(s); });
    for (auto index : UtilityList::range(urls.size())) {
        auto url = urls[index];
        new FutureBytes(this, url, [this, index] (const auto& ba) { images[index].setBytes(ba); });
    }
}
