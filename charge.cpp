//
//  charge.cpp
//  EuPhO2020
//  Created on 7.7.2020
//  Written by Taavet Kalda
//


#include "charge.h"

//using namespace::std;

double const m_e = 9.10938356e-31;
//double m_e = 1.6726219e-27;
double const e_0 = 1.60217662e-19, k_e = 8.9875517923e9;

//double const x_p = 1.0;
//double const y_p = 2.0;
//double const z_p = 3.0;
Vector3d r_p = Vector3d(0.05435205, -0.0259338, -0.1150416);
double const q_p = -8.62193e-11;
//double const radius_p = 0.0001;



void terminate_() {
    std::cout << "Terminating...";
    //exit(0);
}

void announce(string code, double x = 0, double y = 0)
{
    if (code == "MISS") {
        std::cout << "Electron not detected...\n";
    } else if (code == "HIT") {
        std::cout << fixed << setprecision(1) << "Electron detected at (x, y) = (" << x*100 << "cm, " << y*100 << "cm)\n"; // change display precision
    }
    std::cout << "------------------------------------------------\n";
}

bool isFloat( string myString ) {
    std::istringstream iss(myString);
    float f;
    iss >> noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
}

Vector3d get_acc(Vector3d r) {
    double r_sq = r.square();
    Vector3d F = r * (-k_e) * q_p * e_0 / r_sq / sqrt(r_sq);
    return F / m_e;
}


void solve(Vector3d r, Vector3d v, int debug_mode, int desired_number_of_steps) {
    //double dt = -r.z / desired_number_of_steps / v.magnitude();
    double dt_const = 100;
    Vector3d delta_r = r - r_p;
    double deflection_0 = sqrt(delta_r.x*delta_r.x + delta_r.y*delta_r.y);
    for (int i = 0; i < 2*desired_number_of_steps; i++) {

        if (r.magnitude() > 1000) {
            break;
        }

        Vector3d acc = get_acc(delta_r);
        double dt = dt_const / acc.magnitude();
        Vector3d eff_acc = (acc + get_acc(delta_r + v * dt))/2; //+ acc * dt * dt / 2)) / 2
        delta_r += v * dt + eff_acc * dt * dt / 2;
        v += eff_acc * dt;

        r = delta_r + r_p;
        if (r.z > 0) {
            if (debug_mode == 1) {
                std::cout << "Number of iterations: " << i << "\n";
                std::cout << "Final coordinates: (" << r.x << ", " << r.y << ", 0)\n";
                std::cout << "Initial vs Final deflection: " << deflection_0 << " " << sqrt(delta_r.x*delta_r.x + delta_r.y*delta_r.y) << "\n";
                std::cout << "Final speed: " << v.magnitude() << "\n";;
            }
            if (debug_mode >= 0) {
                if (XY_MIN <= r.x && r.x <= XY_MAX && XY_MIN <= r.y && r.y <= XY_MAX) {
                    announce("HIT", r.x, r.y);
                } else {
                    announce("MISS");
                }
            }
            return;
        }
    }
    announce("MISS");
}

// info debug_mode -1 = no output, 0 only problem info, 1 debug info
void parse_and_solve(double x_0, double y_0, double V_0, int debug_mode, int desired_number_of_steps)
{
    if (debug_mode == 1) {
        std::cout << "Electron actually fired from (x, y) = (" << x_0*100 << "cm, " << y_0*100 << "cm)\n";
        std::cout << "with accelerating voltage " << V_0 << "V\n";
        std::cout << "..\n";
    }
    double v_0_mag = pow(2 * V_0 * e_0 / m_e, 0.5);
    if (debug_mode == 1) {
        //std::cout << "Initial coordinates: (" << x_0 << ", " << y_0 << ", -inf)\n";
        std::cout << "Initial speed: " << v_0_mag << "\n";
    }
    Vector3d v_0 = Vector3d(0, 0, v_0_mag);
    Vector3d r_0 = Vector3d(x_0, y_0, -10);
    solve(r_0, v_0, debug_mode, desired_number_of_steps);
}

/* remove old code for CL interface
int main(int argc, char** argv) {
    if (argc != 4) {
        std::cout << "Enter the correct number of arguments!\nFound " << argc << " arguments.\n";
        terminate_();
    }
    if (!isFloat(argv[1])) {
        std::cout << "Enter the correct format for the x-coordinate of the electron beam." << endl;
        terminate_();
    }
    if (!isFloat(argv[2])) {
        std::cout << "Enter the correct format for the y-coordinate of the electron beam." << endl;
        terminate_();
    }
    if (!isFloat(argv[3])) {
        std::cout << "Enter the correct format for the voltage applied on the electron beam." << endl;
        terminate_();
    }

 */

void intended_beam(Vector3d beam, double V0, int debug_mode){
    if (debug_mode == 1) {
        std::cout << "Electron fired from (x, y) = (" << beam.x*100 << "cm, " << beam.y*100 << "cm)\n";
        std::cout << "with accelerating voltage " << V0 << "V\n";
        std::cout << "..\n";
    }
    if (debug_mode == 0) {
        std::cout << "Electron beam fired with parameters (x, y, V) = (" << beam.x*100 << "cm, " << beam.y*100 << "cm, " << V0 << "V)\n";
    }
}

void launch_beam(Vector3d beam, double V0, int debug_mode){

    parse_and_solve(beam.x, beam.y, V0, debug_mode, desired_number_of_steps);

    //0.05435, -0.02593, -0.115   7.237, 7.236   12.987 12.935
    // 5.435, -2.593, -11.5
    /*int debug_mode = 0;
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    parse_and_solve(-0.05425, -0.02593, 2, debug_mode, 4000000);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    std::cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(end - begin).count()/1000 << "[µs]" << endl;
    */
}
