#ifndef ORIENTATION_HPP
#define ORIENTATION_HPP

#include "Math.hpp"

class Orientation
{
    Quaternion temp;
    Vector bearing, horAxis, vertAxis;
    double roll, yaw, pitch;

public:
    Orientation();

    double getRoll();
    double getPitch();
    double getYaw();

    void update(double dX, double dY, double dZ);
    void setYaw(double y); //use once at startup using either compass or gps heading
};

#endif // ORIENTATION_HPP
