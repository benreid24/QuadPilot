#include "I2C.h"
#include <wiringPiI2C.h>

double average(int16_t* data)
{
    int mx = -10000000, mn = 10000000;
    int mxi(0), mni(0);
    for (int i = 0; i<6; i++)
    {
        if (data[i]>mx)
        {
            mx = data[i];
            mxi = i;
        }
        else if (data[i]<mn)
        {
            mn = data[i];
            mni = i;
        }
    }
    data[mni] = data[mxi] = 0;
    return double(data[0] + data[1] + data[2] + data[3] + data[4] + data[5])/4;
}

double average(double* data)
{
    int mx = -10000000, mn = 10000000;
    int mxi(0), mni(0);
    for (int i = 0; i<6; i++)
    {
        if (data[i]>mx)
        {
            mx = data[i];
            mxi = i;
        }
        else if (data[i]<mn)
        {
            mn = data[i];
            mni = i;
        }
    }
    data[mni] = data[mxi] = 0;
    return (data[0] + data[1] + data[2] + data[3] + data[4] + data[5])/4;
}

int16_t readWord(int devId, int reg)
{
    char buf[2] = {wiringPiI2CReadReg8(devId, reg), wiringPiI2CReadReg8(devId, reg+1)};
    return (int16_t(buf[0]) << 8) | buf[1];
}
