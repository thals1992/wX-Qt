// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/SpcFireWeatherOutlook.h"
#include "objects/FutureBytes.h"
#include "objects/FutureText.h"
#include "spc/UtilitySpcFireOutlook.h"
#include "util/To.h"

SpcFireWeatherOutlook::SpcFireWeatherOutlook(QWidget * parent, int day) : Window(parent) {
    setTitle("SPC Fire Weather Outlook Day " + To::String(day + 1));
    maximize();

    url = UtilitySpcFireOutlook::urls[day];
    product = UtilitySpcFireOutlook::products[day];

    photo = Photo(this, PhotoSizeEnum::scaled);
    text = Text(this, "");
    sw = ObjectTwoWidgetScroll(this, photo.get(), text.get());

    new FutureBytes(this, url, [this] (const auto& ba) { photo.setBytes(ba); });
    new FutureText(this, product, [this] (const auto& s) { text.setText(s); });
}
