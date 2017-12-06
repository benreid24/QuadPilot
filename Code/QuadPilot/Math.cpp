#include "Math.hpp"

double _sinLookup[360];

double Sin(int angle)
{
    while (angle<0)
        angle += 360;
    while (angle>360)
        angle -= 360;
    return _sinLookup[angle];
}

double Cos(int angle)
{
    return Sin(angle+90);
}

double Tan(int angle)
{
    return Sin(angle)/Cos(angle);
}

void MatrixMultiply(double a[3][3], double b[3][3], double res[3][3])
{
    double op[3];
    for(int x=0; x<3; x++)
    {
        for(int y=0; y<3; y++)
        {
            for(int w=0; w<3; w++)
            {
                op[w]=a[x][w]*b[w][y];
            }
            res[x][y]=op[0]+op[1]+op[2];
        }
    }
}

double DotProduct(double a[3], double b[3])
{
    double res = 0;
    for (int i = 0; i<3; i++)
    {
        res += a[i]*b[i];
    }
    return res;
}

void CrossProduct(double a[3], double b[3], double res[3])
{
    res[0] = a[1]*b[1] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
}

void vScale(double scalar, double vec[3], double res[3])
{
    for (int i = 0; i<3; i++)
    {
        res[i] = vec[i]*scalar;
    }
}

void vAdd(double a[3], double b[3], double res[3])
{
    for (int i = 0; i<3; i++)
    {
        res[i] = a[i]+b[i];
    }
}
