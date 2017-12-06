#ifndef ACCELEROMETER_HPP
#define ACCELEROMETER_HPP

#include "Util.hpp"

/**
 * This class stores and updates information obtained from the accelerometer
*/
class Accelerometer
{
    int mpu6050;

    Vector currentAccel;
    int lastTime;

public:
    /**
     * Initializes the data but does not call calibrate
    */
    Accelerometer();

    /**
     * Calibrates the accelerometer data from the sensor
     *
     * \param dev The device id of the mpu6050 sensor on I2C
    */
    void calibrate(int dev);

    /**
     * Updates the acceleration data from the sensor
    */
    void update();

    /**
     * Returns the current acceleration in m/s^2
    */
    Vector getAcceleration();

    /**
     * Returns the calculated orientation based on the gravitational acceleration vector
     *
     * \return Returns the Orientation if the acceleration vector is zero or (0,0,0) otherwise
    */
    Orientation getOrientation();
};

#endif // ACCELEROMETER_HPP
