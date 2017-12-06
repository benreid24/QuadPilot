#ifndef I2C_H
#define I2C_H

#include <cstdlib>

int16_t readWord(int devId, int addr);
double average(int16_t* data); //takes 6 measurements, discards highest and lowest then averages
double average(double* data);

#endif
