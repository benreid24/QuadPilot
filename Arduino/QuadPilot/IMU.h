#ifndef IMU_H
#define IMU_H

extern int imuOutput[4];

void beginIMU();

void updateIMU(int aileron, int elevatoer, int throttle, int yaw);

#endif
