// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ObjectCardHazards.h"
#include "misc/AlertsDetail.h"
#include "util/UtilityString.h"
#include "util/UtilityUI.h"

ObjectCardHazards::ObjectCardHazards() = default;

ObjectCardHazards::ObjectCardHazards(QWidget * parent, const ObjectHazards& objectHazards)
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
        vbox.addWidget(labels.back().get());
        index += 1;
    }
    addLayout(vbox.get());
}

void ObjectCardHazards::removeLabels() {
    vbox.removeChildren();
}
