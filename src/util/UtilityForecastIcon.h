// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYFORECASTICON_H
#define UTILITYFORECASTICON_H

#include <string>
#include <QImage>

using std::string;

class UtilityForecastIcon {
public:
    static QImage getIcon(const string&);

private:
    static QImage parseBitmapString(const string&);
    static QImage getBitmapWithOneNumber(const string&);
    static QImage getDualBitmapWithNumbers(const string&, const string&);
    static string getFilename(const string&);
};

#endif  // UTILITYFORECASTICON_H
