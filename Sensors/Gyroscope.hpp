#ifndef GYROSCOPE_HPP
#define GYROSCOPE_HPP

#include "Util.hpp"

/**
 * This class stores and updates data obtained from the gyroscope
*/
class Gyroscope
{
    int mpu6050;

    Vector intialVel,lastRot;
    int lTime;

public:
    /**
     * Initializes the data but does not call calibrate
    */
    Gyroscope();

    /**
     * Initialize and calibrate the gyroscope sensor
     *
     * \param dev The device id of the mpu6050 sensor on I2C
    */
    void calibrate(int dev);

    /**
     * Updates the rotarion from gyroscope data and elapsed time
    */
    void update();

    /**
     * Returns the rotation in degrees since the last call to update
     *
     * \return A Vector containing the rotation in degrees
    */
    Vector getRotation();
};

#endif // GYROSCOPE_HPP
