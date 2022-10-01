// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/UtilityString.h"
#include <QtGlobal>
#include <QRegularExpression>
// #include <algorithm>
#include <regex>
#include "common/GlobalVariables.h"
#include "objects/WString.h"

// bool UtilityString::match(const QString& data, const QString& regexp) {
//     auto re = QRegularExpression(regexp, QRegularExpression::MultilineOption | QRegularExpression::DotMatchesEverythingOption);
//     QRegularExpressionMatch match = re.match(data);
//     if (match.hasMatch()) {
//         return true;
//     }
//     return false;
// }

vector<string> UtilityString::parseTwo(const string& data, const string& regexp) {
    QRegularExpression re{QString::fromStdString(regexp), QRegularExpression::MultilineOption | QRegularExpression::DotMatchesEverythingOption};
    QRegularExpressionMatch match = re.match(QString::fromStdString(data));
    if (match.hasMatch()) {
        auto matched1 = match.captured(1).toStdString();
        auto matched2 = match.captured(2).toStdString();
        return {matched1, matched2};
    } else {
        return {"", ""};
    }
}

QString UtilityString::parse(const QString& data, const QString& regexp) {
    QRegularExpression re{regexp, QRegularExpression::MultilineOption | QRegularExpression::DotMatchesEverythingOption};
    QRegularExpressionMatch match = re.match(data);
    if (match.hasMatch()) {
        return match.captured(1);
    } else {
        return "";
    }
}

string UtilityString::parse(const string& data, const string& regexp) {
    QRegularExpression re{QString::fromStdString(regexp), QRegularExpression::MultilineOption | QRegularExpression::DotMatchesEverythingOption};
    QRegularExpressionMatch match = re.match(QString::fromStdString(data));
    if (match.hasMatch()) {
        auto matched = match.captured(1);
        return matched.toStdString();
    } else {
        return "";
    }
}

string UtilityString::parseMultiLineLastMatch(const string& data, const string& match) {
    auto stringList = parseColumn(data, match);
    if (!stringList.empty()) {
        return stringList.back();
    } else {
        return "";
    }
}

vector<string> UtilityString::parseColumn(const string& data, const string& regexp) {
    QRegularExpression re{QString::fromStdString(regexp), QRegularExpression::MultilineOption | QRegularExpression::DotMatchesEverythingOption};
    QRegularExpressionMatchIterator i = re.globalMatch(QString::fromStdString(data));
    vector<string> words;
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        auto word = match.captured(1);
        words.push_back(word.toStdString());
    }
    return words;
}

string UtilityString::extractPreLsr(const string& htmlF) {
    QString separator = "ABC123E";
    auto html = QString::fromStdString(htmlF);
    const auto htmlOneLine = html.replace(QString::fromStdString(GlobalVariables::newline), separator);
    auto parsedText = parse(htmlOneLine, QString::fromStdString(GlobalVariables::prePattern));
    return parsedText.replace(separator, QString::fromStdString(GlobalVariables::newline)).toStdString();
}

string UtilityString::getLastXChars(const string& data, int count) {
    return QString::fromStdString(data).right(count).toStdString();
}

string UtilityString::removeHtml(const string& htmlF) {
    QRegularExpression re{"<.*?>"};
    auto html = QString::fromStdString(htmlF);
    html = html.replace(re, "");
    return html.toStdString();
}

string UtilityString::insert(const string& originalString, int index, const string& stringToAdd) {
    auto s = QString::fromStdString(originalString);
    s.insert(index, QString::fromStdString(stringToAdd));
    return s.toStdString();
}

string UtilityString::truncate(const string& originalString, int length) {
    auto s = QString::fromStdString(originalString);
    s.truncate(length);
    return s.toStdString();
}

string UtilityString::substring(const string& s, int start, int end) {
    // if (end == -1) {
    //     return QString::fromStdString(s).mid(start, end - start).toStdString();
    // } else {
    //     return QString::fromStdString(s).mid(start, end - start).toStdString();
    // }
    if (end == -1) {
        try {
            return s.substr(start);
        } catch(std::out_of_range& exception) {
            return s;
        }
    } else {
        try {
            return s.substr(start, end - start);
        } catch(std::out_of_range& exception) {
            return s;
        }
    }
}

// KEEP
// int UtilityString::parseAndCount(const QString& data, const QString& regexp) {
//    return parseColumn(data, regexp).size();
// }

string UtilityString::addPeriodBeforeLastTwoChars(const string& data) {
    const auto index = static_cast<int>(data.size()) - 2;
    return insert(data, index, ".");
}

// bool UtilityString::matches(QString html, QString regexp) {
//     QRegularExpression re(regexp);
//     QRegularExpressionMatch match = re.match(html);
//     return match.hasMatch();
// }

string UtilityString::toCamelCase(const string& s) {
    // #if QT_VERSION >= 0x060000
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
        QStringList parts = QString::fromStdString(s).split(' ', Qt::SkipEmptyParts);
    #else
        QStringList parts = QString::fromStdString(s).split(' ', QString::SkipEmptyParts);
    #endif
    for (auto& part : parts) {
        part.replace(0, 1, part[0].toUpper());
    }
    return parts.join(" ").toStdString();
}

vector<string> UtilityString::parseXml(const string& payloadF, const string& delim) {
    auto payload = payloadF;
    if (delim == "start-valid-time") {
        payload = replaceRegex(payload, "<end-valid-time>.*?</end-valid-time>", "");
        payload = replaceRegex(payload, "<layout-key>.*?</layout-key>", "");
    }
    payload = replaceRegex(payload, "<name>.*?</name>" , "");
    payload = replaceRegex(payload, "</" + delim + ">" , "");
    return WString::split(payload, "<" + delim + ">");
}

vector<string> UtilityString::parseXmlExt(const vector<string>& regexpList, const string& html) {
    vector<string> items;
    for (const auto& reg : regexpList) {
        items.push_back(parse(html, reg));
    }
    return items;
}

vector<string> UtilityString::parseXmlValue(const string& payloadF) {
    auto payload = payloadF;
    payload = replaceRegex(payload, "<name>.*?</name>" , "");
    payload = replaceRegex(payload, "</value>" , "");
    return WString::split(payload, GlobalVariables::xmlValuePattern);
}

bool UtilityString::match(const string& s, const string& regexp) {
    return regex_match(s, std::regex(regexp));
}

string UtilityString::replaceRegex1(const string& s, const string& regexp, const string& newString) {
    return regex_replace(s, std::regex(regexp), newString);
}

string UtilityString::replaceRegex(const string& s, const string& regexp, const string& newString) {
    return regex_replace(s, std::regex(regexp), newString);
}

string UtilityString::parseNwsPre(const string& html) {
    const auto lines = WString::split(html, GlobalVariables::newline);
    auto preFound = false;
    auto endPreFound = false;
    vector<string> modifiedLines;
    for (const auto& line : lines) {
        if (WString::contains(line, "<pre>")) {
            preFound = true;
            continue;
        }
        if (WString::contains(line, "</pre>")) {
            endPreFound = true;
        }
        if (preFound && !endPreFound) {
            modifiedLines.push_back(line);
        }
    }
    return WString::join(modifiedLines, GlobalVariables::newline);
}
