//  Written by Taavet Kalda
#ifndef THREED_VECTOR_H
#define THREED_VECTOR_H
#include<iostream>
#include<math.h>
#include<assert.h>

using namespace std;

struct Vector3d
{
    double x, y ,z;
    Vector3d();
    Vector3d(double x1, double y1, double z1);

    Vector3d(const Vector3d &vec);    //copy constructor
    Vector3d operator+(const Vector3d &vec);    //addition
    Vector3d &operator+=(const Vector3d &vec);  //assigning new result to the vector
    Vector3d operator-(const Vector3d &vec);    //substraction
    Vector3d &operator-=(const Vector3d &vec);  //assigning new result to the vector
    Vector3d operator*(double value);    //multiplication
    Vector3d &operator*=(double value);  //assigning new result to the vector.
    Vector3d operator/(double value);    //division
    Vector3d &operator/=(double value);  //assigning new result to the vector
    Vector3d &operator=(const Vector3d &vec);
    double dot_product(const Vector3d &vec); //scalar dot_product
    Vector3d cross_product(const Vector3d &vec);    //cross_product
    double magnitude();  //magnitude of the vector
    Vector3d norm();   //normalized vector
    double square(); //gives square of the vector

    double distance(const Vector3d &vec);    //gives distance between two vectors
    double get_x(); //return x
    double get_y(); //return y
    double get_z(); //return z
    void disp();    //display value of vectors
};

#endif // 3D_VECTOR_H
