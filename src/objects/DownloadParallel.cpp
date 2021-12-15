// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/DownloadParallel.h"
#include <algorithm>
#include "objects/FutureVoid.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"

DownloadParallel::DownloadParallel(QWidget * parent, FileStorage * fileStorage, QStringList urls) {
    this->fileStorage = fileStorage;
    this->urls = urls;
    fileStorage->clearBuffers();
    for ([[maybe_unused]] const auto& u : urls) {
        fileStorage->animationMemoryBuffer.push_back(MemoryBuffer(0));
        // fileStorage.animationByteArray.add(array("B"));
        downloadComplete.push_back(false);
    }
    for (auto i : UtilityList::range(urls.size())) {
        new FutureVoid(parent, [this, i] { download(i); }, [this, i] { update(i); });
    }
    while (!std::all_of(downloadComplete.begin(), downloadComplete.end(), [] (bool b) { return b; })) {
        // time.sleep(0.001);
    }
}

void DownloadParallel::download(int i) {
    fileStorage->setMemoryBufferForAnimation(i, UtilityIO::downloadAsByteArray(urls[i]));
    downloadComplete[i] = true;
}

void DownloadParallel::update(int i) {
    downloadComplete[i] = true;
}
