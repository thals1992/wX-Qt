// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/Hourly.h"
#include <string>
#include "objects/FutureText.h"
#include "settings/Location.h"

using std::string;

Hourly::Hourly(QWidget * parent)
    : Window{parent}
    , sw{ ScrolledWindow{this, box} }
    , text{ Text{this} }
{
    setSize(500, 900);
    setTitle("Hourly forecast for " + Location::locationName());
    text.setFixedWidth();
    box.addWidget(text);
    box.addMargins();
    new FutureText{this, "HOURLY", [this] (const auto& s) { text.setText(s); }};
}
