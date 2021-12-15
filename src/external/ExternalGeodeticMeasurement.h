/* Geodesy by Mike Gavaghan
 *
 * http://www.gavaghan.org/blog/free-source-code/geodesy-library-vincentys-formula/
 *
 * This code may be freely used and modified on any personal or professional
 * project.  It comes with no warranty.
 *
 * BitCoin tips graciously accepted at 1FB63FYQMy7hpC2ANVhZ5mSgAZEtY1aVLf
 */

#ifndef EXTERNALGEODETICMEASUREMENT_H
#define EXTERNALGEODETICMEASUREMENT_H

#include "external/ExternalGeodeticCurve.h"

class ExternalGeodeticMeasurement : ExternalGeodeticCurve {
public:
    ExternalGeodeticMeasurement(double, double, double, double);

private:
    double elevationChange;
    double p2p;
};

#endif  // EXTERNALGEODETICMEASUREMENT_H
