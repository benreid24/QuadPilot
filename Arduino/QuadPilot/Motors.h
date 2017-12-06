#ifndef MOTORS_H
#define MOTORS_H

void beginMotors();

//aileron,elevator,spin range = [-50,50]
//throttle range = [0,100]
void motorInput(int aileron, int elevator, int throttle, int spin);

#endif
