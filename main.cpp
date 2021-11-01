//
//  main.cpp
//  EuPhO2020
//
//  Created by Paul Stanley on 7/9/20.
//  Copyright © 2020 Paul Stanley. All rights reserved.
//
// Adapted charge.cpp from Taavet Kalda

#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <string.h>
#include <iomanip>
#include <math.h>
#include "3D_vector.h"
#include "charge.h"
#include "error.h"
#include <chrono>
#include <cstdlib>

double xinit, yinit, Vinit;
int beamMagnetInit, beamExtractInit, beamFocusInit;

int debug_mode = 0; //set to zero for normal operation, one for verbose

Vector3d beam, focusParameters;
char action_request;


double read_double() {
    std::string line;
    std::cin >> line;
    if (isFloat(line)) {
        return std::atof(line.c_str());
    }
    return -10000; // Change to -10000 from -1 to avoid interference with valid x,y measurements!
}


int main(int argc, const char * argv[]) {

    /* Comment out of final code!
     if (argc == 2) {
        if (strcmp(argv[1],"-verbose")) {
            std::cout << "Verbose mode for debugging" << endl;
            debug_mode=1;
        }
    }*/


//    std::cout << "Launching beam!\n";
    //bool doBeamLoop = {false};
    //bool tuneBeam = {false};
    bool getInitValue = {false};
    bool alternativeBeamLoop = true;
    double beamx_0 = 0, beamy_0 = 0 , accelV_0 = 0; // change names to avoid some double naming challenges
    double radialError = 0; //beamMagnet = 0, beamFocus = 0, beamExtract = 0, ;

    /*
     while(tuneBeam){  // get parameters to try and tune beam

        getInitValue=true; //set flag to collect beam magnet
        while(getInitValue){
            std::cout << "Beam Magnet Current in mA: ";
            while(!(std::cin >> beamMagnetInit)){
                std::cin.clear();
                std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Invalid entry.  Enter an integer between 0 and 5000: ";
            };
            beamMagnet = (float)beamMagnetInit;
            if (x0 < XY_MIN || x0 > XY_MAX) {
                std::cout << "Magnet current out of bounds" << endl;
            } else {
                getInitValue=false;
            }
        }
        getInitValue=true; //set flag to collect beam extractor
        while(getInitValue){
            std::cout << "Beam Extractor potential in V: ";
            while(!(std::cin >> beamExtractInit)){
                std::cin.clear();
                std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Invalid entry.  Enter an integer between 0 and 5000: ";
            };
            beamExtract = (float)beamExtractInit;
            if (x0 < XY_MIN || x0 > XY_MAX) {
                std::cout << "Extractor potential out of bounds" << endl;
            } else {
                getInitValue=false;
            }
        }
        getInitValue=true; //set flag to collect beam focus
        while(getInitValue){
            std::cout << "Beam Focus potential in V: ";
            while(!(std::cin >> beamFocusInit)){
                std::cin.clear();
                std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Invalid entry.  Enter an integer between 0 and 5000: ";
            };
            beamFocus = (float)beamFocusInit;
            if (x0 < XY_MIN || x0 > XY_MAX) {
                std::cout << "Focus potential out of bounds." << endl;
            } else {
                getInitValue=false;
            }
        }


        focusParameters = Vector3d(beamMagnet, beamExtract, beamFocus);

        radialError = getRadialSpread(focusParameters);

        std::cout << "Beam Spread in mm: " << 1000*radialError << endl;

        std::cout << "(0) to continue tuning or (1) to use beam: ";
        while(!(std::cin >> Vinit)){
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Invalid entry.  Enter either 0 or 1: ";
        };
        if(Vinit==1) {
            tuneBeam=false;
        }
    }
     */

    /*
     while(doBeamLoop){

        getInitValue=true; //set flag to collect V initial
        while(getInitValue){
            std::cout << "Beam Energy in V; 0 returns to main menu: ";
            while(!(std::cin >> Vinit)){
                std::cin.clear();
                std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Invalid entry.  Enter an integer between 0 and 10000: ";
            };
            V0 = (float)Vinit;
            if(Vinit == 0){
                std::cout << "Beam Turned Off, returning to main menu" << endl;
                doBeamLoop = false;
            } else if (V0 < 0 || V0 > V_MAX) {
                std::cout << "Energy of the electron beam out of bounds." << endl;
            } else {
                getInitValue=false;
            }
        }


        getInitValue=true; //set flag to collect x initial
        while(getInitValue){
            std::cout << "X beam location in cm: ";
            while(!(std::cin >> xinit)){
                std::cin.clear();
                std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Invalid entry.  Enter an integer between 0 and 20: ";
            };
            x0 = (float)xinit/100;
            if (x0 < XY_MIN || x0 > XY_MAX) {
                std::cout << "x-coordinate of the electron beam out of bounds." << endl;
            } else {
                getInitValue=false;
            }
        }

        getInitValue=true; //set flag to collect y initial
        while(getInitValue){
            std::cout << "Y beam location in cm: ";
            while(!(std::cin >> yinit)){
                std::cin.clear();
                std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Invalid entry.  Enter an integer between 0 and 20: ";
            };
            y0 = (float)yinit/100;
            if (y0 < XY_MIN || y0 > XY_MAX) {
                std::cout << "y-coordinate of the electron beam out of bounds." << endl;
            } else {
                getInitValue=false;
            }
        }



        beam = Vector3d(x0, y0, 0);  // set initial beam position

        intended_beam(beam, V0, debug_mode);

        //radialError = 0.015;

        beam = error_in_beam(beam, radialError, debug_mode); // shift initial location of beam by small amount.

        launch_beam( beam, Vinit, debug_mode); // launch beam to find target location

    }
     */

    while (alternativeBeamLoop) {
        getInitValue = true; //set flag to collect V initial
        std::cout << "Beam accelerating voltage in V: ";
        while (getInitValue){
            Vinit = read_double();
            /*
             if (Vinit == -1) {
                std::cout << "Invalid entry.  Voltage must be between 1 and 10000: ";
            } else {
             */
                if (Vinit < 0 || Vinit > V_MAX) {
                    std::cout << "Invalid entry.  Voltage must be between 1 and 10000: ";
                } else {
                    accelV_0 = Vinit; //changed name
                    getInitValue = false;
                }

        }

        getInitValue = true; //set flag to collect V initial
        std::cout << "x-coordinate of the electron beam in cm: ";
        while (getInitValue){
            xinit = read_double();
            /*
             if (xinit == -1) {
                std::cout << "Invalid entry.  x-coordinate must be between -20 and 20: ";
            } else {
             */
                xinit /= 100;
                if (xinit < XY_MIN || xinit > XY_MAX) {
                    std::cout << "Invalid entry.  x-coordinate must be between -20 and 20: ";
                } else {
                    beamx_0 = xinit; //changed name
                    getInitValue = false;
                }

        }

        getInitValue = true; //set flag to collect V initial
        std::cout << "y-coordinate of the electron beam in cm: ";
        while (getInitValue){
            yinit = read_double();
            /*
             if (yinit == -1) {
                std::cout << "Invalid entry.  y-coordinate must be between -20 and 20: ";
            } else {
             */
                yinit /= 100;
                if (yinit < XY_MIN || yinit > XY_MAX) {
                    std::cout << "Invalid entry.  y-coordinate must be between -20 and 20: ";
                } else {
                    beamy_0 = yinit; //change name
                    getInitValue = false;
                }

        }

        radialError = 0.0005;

        beam = Vector3d(beamx_0, beamy_0, 0);  // set initial beam position

        intended_beam(beam, accelV_0, debug_mode);

        //radialError = 0.015;

        beam = error_in_beam(beam, radialError, debug_mode); // shift initial location of beam by small amount.

        launch_beam(beam, Vinit, debug_mode); // launch beam to find target location
    }

    return 0;
}


