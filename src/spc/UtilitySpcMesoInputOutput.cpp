// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/UtilitySpcMesoInputOutput.h"
#include "common/GlobalVariables.h"
#include "util/UtilityIO.h"
#include "util/UtilityString.h"

QStringList UtilitySpcMesoInputOutput::getAnimation(const QString& product, const QString& sector, int frameCount) {
    QStringList urls;
    auto html = UtilityIO::getHtml(GlobalVariables::nwsSPCwebsitePrefix + "/exper/mesoanalysis/new/archiveviewer.php?sector=19&parm=pmsl");
    html = html.replace("\n", " ");
    auto timeList = UtilityString::parseColumn(html, "dattim\\[[0-9]{1,2}\\].*?=.*?([0-9]{8})");
    if (timeList.size() > frameCount) {
        for (auto index = frameCount - 1; index >= 0; index -= 1) {
            auto imgUrl = GlobalVariables::nwsSPCwebsitePrefix + "/exper/mesoanalysis/s" + sector + "/" + product + "/" + product + "_" + timeList[index] + ".gif";
            urls.push_back(imgUrl);
        }
    }
    return urls;
}
