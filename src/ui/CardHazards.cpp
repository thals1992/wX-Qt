// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/CardHazards.h"
#include "misc/AlertsDetail.h"
#include "util/UtilityString.h"
#include "util/UtilityUI.h"

CardHazards::CardHazards() = default;

CardHazards::CardHazards(QWidget * parent, const Hazards& objectHazards)
    : VBox{}
    , data{ objectHazards.data }
{
    const auto ids = UtilityString::parseColumn(data, "\"id\": \"(http.*?)\"");
    const auto hazards = UtilityString::parseColumn(data, "\"event\": \"(.*?)\"");
    auto index = 0;
    for (const auto& hazard : hazards) {
        labels.emplace_back(parent, None, "&" + hazard);
        const auto url = ids[index];
        labels.back().connect([url, parent] { new AlertsDetail{parent, url}; });
        vbox.addWidget(labels.back());
        index += 1;
    }
    addLayout(vbox);
}

void CardHazards::removeLabels() {
    vbox.removeChildren();
}
