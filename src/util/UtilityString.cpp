// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/UtilityString.h"
#include <QtGlobal>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QVector>
#include "common/GlobalVariables.h"

bool UtilityString::match(const QString& data, const QString& regexp) {
    auto re = QRegularExpression(regexp, QRegularExpression::MultilineOption | QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatch match = re.match(data);
    if (match.hasMatch()) {
        return true;
    }
    return false;
}

QStringList UtilityString::parseTwo(const QString& data, const QString& regexp) {
    auto re = QRegularExpression(regexp, QRegularExpression::MultilineOption | QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatch match = re.match(data);
    if (match.hasMatch()) {
        QString matched1 = match.captured(1);
        QString matched2 = match.captured(2);
        return {matched1, matched2};
    } else {
        return {"", ""};
    }
}

QString UtilityString::parse(const QString& data, const QString& regexp) {
    auto re = QRegularExpression(regexp, QRegularExpression::MultilineOption | QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatch match = re.match(data);
    if (match.hasMatch()) {
        QString matched = match.captured(1);
        return matched;
    } else {
        return "";
    }
}

QString UtilityString::parseMultiLineLastMatch(const QString& data, const QString& match) {
    auto stringList = parseColumn(data, match);
    if (stringList.size() > 0) {
        return stringList.back();
    } else {
        return "";
    }
}

QStringList UtilityString::parseColumn(const QString& data, const QString& regexp) {
    QRegularExpression re(regexp, QRegularExpression::MultilineOption | QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatchIterator i = re.globalMatch(data);
    QStringList words;
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString word = match.captured(1);
        words.push_back(word);
    }
    return words;
}

QVector<QString> UtilityString::parseColumn(const QString& data, const QString& regexp, [[maybe_unused]] bool a) {
    QRegularExpression re(regexp, QRegularExpression::MultilineOption | QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatchIterator i = re.globalMatch(data);
    QVector<QString> words;
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString word = match.captured(1);
        words.push_back(word);
    }
    return words;
}

QString UtilityString::extractPreLsr(const QString& htmlF) {
    QString separator = "ABC123E";
    auto html = htmlF;
    auto htmlOneLine = html.replace(GlobalVariables::newline, separator);
    auto parsedText = parse(htmlOneLine, GlobalVariables::prePattern);
    return parsedText.replace(separator, GlobalVariables::newline);
}

QString UtilityString::getLastXChars(const QString& data, int count) {
    return data.right(count);
}

QString UtilityString::removeHtml(const QString& htmlF) {
    QRegularExpression re("<.*?>");
    QString html = htmlF;
    html = html.replace(re, "");
    return html;
}

QString UtilityString::insert(const QString& originalString, int index, const QString& stringToAdd) {
    QString s = originalString;
    s.insert(index, stringToAdd);
    return s;
}

QString UtilityString::truncate(const QString& originalString, int length) {
    QString s = originalString;
    s.truncate(length);
    return s;
}

QString UtilityString::substring(const QString& originalString, int start, int end) {
    QString s = originalString;
    return s.mid(start, end - start);
}

int UtilityString::parseAndCount(const QString& data, const QString& regexp) {
    return parseColumn(data, regexp).size();
}

QString UtilityString::addPeriodBeforeLastTwoChars(const QString& data) {
    int index = data.size() - 2;
    return insert(data, index, ".");
}

// bool UtilityString::matches(QString html, QString regexp) {
//     QRegularExpression re(regexp);
//     QRegularExpressionMatch match = re.match(html);
//     return match.hasMatch();
// }

QString UtilityString::toCamelCase(const QString& s) {
    // #if QT_VERSION >= 0x060000
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
        QStringList parts = s.split(' ', Qt::SkipEmptyParts);
    #else
        QStringList parts = s.split(' ', QString::SkipEmptyParts);
    #endif

    for (int i = 0; i < parts.size(); ++i) {
        parts[i].replace(0, 1, parts[i][0].toUpper());
    }
    return parts.join(" ");
}

QStringList UtilityString::parseXml(const QString& payloadF, const QString& delimF){
    auto payload = payloadF;
    auto delim = delimF;
    if (delim == "start-valid-time") {
        payload = payload.replace(QRegularExpression("<end-valid-time>.*?</end-valid-time>") , "").replace(QRegularExpression("<layout-key>.*?</layout-key>") , "");
    }
    payload = payload.replace(QRegularExpression("<name>.*?</name>") , "").replace(QRegularExpression("</" + delim + ">") , "");
    return payload.split("<" + delim + ">");
}

QStringList UtilityString::parseXmlExt(QStringList regexpList, const QString& html) {
    QStringList items;
    for (const auto& reg : regexpList) {
        items.push_back(parse(html, reg));
    }
    return items;
}

QStringList UtilityString::parseXmlValue(const QString& payloadF) {
    auto payload = payloadF;
    payload = replaceRegex(payload, "<name>.*?</name>" , "");
    payload = replaceRegex(payload, "</value>" , "");
    return payload.split(GlobalVariables::xmlValuePattern);
}

QString UtilityString::replaceRegex(const QString& s, const QString& regexp, const QString& newString) {
    auto data = s;
    data = data.replace(QRegularExpression(regexp) , newString);
    return data;
}
