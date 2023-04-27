// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/Observations.h"
#include "misc/UtilityObservations.h"
#include "objects/FutureBytes.h"
#include "ui/PhotoSizeEnum.h"
#include "util/Utility.h"

Observations::Observations(QWidget * parent)
    : Window{parent}
    , photo{ Photo{this, Full} }
    , comboBox{ ComboBox{this, UtilityObservations::labels} }
{
    setTitle("Observations");
    comboBox.setIndexByPref(prefToken, 0);
    comboBox.connect([this] { reload(); });
    box.addWidget(comboBox);
    box.addWidgetAndCenter(photo);
    box.getAndShow(this);
    reload();
}

void Observations::reload() {
    const auto& url = UtilityObservations::urls[comboBox.getIndex()];
    Utility::writePrefInt(prefToken, comboBox.getIndex());
    new FutureBytes{this, url, [this] (const auto& ba) { photo.setBytes(ba); }};
}
