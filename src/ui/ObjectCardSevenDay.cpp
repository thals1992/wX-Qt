// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ObjectCardSevenDay.h"
#include "objects/WString.h"

ObjectCardSevenDay::ObjectCardSevenDay() = default;

ObjectCardSevenDay::ObjectCardSevenDay(QWidget * parent, VBox& box, const vector<string>& forecasts, const vector<string>& icons) {
    auto iconIndex = 0;
    for (const auto& forecast : forecasts) {
        if (WString::contains(forecast, ":")) {
            const auto items = WString::split(forecast, ":");
            const auto day = items[0];
            const auto longForecast = items[1];
            sevenDayCard.emplace_back(parent, day, WString::strip(longForecast), icons[iconIndex]);
            box.addLayout(sevenDayCard.back().get());
        }
        iconIndex += 1;
    }
    box.addStretch();
}

void ObjectCardSevenDay::update(const vector<string>& forecasts, const vector<string>& icons) {
    size_t index = 0;
    for (const auto& forecast : forecasts) {
        const auto items = WString::split(forecast, ":");
        if (items.size() > 1) {
            const auto day = items[0];
            const auto longForecast = items[1];
            if (sevenDayCard.size() > index) {
                sevenDayCard[index].update(day, WString::strip(longForecast), icons[index]);
            }
        }
        index += 1;
    }
}
