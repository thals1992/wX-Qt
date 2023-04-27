// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/LsrByWfo.h"
#include "common/GlobalArrays.h"
#include "objects/FutureVoid.h"
#include "objects/WString.h"
#include "settings/Location.h"
#include "ui/DividerLine.h"
#include "util/To.h"
#include "util/DownloadText.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"

LsrByWfo::LsrByWfo(QWidget * parent)
    : Window{parent}
    , sw{ ScrolledWindow{this, box} }
    , comboboxSector{ ComboBox{this, GlobalArrays::wfos} }
    , wfo{ Location::office() }
{
    setTitle("Local Storm Reports");
    comboboxSector.setIndexByValue(wfo);
    comboboxSector.connect([this] { changeSector(); });
    box.addWidget(comboboxSector);
    box.addLayout(boxText);
    reload();
}

void LsrByWfo::changeSector() {
    wfo = WString::split(comboboxSector.getValue(), ":")[0];
    reload();
}

void LsrByWfo::getLsrFromWfo() {
    lsrList.clear();
    textList.clear();
    boxText.removeChildren();
    const auto url = ("https://forecast.weather.gov/product.php?site=" + wfo + "&issuedby=" + wfo + "&product=LSR&format=txt&version=1&glossary=0");
    const auto html = UtilityIO::getHtml(url);
    const auto numberLSR = UtilityString::parseMultiLineLastMatch(html, "product=LSR&format=TXT&version=(.*?)&glossary");
    if (numberLSR.empty()) {
        lsrList.emplace_back("None issued by this office recently.");
    } else {
        auto maxVersions = To::Int(numberLSR);
        if (maxVersions > 30) {
            maxVersions = 30;
        }
        auto i = 0;
        for (auto version : range3(1, maxVersions, 2)) {
            lsrList.emplace_back("");
            textList.emplace_back(this);
            boxText.addWidget(textList[i]);
            boxText.addWidget(DividerLine(this).get());
            new FutureVoid{this, [i, version, this] { download(i, version); }, [i, this] { update(i); }};
            i += 1;
        }
    }
}

void LsrByWfo::download(int i, int version) {
    lsrList[i] = DownloadText::getTextProductWithVersion("LSR" + wfo, version);
}

void LsrByWfo::update(int i) {
    textList[i].setText(lsrList[i]);
}

void LsrByWfo::reload() {
    new FutureVoid{this, [] {}, [this] { getLsrFromWfo(); }};
}
