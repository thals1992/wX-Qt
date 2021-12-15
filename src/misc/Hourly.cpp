// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/Hourly.h"
#include "objects/FutureText.h"
#include "settings/Location.h"

Hourly::Hourly(QWidget * parent) : Window(parent) {
    setSize(500, 900);
    setTitle("Hourly forecast for " + Location::locationName());
    text = Text(this);
    text.setFixedWidth();
    box.addWidget(text.get());
    box.addMargins();
    sw = ScrolledWindow(this, box);
    new FutureText(this, "HOURLY", [this] (const auto& s) { text.setText(s); });
}
