// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "wpc/RainfallOutlook.h"
#include "objects/FutureBytes.h"
#include "objects/FutureText.h"
#include "util/To.h"
#include "wpc/UtilityWpcRainfallOutlook.h"

RainfallOutlook::RainfallOutlook(QWidget * parent, int day) : Window(parent) {
    setTitle("Excessive Rainfall Outlook Day " + To::String(day + 1));
    maximize();

    url = UtilityWpcRainfallOutlook::urls[day];
    product = UtilityWpcRainfallOutlook::codes[day];

    photo = Photo(this, PhotoSizeEnum::scaled);
    text = Text(this, "");
    sw = ObjectTwoWidgetScroll(this, photo.get(), text.get());

    new FutureBytes(this, url, [this] (const auto& ba) { photo.setBytes(ba); });
    new FutureText(this, product, [this] (const auto& s) { text.setText(s); });
}
