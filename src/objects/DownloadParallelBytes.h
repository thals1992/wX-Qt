// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef DOWNLOADPARALLELBYTES_H
#define DOWNLOADPARALLELBYTES_H

#include <functional>
#include <string>
#include <vector>
#include <QWidget>

using std::function;
using std::string;
using std::vector;

class DownloadParallelBytes {
public:
    DownloadParallelBytes(QWidget *, const vector<string>&);
    vector<QByteArray> byteList;

private:
    void download(int);
    vector<string> urls;
    vector<bool> downloadComplete;
};

#endif  // DOWNLOADPARALLELBYTES_H
