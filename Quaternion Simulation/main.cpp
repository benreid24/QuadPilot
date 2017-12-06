#include "Orientation.hpp"
#include <iostream>
using namespace std;

int main()
{
    /*
    Vector point(0.707107,0,0.707107);
    Vector axis(0,1,0);
    Quaternion rot(45,axis);

    cout << "Point: " << point << endl;
    cout << "Yaw: " << point.yaw() << endl;
    cout << "Pitch: " << point.polarAngle() << endl << endl;

    point = rot*point*rot.reciporical();
    cout << "Point: " << point << endl;
    cout << "Yaw: " << point.yaw() << endl;
    cout << "Pitch: " << point.polarAngle() << endl;
    point.normalize();
    cout << "Normalized point: " << point << endl;
    cout << "Yaw: " << point.yaw() << endl;
    cout << "Pitch: " << point.polarAngle() << endl;

    cout << point.magnitude() << endl << axis.magnitude() << endl << rot.magnitude() << endl << rot.reciporical().magnitude() << endl;
    */

    Orientation o;
    o.update(0, 0.5, 0.5);

    cout << "Yaw: " << o.getYaw() << endl;
    cout << "Pitch: " << o.getPitch() << endl;

    return 0;
}
