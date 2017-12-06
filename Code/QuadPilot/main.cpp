#include <cmath>
#include <cstdio>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <errno.h>
#include "Math.hpp"
#include "I2C.h"
#include "IMU.hpp"
#include "GPS.hpp"
#include "Altimeter.hpp"
#include <fstream>
using namespace std;

int main()
{
    for (int i = 0; i<360; i++)
    {
        _sinLookup[i] = sin(double(i)*180/3.1415926);
    }

    IMU imu;
    imu.calibrateSensors();

    GPS gps;
    bool ret = gps.initialize();
    if (!ret)
        printf("%i\n", errno);

    Altimeter altimeter;
    altimeter.initialize();


    while (true)
    {
       /* imu.update();
        printf("Pitch: %f\n", imu.getGyroOrientation().pitch);
        printf("Roll: %f\n", imu.getGyroOrientation().roll);
        printf("Yaw: %f\n", imu.getGyroOrientation().yaw);*/
        /*gps.update();
        GpsData data = gps.getData();
        printf("Lattitude: %f\n", data.lattitude);
        printf("Longitude: %f\n", data.longitude);
        printf("Elevation: %f\n", data.altitude);
        printf("Heading: %f\n", data.heading);
        printf("Speed: %f\n", data.speed);
        printf("Satalites: %i\n", data.sataliteCount);*/
        altimeter.update();
        printf("Altitude: %f\n", altimeter.altitude());
        printf("Temperature: %f\n", altimeter.temperature());
        printf("Pressure: %i\n", altimeter.pressure()/100);

        delay(20);
    }

    return 0;
}
