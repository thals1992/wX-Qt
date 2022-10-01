/* Geodesy by Mike Gavaghan
 *
 * http://www.gavaghan.org/blog/free-source-code/geodesy-library-vincentys-formula/
 *
 * This code may be freely used and modified on any personal or professional
 * project.  It comes with no warranty.
 *
 * BitCoin tips graciously accepted at 1FB63FYQMy7hpC2ANVhZ5mSgAZEtY1aVLf
 */

#ifndef EXTERNALGEODETICCALCULATOR_H
#define EXTERNALGEODETICCALCULATOR_H

#include <vector>
#include "external/ExternalEllipsoid.h"
#include "external/ExternalGlobalCoordinates.h"

using std::vector;

class ExternalGeodeticCalculator {
public:
    static ExternalGlobalCoordinates calculateEndingGlobalCoordinates(ExternalGlobalCoordinates, double, double);
    static ExternalGlobalCoordinates calculateEndingGlobalCoordinatesOriginal(ExternalEllipsoid, ExternalGlobalCoordinates, double, double, vector<double> *);
};

#endif  // EXTERNALGEODETICCALCULATOR_H
