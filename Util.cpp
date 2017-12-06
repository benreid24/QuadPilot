#include "Util.hpp"
#include "wiringPi/wiringPi.h"
#include "wiringPi/wiringPiI2C.h"
#include <cmath>
using namespace std;

int16_t readWord(int devId, int reg)
{
    char buf[2] = {wiringPiI2CReadReg8(devId, reg), wiringPiI2CReadReg8(devId, reg+1)};
    return (int16_t(buf[0]) << 8) | buf[1];
}

Vector::Vector()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector::Vector(double a, double b, double c)
{
    x = a;
    y = b;
    z = c;
}

double Vector::magnitude()
{
    return sqrt(x*x+y*y+z*z);
}

double Vector::magnitudeSquared()
{
    return (x*x+y*y+z*z);
}

void Vector::normalize()
{
    double mag = magnitude();
    x /= mag;
    y /=mag;
    z /= mag;
}

Orientation::Orientation()
{
    roll = 0;
    pitch = 0;
    yaw = 0;
}

Orientation::Orientation(double r, double p, double y)
{
    roll = r;
    pitch = p;
    yaw = y;
}
