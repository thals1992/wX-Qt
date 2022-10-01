// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYSTRING_H
#define UTILITYSTRING_H

#include <string>
#include <vector>
#include <QString>

using std::string;
using std::vector;

class UtilityString {
public:
    static string parse(const string&, const string&);
    static string parseMultiLineLastMatch(const string&, const string&);
    static vector<string> parseTwo(const string&, const string&);
    static vector<string> parseColumn(const string&, const string&);
    static string extractPreLsr(const string&);
    static string getLastXChars(const string&, int);
    static string removeHtml(const string&);
    static string insert(const string&, int, const string&);
    static string truncate(const string&, int);
    static string substring(const string&, int, int = -1);
    static string addPeriodBeforeLastTwoChars(const string&);
    static string toCamelCase(const string&);
    static vector<string> parseXml(const string& payloadF, const string& delim);
    static vector<string> parseXmlExt(const vector<string>& regexpList, const string& html);
    static vector<string> parseXmlValue(const string& payloadF);
    static bool match(const string&, const string&);
    static string replaceRegex1(const string&, const string&, const string&);
    static string replaceRegex(const string&, const string&, const string&);
    static string parseNwsPre(const string&);

private:
    static QString parse(const QString&, const QString&);
};

#endif  // UTILITYSTRING_H
