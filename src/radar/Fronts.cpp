// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/Fronts.h"
#include <QVector>
#include "util/UtilityCanvasProjection.h"
#include "util/UtilityList.h"

Fronts::Fronts() {
}

Fronts::Fronts(FrontTypeEnum frontType) {
    this->frontType = frontType;
    if (frontType == FrontTypeEnum::COLD) {
        penColor = QColor(0, 127, 255);
    } else if (frontType == FrontTypeEnum::WARM) {
        penColor = QColor(255, 0, 0);
    } else if (frontType == FrontTypeEnum::STNRY) {
        penColor = QColor(0, 127, 255);
    } else if (frontType == FrontTypeEnum::STNRY_WARM) {
        penColor = QColor(255, 0, 0);
    } else if (frontType == FrontTypeEnum::OCFNT) {
        penColor = QColor(255, 0, 255);
    } else if (frontType == FrontTypeEnum::TROF) {
        penColor = QColor(254, 216, 177);
    }
}

void Fronts::translate(const ProjectionNumbers& pn) {
    if (coordinates.size() > 3) {
        qLines.clear();
        int position = 0;
        for (auto i : UtilityList::range3(0, coordinates.size(), 2)) {
            if (i + 1 < coordinates.size()) {
                const auto coords1 = UtilityCanvasProjection::computeMercatorNumbersFromLatLon(coordinates[i], pn);
                const auto coords2 = UtilityCanvasProjection::computeMercatorNumbersFromLatLon(coordinates[i + 1], pn);
                const auto line = QLineF(coords1[0], coords1[1], coords2[0], coords2[1]);
                qLines.push_back(line);
                position += 1;
            }
        }
    }
}
