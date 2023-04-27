// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WXGLDOWNLOAD_H
#define WXGLDOWNLOAD_H

#include <string>
#include <vector>
#include <QWidget>
#include "objects/FileStorage.h"

using std::string;
using std::vector;

class NexradDownload {
public:
    static string getRidPrefix(const string&, bool);
    static string getRadarDirectoryUrl(const string&, const string&, const string&);
    static string getRadarFileUrl(const string&, const string&, bool);
    static void getRadarFilesForAnimation(QWidget *, int, const string&, const string&, FileStorage *);

private:
    static const string pattern1;
    static const string pattern2;
    static const string nwsRadarPub;
    static const vector<string> pacRids;
};

#endif  // WXGLDOWNLOAD_H
