// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/DownloadParallelBytes.h"
#include <algorithm>
#include "objects/FutureVoid.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"

DownloadParallelBytes::DownloadParallelBytes(QWidget * parent, QStringList urls) {
    this->urls = urls;
    for ([[maybe_unused]] const auto& u : urls) {
        byteList.push_back(QByteArray());
        downloadComplete.push_back(false);
    }
    for (auto i : UtilityList::range(urls.size())) {
        new FutureVoid(parent, [this, i] { download(i); }, [this, i] { update(i); });
    }
    while (!std::all_of(downloadComplete.begin(), downloadComplete.end(), [] (bool b) { return b; })) {
        // time.sleep(0.001);
    }
}

void DownloadParallelBytes::download(int i) {
    byteList[i] = UtilityIO::downloadAsByteArray(urls[i]);
    downloadComplete[i] = true;
}

void DownloadParallelBytes::update(int i) {
    downloadComplete[i] = true;
}
