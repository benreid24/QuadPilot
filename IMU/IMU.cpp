#include "IMU.hpp"
#include "Util.hpp"
#include "wiringPi/wiringPi.h"
#include "wiringPi/wiringPiI2C.h"
using namespace std;

IMU::IMU()
{
    //
}

void IMU::calibrate()
{
    mpu6050 = wiringPiI2CSetup(104);
    wiringPiI2CWriteReg8(mpu6050, 0x6b, 0); //turn off idle mode
    wiringPiI2CWriteReg8(mpu6050, 0x1b, 8); //set gyroscope full scale range +-500
    wiringPiI2CWriteReg8(mpu6050, 0x1c, 0);

    gyro.calibrate(mpu6050);
    accelerometer.calibrate(mpu6050);

    while (!gps.hasFix())
    {
        delay(1000);
    }
}

void IMU::update()
{
    gps.update();
    accelerometer.update();
    gyro.update();
    gyroCalc.update(gyro.getRotation());

    gpsData = gps.getData();
    heading = (compass.getHeading()*0.2+gpsData.heading*0.8);

    Vector accel = accelerometer.getAcceleration();
    if (withinThreshold(accel.magnitudeSquared(),9.81*9.81,0.3)) // TODO - play with this value
    {
        gyroCalc.update(accelerometer.getOrientation());
        orientation = accelerometer.getOrientation();
    }
    else if (withinThreshold(accel.magnitudeSquared(),9.81*9.81,1.5))
    {
        orientation.roll = gyroCalc.getOrientation().roll*0.8 + accelerometer.getOrientation().roll*0.2;
        orientation.pitch = gyroCalc.getOrientation().pitch*0.8 + accelerometer.getOrientation().pitch*0.2;
    }
    else
    {
        orientation.roll = gyroCalc.getOrientation().roll;
        orientation.pitch = gyroCalc.getOrientation().pitch;
    }
    orientation.yaw = gyroCalc.getOrientation().yaw;
}

Orientation IMU::getOrientation()
{
    return orientation;
}

double IMU::getHeading()
{
    return heading;
}

GPSData IMU::getGpsData()
{
    return gpsData;
}
