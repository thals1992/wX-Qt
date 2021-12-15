// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYSTRING_H
#define UTILITYSTRING_H

#include <QStringList>

class UtilityString {
public:
    static bool match(const QString&, const QString&);
    static QString parse(const QString&, const QString&);
    static QString parseMultiLineLastMatch(const QString&, const QString&);
    static QStringList parseTwo(const QString&, const QString&);
    static QStringList parseColumn(const QString&, const QString&);
    static QVector<QString> parseColumn(const QString&, const QString&, bool);
    static QString extractPreLsr(const QString&);
    static QString getLastXChars(const QString&, int);
    static QString removeHtml(const QString&);
    static QString insert(const QString&, int, const QString&);
    static QString truncate(const QString&, int);
    static QString substring(const QString&, int, int);
    static int parseAndCount(const QString&, const QString&);
    static QString replaceRegexp(const QString&, const QString&, const QString&);
    static QString addPeriodBeforeLastTwoChars(const QString&);
    static QString toCamelCase(const QString&);
    static QStringList parseXml(const QString& payloadF, const QString& delimF);
    static QStringList parseXmlExt(QStringList regexpList, const QString& html);
    static QStringList parseXmlValue(const QString&);
    static QString replaceRegex(const QString&, const QString&, const QString&);
};

#endif  // UTILITYSTRING_H
