#ifndef IMU_HPP
#define IMU_HPP

#include "Sensors/Accelerometer.hpp"
#include "Sensors/Gyroscope.hpp"
#include "Sensors/Magnetometer.hpp"
#include "Sensors/GPS.hpp"
#include "GyroscopeOrientation.hpp"

/**
 * This is the primary class responsible for storing and updating all of the orientation data
*/
class IMU
{
    int mpu6050;
    GPS gps;
    Gyroscope gyro;
    Accelerometer accelerometer;
    Magnetometer compass;
    GyroscopeOrientation gyroCalc;

    Orientation orientation; //combined Orientation from accelerometers and gyros
    double heading; //averaged heading from gps and compass
    GPSData gpsData; //for storing position and the like

public:
    /**
     * Initializes all internal data but does not call calibrate
    */
    IMU();

    /**
     * Calibrates all sensors. This function doesn't return until the GPS is initialized
    */
    void calibrate();

    /**
     * Updates all sensor data and recalculates the filtered orientation and heading
    */
    void update();

    /**
     * Returns the filtered orientation generated from both gyroscope and accelerometer data
     *
     * \return The current orientation of the quadcopter
    */
    Orientation getOrientation();

    /**
     * Returns the current heading as an average of the compass and gps headings
     *
     * \return The current heading of the quadcopter
    */
    double getHeading();

    /**
     * Returns the most recent data obtained from the GPS
     *
     * \note If a heading is needed use the getHeading function, not the heading returned from this function
     * \return The most recent GPS data
    */
    GPSData getGpsData();
};

#endif // IMU_HPP
