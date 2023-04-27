// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/SevenDayCollection.h"
#include "objects/WString.h"

SevenDayCollection::SevenDayCollection()  = default;

SevenDayCollection::SevenDayCollection(QWidget * parent, VBox& box, SevenDay * sevenDay) {
    this->sevenDay = sevenDay;
    auto iconIndex = 0;
    for (const auto& forecast : sevenDay->detailedForecasts) {
        if (WString::contains(forecast, ":")) {
            const auto items = WString::split(forecast, ":");
            const auto day = items[0];
            const auto longForecast = items[1];
            sevenDayCard.emplace_back(parent, day, WString::strip(longForecast), sevenDay->icons[iconIndex]);
            box.addLayout(sevenDayCard.back());
        }
        iconIndex += 1;
    }
    box.addStretch();
}

void SevenDayCollection::update() {
    size_t index = 0;
    for (const auto& forecast : sevenDay->detailedForecasts) {
        const auto items = WString::split(forecast, ":");
        if (items.size() > 1) {
            const auto day = items[0];
            const auto longForecast = items[1];
            if (sevenDayCard.size() > index) {
                sevenDayCard[index].update(day, WString::strip(longForecast), sevenDay->icons[index]);
            }
        }
        index += 1;
    }
}
