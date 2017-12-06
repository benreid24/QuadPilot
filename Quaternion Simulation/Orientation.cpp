#include "Orientation.hpp"
#include <iostream>
using namespace std;

Orientation::Orientation() : bearing(1,0,0)
{
    roll = 0;
    yaw = 0;
    pitch = 0;
}

void Orientation::update(double dX, double dY, double dZ)
{
    horAxis = Vector(0,1,0);

    temp = Quaternion(yaw, Vector(0,0,1));
    temp.rotatePoint(horAxis);           //rotate yaw about earth vertical axis
    temp = Quaternion(roll,bearing);
    temp.rotatePoint(horAxis);  //rotate roll about bearing axis

    vertAxis = bearing.crossProduct(horAxis); //cross product yeilds perpindicular bivector

    Quaternion(dY,horAxis).rotatePoint(bearing);
    Quaternion(dZ,vertAxis).rotatePoint(bearing);

    roll += dX;
    yaw = bearing.yaw();
    pitch = bearing.polarAngle();
}

double Orientation::getRoll()
{
    return roll;
}

double Orientation::getYaw()
{
    return yaw;
}

double Orientation::getPitch()
{
    return pitch;
}

void Orientation::setYaw(double y)
{
    yaw = y;
}
