//
//  error.h
//  EuPhO2020
//
//  Created by Paul Stanley on 7/10/20.
//  Copyright © 2020 Paul Stanley. All rights reserved.
//

#ifndef error_h
#define error_h

#include <stdio.h>
#include <math.h>
#include <random>
#include "3D_vector.h"

double const RANDSCALING = 1.0;

Vector3d error_in_beam( Vector3d, double, int );

double getRadialSpread( Vector3d );

#endif /* error_h */
