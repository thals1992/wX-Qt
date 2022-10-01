// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/DownloadParallelBytes.h"
#include <algorithm>
#include "objects/FutureVoid.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"

DownloadParallelBytes::DownloadParallelBytes(QWidget * parent, const vector<string>& urls)
    : urls{ urls }
{
    for ([[maybe_unused]] const auto& u : urls) {
        byteList.emplace_back();
        downloadComplete.push_back(false);
    }
    for (auto i : range(urls.size())) {
        new FutureVoid{parent, [this, i] { download(i); }, [] { ; }};
    }
    while (!std::all_of(downloadComplete.begin(), downloadComplete.end(), [] (bool b) { return b; })) {
        // time.sleep(0.001);
    }
}

void DownloadParallelBytes::download(int i) {
    byteList[i] = UtilityIO::downloadAsByteArray(urls[i]);
    downloadComplete[i] = true;
}
