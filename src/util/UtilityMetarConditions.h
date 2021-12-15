// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYMETARCONDITIONS_H
#define UTILITYMETARCONDITIONS_H

#include <QHash>
#include <QString>

class UtilityMetarConditions {
public:
    static const QHash<QString, QString> iconFromCondition;
};

#endif  // UTILITYMETARCONDITIONS_H
