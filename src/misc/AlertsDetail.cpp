// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/AlertsDetail.h"
#include "objects/FutureVoid.h"

AlertsDetail::AlertsDetail(QWidget * parent, const QString& url) : Window(parent) {
    this->url = url;
    setSize(700, 900);
    box = VBox(this);
    box.addMargins();
    text = Text(this, "");
    box.addWidget(text.get());
    box.setAlignment(text.get(), Qt::AlignTop);
    sw = ScrolledWindow(this, box);
    new FutureVoid(this, [&] { download(); }, [&] { updateText(); });
}

void AlertsDetail::download() {
    capAlert = CapAlert(url);
}

void AlertsDetail::updateText() {
    text.setText(capAlert.text);
    setTitle(capAlert.title);
}
