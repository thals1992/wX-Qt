// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef DOWNLOADPARALLEL_H
#define DOWNLOADPARALLEL_H

#include <string>
#include <vector>
#include <QWidget>
#include "objects/FileStorage.h"

using std::string;
using std::vector;

class DownloadParallel {
public:
    DownloadParallel(QWidget * parent, FileStorage * fileStorage, const vector<string>& urls);

private:
    void download(int);
    void update(int);
    FileStorage * fileStorage;
    vector<string> urls;
    vector<bool> downloadComplete;
};

#endif  // DOWNLOADPARALLEL_H
