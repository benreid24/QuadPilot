#include <iostream>
#include <cstdlib>
#include "IMU/IMU.hpp"
#include "wiringPi/wiringPi.h"
using namespace std;

int main()
{
    piHiPri(99);
    system("gpio load i2c");
}
