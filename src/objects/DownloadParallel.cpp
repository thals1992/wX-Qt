// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/DownloadParallel.h"
#include <algorithm>
#include "objects/FutureVoid.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"

DownloadParallel::DownloadParallel([[maybe_unused]] QWidget * parent, FileStorage * fileStorage, const vector<string>& urls)
    : fileStorage{ fileStorage }
    , urls{ urls }
{
    fileStorage->clearBuffers();
    for ([[maybe_unused]] const auto& u : urls) {
        fileStorage->animationMemoryBuffer.emplace_back(0);
        downloadComplete.push_back(false);
    }
    for (auto i : range(urls.size())) {
        // new FutureVoid{parent, [this, i] { download(i); }, [this, i] { update(i); }};
        // TODO FIXME this (line above and while loop below) worked fine on MacOS but not on chromebook
        download(i);
    }
    // while (!std::all_of(downloadComplete.begin(), downloadComplete.end(), [] (bool b) { return b; })) {
    //     // time.sleep(0.001);
    // }
}

void DownloadParallel::download(int i) {
    fileStorage->setMemoryBufferForAnimation(i, UtilityIO::downloadAsByteArray(urls[i]));
    downloadComplete[i] = true;
}

void DownloadParallel::update(int i) {
    downloadComplete[i] = true;
}
