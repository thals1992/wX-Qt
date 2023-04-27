// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/AlertsDetail.h"
#include "objects/FutureVoid.h"

AlertsDetail::AlertsDetail(QWidget * parent, const string& url)
    : Window{ parent }
    , sw{ ScrolledWindow{this, box} }
    , text{ Text{this} }
    , url{ url }
{
    box.addMargins();
    box.addWidget(text);
    box.setAlignment(text, Qt::AlignTop);
    new FutureVoid{this, [this, url] { capAlert = CapAlert{url}; }, [this] { update(); }};
}

void AlertsDetail::update() {
    text.setText(capAlert.text);
    setTitle(capAlert.title);
}
