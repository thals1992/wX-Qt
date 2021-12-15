// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYNEXRADCOLORS_H
#define UTILITYNEXRADCOLORS_H

class UtilityNexradColors {
public:
    static double interpolate(int, int, double);
    static double interpolateHue(int, int, double);
    static int interpolateColor(int, int, double);
};

#endif  // UTILITYNEXRADCOLORS_H
