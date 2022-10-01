// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef FILE_H
#define FILE_H

#include <vector>
#include <QByteArray>
#include <QString>

using std::string;
using std::vector;

class File {
public:
    explicit File(const string&);
    QString getText();
    QByteArray getBinaryDataFromResource();
//    vector<unsigned char> getBinaryDataFromResource();
    // void setText(const QString&);

private:
    string fileName;
};

#endif  // FILE_H
