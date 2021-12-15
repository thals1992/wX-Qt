// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/UtilityList.h"

int UtilityList::findex(const QString& value, const QStringList& qlist) {
    for (auto index = 0; index < qlist.size(); index +=1) {
        if (qlist[index].startsWith(value)) {
            return index;
        }
    }
    return 0;
}

int UtilityList::indexOf(const QStringList& qlist,  const QString& value) {
    for (auto index = 0; index < qlist.size(); index +=1) {
        if (qlist[index] == value) {
            return index;
        }
    }
    return 0;
}

QVector<int> UtilityList::range(int count) {
    QVector<int> list;
    for (auto index = 0; index < count; index++) {
        list.push_back(index);
    }
    return list;
}

QVector<int> UtilityList::range3(int from, int to, int by) {
    QVector<int> list;
    for (auto i = from; i < to; i += by) {
        list.push_back(i);
    }
    return list;
}

QVector<int> UtilityList::range2(int from, int to) {
    QVector<int> list;
    for (auto i = from; i < to; i += 1) {
        list.push_back(i);
    }
    return list;
}

QStringList UtilityList::reversed(const QStringList& items) {
    auto returnList = items;
    std::reverse(returnList.begin(), returnList.end());
    return returnList;
}
