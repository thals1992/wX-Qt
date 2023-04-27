// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/SpcStormReports.h"
#include <algorithm>
#include <set>
#include "common/GlobalVariables.h"
#include "objects/FutureBytes.h"
#include "objects/FutureText.h"
#include "objects/WString.h"
#include "spc/LsrByWfo.h"
#include "spc/UtilitySpcStormReports.h"
#include "ui/CardBlackHeaderText.h"
#include "ui/DividerLine.h"
#include "ui/PhotoSizeEnum.h"
#include "util/To.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"

SpcStormReports::SpcStormReports(QWidget * parent, const string& spcStormReportsDay)
    : Window{parent}
    , sw{ ScrolledWindow{this, box} }
    , calendar{ Calendar{this} }
    , photo{ Photo{this, Scaled} }
    , comboBox{ ComboBox{this} }
    , lsrWfoButton{ Button{this, None, "LSR by WFO"} }
    , spcStormReportsDay{ spcStormReportsDay }
    , url{ GlobalVariables::nwsSPCwebsitePrefix + "/climo/reports/" + spcStormReportsDay + ".gif" }
    , stormReportsUrl{ GlobalVariables::nwsSPCwebsitePrefix + "/climo/reports/" + spcStormReportsDay + ".csv" }
{
    setTitle("SPC Storm Reports");
    states.clear();
    stormReports.clear();
    cardWidgets.clear();

    calendar.connect([this] { onDateChanged(); });
    lsrWfoButton.connect([this] { new LsrByWfo{this}; });

    boxImage.addWidget(photo);
    boxImage.addWidget(calendar);
    box.addWidget(lsrWfoButton);
    box.addWidget(comboBox);
    box.addLayout(boxImage);
    box.addLayout(boxText);

    reload();
}

void SpcStormReports::onDateChanged() {
    const auto dayStr = WString::fixedLengthStringPad0(To::string(calendar.getDayOfMonth()), 2);
    const auto monthStr = WString::fixedLengthStringPad0(To::string(calendar.getMonth()), 2);
    const auto yearStr = UtilityString::substring(To::string(calendar.getYear()), 2, 4);
    const auto dateStr = yearStr + monthStr + dayStr;
    spcStormReportsDay = dateStr;
    url = GlobalVariables::nwsSPCwebsitePrefix + "/climo/reports/" + spcStormReportsDay + "_rpts.gif";
    stormReportsUrl = GlobalVariables::nwsSPCwebsitePrefix + "/climo/reports/" + spcStormReportsDay + "_rpts.csv";
    states.clear();
    stormReports.clear();
    reload();
}

void SpcStormReports::updateReports(const string& html) {
    stormReports = UtilitySpcStormReports::process(WString::split(html, GlobalVariables::newline));
    vector<string> rawStates;
    for (const auto& stormReport : stormReports) {
        if (stormReport.damageHeader.empty() && !stormReport.state.empty()) {
            rawStates.push_back(stormReport.state);
        }
    }
    std::set<string> tmpSet{rawStates.begin(), rawStates.end()};
    vector<string> uniqStates{tmpSet.begin(), tmpSet.end()};
    sort(uniqStates.begin(), uniqStates.end());
    vector<string> uniqStatesWithCount;
    for (const auto& item : uniqStates) {
        uniqStatesWithCount.push_back(item + ": " + To::string(UtilityList::count(rawStates, item)));
    }
    states.emplace_back("All");
    addAll(states, uniqStatesWithCount);
    comboBox.setList(states);
    comboBox.connect([this] { filterReports(); });
    comboBox.setIndex(0);
    filterReports();
}

void SpcStormReports::filterReports() {
    const size_t index = comboBox.getIndex();
    if (index >= states.size()) {
        return;
    }
    const auto filter = WString::split(states[index], ":")[0];
    boxText.removeChildren();
    cardWidgets.clear();
    for (const auto& stormReport : stormReports) {
        if (stormReport.damageHeader.empty() && filter == "All") {
            boxText.addLayout(CardStormReportItem(this, stormReport).getView());
            boxText.addWidget(DividerLine(this).get());
        } else if (stormReport.damageHeader.empty() && stormReport.state == filter) {
            boxText.addLayout(CardStormReportItem(this, stormReport).getView());
            boxText.addWidget(DividerLine(this).get());
        } else if (!stormReport.damageHeader.empty()) {
            boxText.addLayout(CardBlackHeaderText(this, stormReport.damageHeader).getView());
            boxText.addWidget(DividerLine(this).get());
        }
    }
    boxText.addStretch();
}

void SpcStormReports::reload() {
    new FutureBytes{this, url, [this] (const auto& ba) { photo.setNoScale(ba); }};
    new FutureText{this, stormReportsUrl, [this] (const auto& s) { updateReports(s); }};
}
