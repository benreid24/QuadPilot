#include "Altimeter.hpp"
#include "I2C.h"
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <cmath>
#include <cstdio>
using namespace std;

Altimeter::Altimeter()
{
    up = ut = lastUpdate = id = alt = state = 0;
}

void Altimeter::initialize()
{
    id = wiringPiI2CSetup(0x77);
    wiringPiI2CWriteReg8(id, 0xf4, 0x2e);
    delay(6);
    ut = (wiringPiI2CReadReg8(id, 0xf6)<<8) + wiringPiI2CReadReg8(id, 0xf7);
    wiringPiI2CWriteReg8(id, 0xf4, 0x34+(1<<6));
    delay(9);
    up = (wiringPiI2CReadReg8(id, 0xf6) << 16) + (wiringPiI2CReadReg8(id, 0xf7) << 8) + wiringPiI2CReadReg8(id, 0xf8);
    state = 1;
    update();
}

void Altimeter::update()
{
    if ((state<=3 && millis()-lastUpdate<9) || (state==4 && millis()-lastUpdate<6))
        return;
    lastUpdate = millis();

    if (state<=3)
        up = (wiringPiI2CReadReg8(id, 0xf6) << 16) + (wiringPiI2CReadReg8(id, 0xf7) << 8) + wiringPiI2CReadReg8(id, 0xf8);
    else
        ut = (wiringPiI2CReadReg8(id, 0xf6)<<8) + wiringPiI2CReadReg8(id, 0xf7);
    state++;
    if (state>4)
        state = 0;

    long x1 = ((ut - unsigned(readWord(id, 0xb4))) * unsigned(readWord(id, 0xb2)))/32768;
    printf("x1: %i\n", x1);
    long x2 = (readWord(id, 0xbc) * 2048)/(x1+readWord(id, 0xbe));
    printf("x2: %i\n", x2);
    long b5 = x1 + x2;
    printf("b5: %i\n", b5);
    tmp = double((b5 + 8)/16)/10;
    long b6 = b5 - 4000;
    printf("b6: %i\n", b6);
    x1 = (readWord(id, 0xb8)*(b6*b6/4096))/2048;
    printf("x1: %i\n", x1);
    x2 = readWord(id, 0xac)*b6/2048;
    printf("ac2: %i\n", short(readWord(id, 0xac)));
    printf("x2: %i\n", x2);
    long x3 = x1 + x2;
    printf("x3: %i\n", x3);
    long b3 = (((readWord(id, 0xaa)*4+x3)<<1)+2)/4;
    printf("b3: %i\n", b3);
    x1 = readWord(id, 0xae)*b6/8192;
    printf("x1: %i\n");
    x2 = (readWord(id, 0xb6)*(b6*b6/4096))/65536;
    printf("x2: %i\n", x2);
    x3 = ((x1+x2)+2)/4;
    printf("x3: %i\n", x3);
    unsigned long b4 = unsigned(readWord(id, 0xb0)) * (unsigned long)(x3 + 32768)/32768;
    printf("b4: %u\n", b4);
    unsigned long b7 = ((unsigned long)up - b3) * (50000>>1);
    printf("b7: %u\n", b7);
    if (b7<0x80000000)
        pres = (b7*2)/b4;
    else
        pres = (b7/b4)*2;
    printf("p: %i\n", pres);
    x1 = (pres/256) * (pres/256);
    printf("x1: %i\n", x1);
    x1 = (x1*3038)/65536;
    printf("x1: %i\n", x1);
    x2 = (-7357*pres)/65536;
    printf("x2: %i\n", x2);
    pres = pres + (x1+x2+3791)/16;
    printf("p: %i\n", pres);
        alt = 44330*(1-pow(double(pres)/100/1013.25, 0.1902949));
        printf("Alt: %f\n", alt);
    //alt += (nAlt-alt)*0.4;
    delay(1000000);

    if (state<=3)
        wiringPiI2CWriteReg8(id, 0xf4, 0x34+(1<<6));
    else
        wiringPiI2CWriteReg8(id, 0xf4, 0x2e);
}

double Altimeter::altitude()
{
    return alt;
}

double Altimeter::temperature()
{
    return tmp;
}

long Altimeter::pressure()
{
    return pres;
}
