// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/UsAlerts.h"
#include <QSet>
#include "objects/FutureBytes.h"
#include "objects/FutureVoid.h"
#include "ui/ObjectCardAlertDetail.h"
#include "util/To.h"
#include "util/UtilityDownloadNws.h"
#include "util/UtilityString.h"

UsAlerts::UsAlerts(QWidget * parent): Window(parent) {
    setTitle("US Alerts");
    maximize();
    comboBox = ComboBox(this);
    box = VBox(this);
    boxCombo = VBox(this);
    boxText = VBox(this);
    photo = Photo(this, PhotoSizeEnum::normal);
    boxCombo.addWidget(comboBox.get());
    box.addLayout(boxCombo.get());
    box.addWidgetAndCenter(photo.get());
    box.addLayout(boxText.get());
    sw = ScrolledWindow(this, box);
    new FutureBytes(this, "https://forecast.weather.gov/wwamap/png/US.png", [this] (const auto& ba) { photo.setBytes(ba); });
    new FutureVoid(this, [this] { downloadCap(); }, [this] { updateText(); });
}

void UsAlerts::downloadCap() {
    html = UtilityDownloadNws::getCap("us");
}

void UsAlerts::updateText() {
    auto alerts = UtilityString::parseColumn(html, "<entry>(.*?)</entry>");
    QStringList rawEvents;
    for (const auto& alert : alerts) {
        capAlerts.push_back(CapAlertXml(alert));
    }
    QStringList filter;
    filter += defaultFilter;
    for (const auto& item : filter) {
        filterCount[item] = 0;
    }
    for (const auto& cap : capAlerts) {
        rawEvents.push_back(cap.event);
        if (filterCount.contains(cap.event)) {
            filterCount[cap.event] = filterCount[cap.event] + 1;
        } else {
            filterCount[cap.event] = 1;
        }
        if (filter.contains(cap.event)) {
            boxText.addLayout(ObjectCardAlertDetail(this, cap).get());
        }
    }
    boxText.addStretch();
    QSet<QString> uniqEventsSet;
    for (const auto& item : rawEvents) {
        uniqEventsSet.insert(item);
    }
    QStringList uniqEvents;
    for (const auto& item : uniqEventsSet) {
        uniqEvents.push_back(item);
    }
    uniqEvents.sort();
    QStringList uniqEventssWithCount;
    for (const auto& item : uniqEvents) {
        uniqEventssWithCount.push_back(item + ": " + To::String(count(item, rawEvents)));
    }
    comboBox.appendText("Tor/Ffw/Tst");
    eventList.push_back("Tor/Ffw/Tst");
    for (const auto& value : uniqEventssWithCount) {
        comboBox.appendText(value);
        eventList.push_back(value);
    }
    comboBox.setIndex(0);
    comboBox.connect([this] { filterEvents(); });
}

void UsAlerts::filterEvents() {
    auto index = comboBox.getIndex();
    boxText.removeChildren();
    auto filter = eventList[index].split(":")[0];
    if (index == 0) {
        filter = ":" + defaultFilter.join(":");
        for (const auto& cap : capAlerts) {
            if (filter.contains(":" + cap.event + ":")) {
                boxText.addLayout(ObjectCardAlertDetail(this, cap).get());
            }
        }
        QString text = "";
        for (const auto& item : filter.split(":")) {
            if (item != ":" && item != "") {
                text += item + ": " + To::String(filterCount[item]) + "  ";
            }
        }
    } else {
        for (const auto& cap : capAlerts) {
            if (cap.event == filter) {
                boxText.addLayout(ObjectCardAlertDetail(this, cap).get());
            }
        }
    }
    boxText.addStretch();
}

int UsAlerts::count(const QString& token, const QStringList& itemList) {
    auto total = 0;
    for (const auto& item : itemList) {
        if (token == item) {
            total += 1;
        }
    }
    return total;
}
