#ifndef MAGNETOMETER_HPP
#define MAGNETOMETER_HPP

/**
 * Class for reading and storing heading data from the magnetometers
*/
class Magnetometer
{
    double heading;

public:
    /**
     * Does pretty much nothing
    */
    Magnetometer();

    /**
     * Reads data from magnetometers then recalculates heading
    */
    void update();

    /**
     * Returns the heading in degrees with North being 0
    */
    double getHeading();
};

#endif // MAGNETOMETER_HPP
