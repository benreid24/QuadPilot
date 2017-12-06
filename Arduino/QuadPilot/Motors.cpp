#include <Adafruit_PWMServoDriver.h>
#include "Motors.h"

#define SENSITIVITY 8

#define ESCMIN 2200
#define ESCMAX 3600

#define FRONTRIGHT 0
#define FRONTLEFT 1
#define BACKRIGHT 2
#define BACKLEFT 3

Adafruit_PWMServoDriver escs = Adafruit_PWMServoDriver();
int motorVals[4];

void beginMotors()
{
  escs.begin();
  escs.setPWMFreq(480); //play with this to figure out a good number
  for (int i = 0; i<4; ++i)
    motorVals[i] = 0;
}

void motorInput(int R, int P, int T, int Y)
{
  T = map(T,0,100,0,90);
  R = map(R,-50,50,-T/SENSITIVITY,T/SENSITIVITY);
  P = map(P,-50,50,-T/SENSITIVITY,T/SENSITIVITY);
  Y = map(Y,-50,50,-T/SENSITIVITY,T/SENSITIVITY);
  
  motorVals[FRONTRIGHT] = map(T+P-R-Y, 0, 100, ESCMIN, ESCMAX);
  motorVals[FRONTLEFT] = map(T+P+R+Y, 0, 100, ESCMIN, ESCMAX);
  motorVals[BACKRIGHT] = map(T-P-R+Y, 0, 100, ESCMIN, ESCMAX);
  motorVals[BACKLEFT] = map(T-P+R-Y, 0, 100, ESCMIN, ESCMAX);
  escs.setPWM(FRONTRIGHT,0,motorVals[FRONTRIGHT]);
  escs.setPWM(FRONTLEFT,0,motorVals[FRONTLEFT]);
  escs.setPWM(BACKLEFT,0,motorVals[BACKLEFT]);
  escs.setPWM(BACKRIGHT,0,motorVals[BACKRIGHT]);
}

