#include "IMU.hpp"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "I2C.h"
#include "Math.hpp"
#include <cmath>
#include <cstdio>
using namespace std;

IMU::IMU()
{
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            DCM[i][j] = 0;
        }
    }
    DCM[0][0] = DCM[1][1] = DCM[2][2] = 1;
    xGOff = yGOff = zGOff = xAOff = yAOff = zAOff = 0;
    lastUpdate = millis();
}

void IMU::calibrateSensors()
{
    system("gpio load i2c");
    mpu6050 = wiringPiI2CSetup(104);
    wiringPiI2CWriteReg8(mpu6050, 0x6b, 0); //turn off idle mode
    wiringPiI2CWriteReg8(mpu6050, 0x1b, 8); //set gyroscope full scale range +-500
    wiringPiI2CWriteReg8(mpu6050, 0x1c, 0);

    double samples[6];
    for (int i = 0; i<6; i++)
    {
        samples[i] = readGyro(X);
    }
    xGOff = average(samples);
    for (int i = 0; i<6; i++)
    {
        samples[i] = readGyro(Y);
    }
    yGOff = average(samples);
    for (int i = 0; i<6; i++)
    {
        samples[i] = readGyro(Z);
    }
    zGOff = average(samples);

    for (int i = 0; i<6; i++)
    {
        samples[i] = readAccel(X);
    }
    xAOff = average(samples);
    for (int i = 0; i<6; i++)
    {
        samples[i] = readAccel(Y);
    }
    yAOff = average(samples);
    for (int i = 0; i<6; i++)
    {
        samples[i] = readAccel(Z);
    }
    zAOff = average(samples);

    lastUpdate = 0;
    XF = 0;
}

double IMU::readGyro(Axis a)
{
    int16_t data = readWord(mpu6050, 0x43+a);
    double out = double(data)*0.0153;
    if (a==X)
        return int(out-xGOff);
    else if (a==Y)
        return int(out-yGOff);
    return int(out-zGOff);
}

double IMU::readAccel(Axis a)
{
    int16_t data = readWord(mpu6050, 0x3B+a);
    double out = double(data)/1670.13252;
    if (a==X)
        return int(out-xAOff);
    else if (a==Y)
        return int(out-yAOff);
    return int(out-zAOff);
}

void IMU::update()
{
    if (lastUpdate==0)
    {
        lastUpdate = micros();
        return;
    }
    double dt = double(micros()-lastUpdate)/1000000;
    lastUpdate = micros();

    //update gyro orientation
        //update matrix
        double samples[6];
        for (int i = 0; i<6; i++)
        {
            samples[i] = readGyro(X);
        }
        double x = average(samples);
        x = (x+wI.x)/2;
        wI.x = average(samples);
        for (int i = 0; i<6; i++)
        {
            samples[i] = readGyro(Y);
        }
        double y = average(samples);
        //y = (y+wI.y)/2;
       // wI.y = average(samples);
        for (int i = 0; i<6; i++)
        {
            samples[i] = readGyro(Z);
        }
        double z = average(samples);
        z = (z+wI.z)/2;
        wI.z = average(samples);

      //  printf("DT: %f\n", dt);
        //printf("X: %f\n", x);

        if (gyroOrientation.roll<90)
            x = 30;
        else
            x = -1;

        if (gyroOrientation.roll>85 && gyroOrientation.roll<95)
            y = 1;
        else
            y = 0;
        z = 0;

        x *= dt;
        y *= dt;
        z *= dt;
        XF += y;
       // printf("Y: %f\n", XF);

        updateM[0][0]=0;
        updateM[0][1]=-z;
        updateM[0][2]=y;
        updateM[1][0]=z;
        updateM[1][1]=0;
        updateM[1][2]=-x;
        updateM[2][0]=-y;
        updateM[2][1]=x;
        updateM[2][2]=0;

        MatrixMultiply(DCM, updateM, temp);
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                DCM[i][j] += temp[i][j];
            }
        }

        //normalize
        double error = -DotProduct(&DCM[0][0], &DCM[1][0])*0.5;
        double renorm = 0;

        vScale(error, &DCM[1][0], &temp[0][0]);
        vScale(error, &DCM[0][0], &temp[1][0]);

        vAdd(&DCM[0][0], &temp[0][0], &temp[0][0]);
        vAdd(&DCM[1][0], &temp[1][0], &temp[1][0]);

        CrossProduct(&temp[0][0], &temp[1][0], &temp[2][0]);

        renorm = 0.5 * (3 - DotProduct(&temp[0][0], &temp[0][0]));
        vScale(renorm, &temp[0][0], &DCM[0][0]);

        renorm = 0.5 * (3 - DotProduct(&temp[1][0], &temp[1][0]));
        vScale(renorm, &temp[1][0], &DCM[1][0]);

        renorm = 0.5 * (3 - DotProduct(&temp[2][0], &temp[2][0]));
        vScale(renorm, &temp[2][0], &DCM[2][0]);

        //drift correction would be applied here ***************************************************************************************************

        //calculate euler angles
        {
            Orientation t = gyroOrientation;
            gyroOrientation.pitch = -asin(DCM[2][0])*180/3.1415926;
            gyroOrientation.roll = atan2(DCM[2][1],DCM[2][2])*180/3.1415926;
            gyroOrientation.yaw = atan2(DCM[1][0],DCM[0][0])*180/3.1415926;
            angularVelocity.x = (gyroOrientation.roll-t.roll)/dt;
            angularVelocity.y = (gyroOrientation.pitch-t.pitch)/dt;
            angularVelocity.z = (gyroOrientation.yaw-t.yaw)/dt;
            orientation = gyroOrientation;
        }

    //read accelerometers and integrate velocity. check if not accelerating, calculate orientation if not
        for (int i = 0; i<6; i++)
        {
            samples[i] = readAccel(X);
        }
        x = average(samples);
        for (int i = 0; i<6; i++)
        {
            samples[i] = readAccel(Y);
        }
        y = average(samples);
        for (int i = 0; i<6; i++)
        {
            samples[i] = readAccel(Z);
        }
        z = average(samples);

        double magSqrd = x*x + y*y + z*z;
        if (magSqrd>77.44 && magSqrd<116.64) //actual acceleration is between 8.8 and 10.8
        {
            accelOrientation.roll = atan2(y,z)*180/3.1415926;
            accelOrientation.pitch = atan2(x, sqrt(y*y + z*z))*180/3.1415926;
            orientation.roll = gyroOrientation.roll*0.9 + accelOrientation.roll*0.1;
            orientation.pitch = gyroOrientation.pitch*0.9 + accelOrientation.pitch*0.1;
            //TODO - how to create orientation matrix from this?
            //maybe just store the difference between accel orientation and gyro orientation as offsets and apply to them calculated gyro orientations in the future
        }

        //TODO - how to eliminate gravity, convert to proper components then integrate

    //read magnometer

    //read gps

    //read temperature
        int16_t word = readWord(mpu6050, 0x41);
        temperature = double(word)/340 + 36.53;
}

Orientation IMU::getOrientation()
{
    return orientation;
}

double IMU::getTemperature()
{
    return temperature;
}

Orientation IMU::getGyroOrientation()
{
    return gyroOrientation;
}

Orientation IMU::getAccelOrientation()
{
    return accelOrientation;
}

Vector IMU::getAngularVelocity()
{
    return angularVelocity;
}

Vector IMU::getVelocity()
{
    return velocity;
}
