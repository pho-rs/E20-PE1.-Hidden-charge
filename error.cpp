//
//  error.cpp
//  EuPhO2020
//
//  Created by Paul Stanley on 7/10/20.
//  Copyright © 2020 Paul Stanley. All rights reserved.
//

#include <chrono>
#include "error.h"

Vector3d error_in_beam( Vector3d beam, double radialError, int debug_mode){
    double x, y;

    double variance;

    x = beam.x;
    y = beam.y;

    // Using the C++ Gaussian package.  Correct me if I am wrong!

    variance = radialError*radialError;

    std::mt19937 generator(chrono::system_clock::now().time_since_epoch().count());
    std::normal_distribution<double> error(0,radialError); //I've got conflicting definitions here  do I use variance?

    x += error(generator);
    y += error(generator);

    beam = Vector3d( x, y, 0);

    return(beam);
}

double getRadialSpread( Vector3d focusParameters){
    double minError = 0.002; // two millimeter minimum error, can change this.
    double growError = 0.005; // scaling factor for error growth
    Vector3d idealFocus(2976,4072,3937); // some made up numbers from my past
    Vector3d offset = idealFocus - focusParameters;
    double magError = offset.magnitude();
    if( magError < 1) magError = 1; // let's not get crazy here....
    double error = growError*log10(magError) + minError;
    return error;
}
