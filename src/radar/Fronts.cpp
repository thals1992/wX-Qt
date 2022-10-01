// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/Fronts.h"
#include "util/UtilityCanvasProjection.h"
#include "util/UtilityList.h"

Fronts::Fronts(FrontTypeEnum frontType)
    : frontType{ frontType }
{
    if (frontType == COLD) {
        penColor = QColor{0, 127, 255};
    } else if (frontType == WARM) {
        penColor = QColor{255, 0, 0};
    } else if (frontType == STNRY) {
        penColor = QColor{0, 127, 255};
    } else if (frontType == STNRY_WARM) {
        penColor = QColor{255, 0, 0};
    } else if (frontType == OCFNT) {
        penColor = QColor{255, 0, 255};
    } else if (frontType == TROF) {
        penColor = QColor{254, 216, 177};
    }
}

void Fronts::translate(int paneIndex, const ProjectionNumbers& pn) {
    if (coordinates.size() > 3) {
        coordinatesModified[paneIndex].clear();
        for (size_t i : range3(0, coordinates.size(), 2)) {
            if (i + 1 < coordinates.size()) {
                const auto coords1 = UtilityCanvasProjection::computeMercatorNumbersFromLatLon(coordinates[i], pn);
                const auto coords2 = UtilityCanvasProjection::computeMercatorNumbersFromLatLon(coordinates[i + 1], pn);
                coordinatesModified[paneIndex].push_back(QLineF{coords1[0], coords1[1], coords2[0], coords2[1]});
            }
        }
    }
}
