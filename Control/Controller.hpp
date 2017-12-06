#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "MotorDriver.hpp"

class IMU;

/**
 * This class abstracts away direct sensor reading and motor control. It will manage the motors and utilize the sensor data to
 * put the craft into the desired orientation while maintaining elevation. When the desired orientation requires a change
 * in heading, the craft is first leveled, then rotated, then put into the desired attitude
*/
class Controller
{
    Oreintation desiredO;

public:
    /**
     * Initializes internal data
    */
    Controller();

    /**
     * Adjusts the motor speeds to obtain the desired orientation while maintaining elevation
    */
    void update(IMU* imu);

    /**
     * Changes the target orientation to whatever is passed into this function
     *
     * \param o The new target orientation
    */
    void setOrientation(Orientation o);

    /**
     * This function will change the target orientation to be level, then will adjust altitude
     *
     * \param a The new target altitude in meters
    */
    void setAltitude(double a);

    /**
     * This fucntion will start all of the motors at a uniform, low speed then start maintating orientation
    */
    void startMotors();

    /**
     * WARNING: This function will stop all of the motors entirely
    */
    void killMotors();
};

#endif // CONTROLLER_HPP
