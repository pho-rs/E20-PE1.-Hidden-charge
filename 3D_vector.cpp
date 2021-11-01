//  Written by Taavet Kalda
#include "3D_vector.h"
#include<iostream>
#include<math.h>
#include<assert.h>
using namespace std;

Vector3d::Vector3d()
{
    x = 1;
    y = 0;
    z = 0;
}

Vector3d::Vector3d(double x1, double y1, double z1)
{
    x = x1;
    y = y1;
    z = z1;
}

Vector3d::Vector3d(const Vector3d &vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

//addition

Vector3d Vector3d ::operator+(const Vector3d &vec)
{
    return Vector3d(x + vec.x, y + vec.y, z + vec.z);
}

Vector3d &Vector3d ::operator+=(const Vector3d &vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

//substraction//
Vector3d Vector3d ::operator-(const Vector3d &vec)
{
    return Vector3d(x - vec.x, y - vec.y, z - vec.z);
}

Vector3d &Vector3d::operator-=(const Vector3d &vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}

//scalar multiplication

Vector3d Vector3d ::operator*(double value)
{
    return Vector3d(x * value, y * value, z * value);
}



Vector3d &Vector3d::operator*=(double value)
{
    x *= value;
    y *= value;
    z *= value;
    return *this;
}

//scalar division
Vector3d Vector3d ::operator/(double value)
{
    assert(value!=0);
    return Vector3d(x / value, y / value, z / value);
}

Vector3d &Vector3d ::operator/=(double value)
{
    assert(value!=0);
    x /= value;
    y /= value;
    z /= value;
    return *this;
}


Vector3d &Vector3d::operator=(const Vector3d &vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
    return *this;
}

//Dot product
double Vector3d::dot_product(const Vector3d &vec)
{
    return x * vec.x + vec.y * y + vec.z * z;
}

//cross product
Vector3d Vector3d::cross_product(const Vector3d &vec)
{
    double ni = y * vec.z - z * vec.y;
    double nj = z * vec.x - x * vec.z;
    double nk = x * vec.y - y * vec.x;
    return Vector3d(ni, nj, nk);
}

double Vector3d::magnitude()
{
    return sqrt(square());
}

double Vector3d::square()
{
    return x*x + y*y + z*z;
}

Vector3d Vector3d:: norm()
{
    assert(magnitude()!=0);
    *this /= magnitude();
    return *this;
}

double Vector3d::distance(const Vector3d &vec)
{
    Vector3d dist = *this-vec;
    return dist.magnitude();
}

double Vector3d::get_x()
{
    return x;
}

double Vector3d::get_y()
{
    return y;
}

double Vector3d::get_z()
{
    return z;
}

void Vector3d::disp()
{
    cout<<x<<" "<<y<<" "<<z<<endl;
}
