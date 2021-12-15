// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ObjectCardHazards.h"
#include <QStringList>
#include "misc/AlertsDetail.h"
#include "util/UtilityString.h"
#include "util/UtilityUI.h"

ObjectCardHazards::ObjectCardHazards() {
}

ObjectCardHazards::ObjectCardHazards(QWidget * parent, const ObjectHazards& objectHazards) : VBox(parent) {
    this->parent = parent;
    data = objectHazards.data;
    auto ids = UtilityString::parseColumn(data, "\"id\": \"(http.*?)\"");
    auto hazards = UtilityString::parseColumn(data, "\"event\": \"(.*?)\"");
    vbox = VBox(parent);
    auto index = 0;
    labels.clear();
    for (const auto& hazard : hazards) {
        labels.push_back(new Button(parent, "&" + hazard));
        const auto url = ids[index];
        labels.back()->connect([this, url] { launchAlert(url); });
        vbox.addWidget(labels.back()->get());
        index += 1;
    }
    addLayout(vbox.get());
}

void ObjectCardHazards::removeLabels() {
    UtilityUI::removeChildren(vbox.get());
}

void ObjectCardHazards::launchAlert(const QString& url) {
    auto window = new AlertsDetail(parent, url);
    window->show();
}
