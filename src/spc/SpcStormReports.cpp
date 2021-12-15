// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/SpcStormReports.h"
#include <QSet>
#include "common/GlobalVariables.h"
#include "objects/FutureBytes.h"
#include "objects/FutureText.h"
#include "spc/LsrByWfo.h"
#include "spc/UtilitySpcStormReports.h"
#include "ui/ObjectCardBlackHeaderText.h"
#include "ui/ObjectDividerLine.h"
#include "ui/PhotoSizeEnum.h"
#include "util/To.h"

SpcStormReports::SpcStormReports(QWidget * parent, const QString& spcStormReportsDay) : Window(parent) {
    this->spcStormReportsDay = spcStormReportsDay;
    setTitle("SPC Storm Reports");
    setSize(1000, 900);
    url = GlobalVariables::nwsSPCwebsitePrefix + "/climo/reports/" + spcStormReportsDay + ".gif";
    stormReportsUrl = GlobalVariables::nwsSPCwebsitePrefix + "/climo/reports/" + spcStormReportsDay + ".csv";
    states.clear();
    stormReports.clear();
    cardWidgets.clear();

    box = VBox(this);

    stateMenu = ComboBox(this);
    boxImage = HBox(this);
    calendar = Calendar(this);
    calendar.connect([this] { onDateChanged(); });
    lsrWfoButton = Button(this, "LSR by WFO");
    lsrWfoButton.connect([this] { new LsrByWfo(this); });

    boxText = VBox(this);
    photo = Photo(this, PhotoSizeEnum::normal);
    boxImage.addWidget(photo.get());
    boxImage.addWidget(calendar.get());
    box.addWidget(lsrWfoButton.get());
    box.addWidget(stateMenu.get());
    box.addLayout(boxImage.get());
    box.addLayout(boxText.get());

    sw = ScrolledWindow(this, box.get());
    reload();
}

void SpcStormReports::onDateChanged() {
    auto dayStr = To::String(calendar.getDay()).rightJustified(2, '0');
    auto monthStr = To::String(calendar.getMonth()).rightJustified(2, '0');
    auto yearStr = To::String(calendar.getYear()).mid(2);
    auto dateStr = yearStr + monthStr + dayStr;
    spcStormReportsDay = dateStr;
    url = GlobalVariables::nwsSPCwebsitePrefix + "/climo/reports/" + spcStormReportsDay + "_rpts.gif";
    stormReportsUrl = GlobalVariables::nwsSPCwebsitePrefix + "/climo/reports/" + spcStormReportsDay + ".csv";
    states.clear();
    stormReports.clear();
    reload();
}

void SpcStormReports::updateReports(const QString& html) {
    stormReports = UtilitySpcStormReports::process(html.split(GlobalVariables::newline));
    QStringList rawStates;
    for (const auto& stormReport : stormReports) {
        if (stormReport.damageHeader == "" && stormReport.state != "") {
            rawStates.push_back(stormReport.state);
        }
    }
    // QStringList uniqStates = rawStates.toSet().toList();
    //#if QT_VERSION >= 0x051400 //0x060000
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
        QStringList uniqStates = QSet<QString>(rawStates.begin(), rawStates.end()).values();
    #else
        QStringList uniqStates = rawStates.toSet().toList();
    #endif
    uniqStates.sort();
    QStringList uniqStatesWithCount;
    for (const auto& item : uniqStates) {
        uniqStatesWithCount.push_back(item + ": " + To::String(static_cast<int>(rawStates.count(item))));
    }
    stateMenu.removeAll();
    states.push_back("All");
    states += uniqStatesWithCount;
    stateMenu.addItems(states);
    stateMenu.block(0);
    stateMenu.connect([this] { filterReports(); });
    stateMenu.setIndex(0);
    filterReports();
    stateMenu.unblock(0);
}

void SpcStormReports::filterReports() {
    auto index = stateMenu.getIndex();
    if (index >= states.size() || index == -1) {
        return;
    }
    const auto filter = states[index].split(":")[0];
    boxText.removeChildren();
    cardWidgets.clear();
    for (const auto& stormReport : stormReports) {
        if (stormReport.damageHeader == "" && filter == "All") {
            boxText.addLayout(ObjectCardStormReportItem(this, stormReport).get());
            boxText.addWidget(ObjectDividerLine(this).get());
        } else if (stormReport.damageHeader == "" && stormReport.state == filter) {
            boxText.addLayout(ObjectCardStormReportItem(this, stormReport).get());
            boxText.addWidget(ObjectDividerLine(this).get());
        } else if (stormReport.damageHeader != "") {
            boxText.addLayout(ObjectCardBlackHeaderText(this, stormReport.damageHeader).get());
            boxText.addWidget(ObjectDividerLine(this).get());
        }
    }
    boxText.addStretch();
}

void SpcStormReports::reload() {
    new FutureBytes(this, url, [this] (const auto& ba) { photo.setNoScale(ba); });
    new FutureText(this, stormReportsUrl, [this] (const auto& s) { updateReports(s); });
}
