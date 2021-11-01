//
//  charge.h
//  EuPhO2020
//
//  Created by Paul Stanley on 7/9/20.
//  Copyright © 2020 Paul Stanley. All rights reserved.
//  Written by Taavet Kalda
//

#ifndef charge_h
#define charge_h

#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>
#include "3D_vector.h"
#include <chrono>

double const XY_MIN = -0.2;
double const XY_MAX = 0.2;

double const V_MAX = 10000;
double const V_MIN = 1;

//int const debug_mode = 1; // -1 no ouput; 0 normal run; 1 verbose output

int const desired_number_of_steps = 2000000;

bool isFloat( string );
void intended_beam( Vector3d, double, int );
void launch_beam( Vector3d, double, int );

#endif /* charge_h */
