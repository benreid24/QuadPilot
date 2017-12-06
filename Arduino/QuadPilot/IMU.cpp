#include <PID_v1.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "IMU.h"

#define MAXANGLE 30
#define KP 2
#define KI 5
#define KD 1

//Yaw - X (CW = Positive)
//Roll - Z (Right = Positive)
//Pitch - Y (Forward = Positive)
Adafruit_BNO055 ahrs = Adafruit_BNO055(55);
float yOff = 0, zOff = 0;

double pidInputs[2] = {0,0};
double pidOutputs[2] = {0,0};
double pidSetpoints[2] = {0,0};
PID pids[2] = {PID(&pidInputs[0],&pidOutputs[0], &pidSetpoints[0], KP, KI, KD, DIRECT),
               PID(&pidInputs[0],&pidOutputs[0], &pidSetpoints[0], KP, KI, KD, REVERSE)};
int imuOutput[4] = {0,0,0,0};

int clip(int v, int mn, int mx)
{
  if (v<mn)
    return mn;
  if (v>mx)
    return mx;
  return v;
}

void beginIMU()
{
  //Start driver
  if (!ahrs.begin())
  {
    Serial.print("Failed to initialize IMU");
    while (1){}
  }

  //Determine offset
  int i = 0;
  for (; i<10; ++i)
  {
    sensors_event_t event;
    ahrs.getEvent(&event);
    yOff += event.orientation.y;
    zOff += event.orientation.z;
    delay(100);
  }
  yOff /= 10;
  zOff /= 10;

  //Set PID frequencies and start them
  pids[0].SetSampleTime(50);
  pids[1].SetSampleTime(50);
  pids[0].SetMode(AUTOMATIC);
  pids[1].SetMode(AUTOMATIC);
}

void updateIMU(int aileron, int elevator, int throttle, int yaw)
{
  sensors_event_t event;
  ahrs.getEvent(&event);
  int aPitch = event.orientation.y;
  int aRoll = event.orientation.z;
  
  int dRoll = map(aileron,-50,50,-MAXANGLE,MAXANGLE)/2;
  int dPitch = map(elevator,-50,50,-MAXANGLE,MAXANGLE)/2;

  pidSetpoints[0] = dRoll;
  pidSetpoints[1] = dPitch;
  pidInputs[0] = aRoll;
  pidInputs[1] = aPitch;

  //imuOutput[0] = clip(map((dRoll-aRoll),-MAXANGLE,MAXANGLE,-50,50),-50,50)+7; //possibly multiply the angle difference?
  //imuOutput[1] = clip(map((aPitch-dPitch),-MAXANGLE,MAXANGLE,-50,50),-50,50); //negate input for this channel
  imuOutput[0] = pidOutputs[0];
  imuOutput[1] = pidOutputs[1];
  
  imuOutput[2] = throttle;
  imuOutput[3] = yaw;
}

