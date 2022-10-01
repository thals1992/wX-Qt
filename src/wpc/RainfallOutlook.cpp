// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "wpc/RainfallOutlook.h"
#include "objects/FutureBytes.h"
#include "objects/FutureText.h"
#include "util/To.h"
#include "wpc/UtilityWpcRainfallOutlook.h"

RainfallOutlook::RainfallOutlook(QWidget * parent, int day)
    : Window{parent}
    , photo{ Photo{this, Scaled} }
    , text{ Text{this} }
    , sw{ ObjectTwoWidgetScroll{this, photo.get(), text.get()} }
{
    setTitle("Excessive Rainfall Outlook Day " + To::string(day + 1));
    const auto& url = UtilityWpcRainfallOutlook::urls[day];
    const auto& product = UtilityWpcRainfallOutlook::codes[day];
    new FutureBytes{this, url, [this] (const auto& ba) { photo.setBytes(ba); }};
    new FutureText{this, product, [this] (const auto& s) { text.setText(s); }};
}
