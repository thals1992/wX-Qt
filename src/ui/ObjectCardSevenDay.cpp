// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ObjectCardSevenDay.h"

ObjectCardSevenDay::ObjectCardSevenDay() {
}

ObjectCardSevenDay::ObjectCardSevenDay(QWidget * parent, VBox& box, const QStringList& forecasts, const QStringList& icons) {
    auto iconIndex = 0;
    for (const auto& forecast : forecasts) {
        if (forecast.contains(":")) {
            auto items = forecast.split(":");
            auto day = items[0];
            auto longForecast = items[1];
            auto widget = SevenDayCard(parent, day, longForecast.trimmed(), icons[iconIndex]);
            cards.push_back(widget);
            box.addLayout(widget.get());
        }
        iconIndex += 1;
    }
    box.addStretch();
}

void ObjectCardSevenDay::update(const QStringList& forecasts, const QStringList& icons) {
    auto index = 0;
    for (const auto& forecast : forecasts) {
        auto items = forecast.split(":");
        if (items.size() > 1) {
            auto day = items[0];
            auto longForecast = items[1];
            if (cards.size() > index) {
                cards[index].update(day, longForecast.trimmed(), icons[index]);
            }
        }
        index += 1;
    }
}
