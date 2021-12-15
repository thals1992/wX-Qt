// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/LsrByWfo.h"
#include "common/GlobalArrays.h"
#include "objects/FutureVoid.h"
#include "settings/Location.h"
#include "ui/ObjectDividerLine.h"
#include "util/To.h"
#include "util/UtilityDownload.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"

LsrByWfo::LsrByWfo(QWidget * parent) : Window(parent) {
    setTitle("Local Storm Reports");
    maximize();
    wfo = Location::office();

    box = VBox(this);
    boxText = VBox(this);

    comboboxSector = ComboBox(this, GlobalArrays::wfos);
    comboboxSector.setIndexByValue(wfo);
    comboboxSector.connect([this] { changeSector(); });

    box.addWidget(comboboxSector.get());
    box.addLayout(boxText.get());

    sw = ScrolledWindow(this, box);
    reload();
}

void LsrByWfo::changeSector() {
    wfo = comboboxSector.getValue().split(":")[0];
    reload();
}

void LsrByWfo::getLsrFromWfo() {
    lsrList.clear();
    textList.clear();
    boxText.removeChildren();
    auto url = ("https://forecast.weather.gov/product.php?site=" + wfo + "&issuedby=" + wfo + "&product=LSR&format=txt&version=1&glossary=0");
    auto html = UtilityIO::getHtml(url);
    auto numberLSR = UtilityString::parseMultiLineLastMatch(html, "product=LSR&format=TXT&version=(.*?)&glossary");
    if (numberLSR == "") {
        lsrList.push_back("None issued by this office recently.");
    } else {
        int maxVers = To::Int(numberLSR);
        if (maxVers > 30) {
            maxVers = 30;
        }
        auto i = 0;
        for (auto version : UtilityList::range3(1, maxVers, 2)) {
            lsrList.push_back("");
            textList.push_back(Text(this, ""));
            boxText.addWidget(textList[i].get());
            boxText.addWidget(ObjectDividerLine(this).get());
            new FutureVoid(this, [i, version, this] { download(i, version); }, [i, this] { update(i); });
            i += 1;
        }
    }
}

void LsrByWfo::download(int i, int version) {
    lsrList[i] = UtilityDownload::getTextProductWithVersion("LSR" + wfo, version);
}

void LsrByWfo::update(int i) {
    textList[i].setText(lsrList[i]);
}

void LsrByWfo::reload() {
    new FutureVoid(this, [] {}, [this] { getLsrFromWfo(); });
}
