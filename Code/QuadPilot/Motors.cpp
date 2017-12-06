#include "Motors.hpp"
#include "Systems.hpp"
#include "Math.hpp"
#include <cstdlib>
#include <string>
#include <cstdio>
#include <wiringPi.h>
using namespace std;

Motors::Motors()
{
    for (int i = 0; i<4; i++)
    {
        motorSpeeds[i] = 0;
    }
    hoverPower = 0;
    _roll = _pitch = _climb = 0;
    system("servod --p1pins=\"\" --p5pins=\"3,4,5,6\" --pcm");
}

void Motors::setMotor(Position pos, int rate)
{
    int tmp = hoverPower + rate;
    if (tmp<15)
        tmp = 15;
    if (tmp>100)
        tmp = 100;
    motorSpeeds[pos] = tmp;

    char p[2], spd[4];
    sprintf(p, "%d", pos);
    sprintf(spd, "%d", tmp);
    system((string("echo ")+p+"="+spd+"% > /dev/servoblaster").c_str()); //TODO - convert to using fstream, this takes 20ms to execute!
}

void Motors::setSpeeds()
{
    motorSpeeds[FrontRight] = hoverPower + _climb + _pitch - _roll;
    motorSpeeds[FrontLeft] = hoverPower + _climb + _pitch + _roll;
    motorSpeeds[RearRight] = hoverPower + _climb - _pitch - _roll;
    motorSpeeds[RearLeft] = hoverPower + _climb - _pitch + _roll;
    setMotor(FrontRight, motorSpeeds[FrontRight]);
    setMotor(FrontLeft, motorSpeeds[FrontLeft]);
    setMotor(RearRight, motorSpeeds[RearRight]);
    setMotor(RearLeft, motorSpeeds[RearLeft]);
}

void Motors::initialize()
{
    //find hover value
    double gndDis = sonar.getBottomDistance();
    while (!withinThreshhold(sonar.getBottomDistance()-gndDis, double(30), double(5)))
    {
        hoverPower++;
        setMotor(FrontRight, hoverPower);
        setMotor(FrontLeft, hoverPower);
        setMotor(RearRight, hoverPower);
        setMotor(RearLeft, hoverPower);
    }
    int t = millis();
    while (millis()-t<10000)
    {
        if (sonar.getBottomVelocity()>0)
        {
            hoverPower--;
            setMotor(FrontRight, hoverPower);
            setMotor(FrontLeft, hoverPower);
            setMotor(RearRight, hoverPower);
            setMotor(RearLeft, hoverPower);
        }
        else if (sonar.getBottomVelocity()<0)
        {
            hoverPower++;
            setMotor(FrontRight, hoverPower);
            setMotor(FrontLeft, hoverPower);
            setMotor(RearRight, hoverPower);
            setMotor(RearLeft, hoverPower);
        }
    }
}

void Motors::climb(int amnt)
{

}
