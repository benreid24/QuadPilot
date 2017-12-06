#ifndef GPS_HPP
#define GPS_HPP

/**
 * Struct for compactly storing and passing GPS related data
*/
struct GPSData
{
    double lattitude, longitude, altitude, heading, speed, estimatedHeight;
    int sataliteCount;
};

class GPS
{
    //TODO - internal data here
    double initialAlt; //used for estimating height

public:
    /**
     * Initializes internal data
    */
    GPS();

    /**
     * Updates internal data from GPS sensor. Call at 10Hz or less (internally enforced)
    */
    void update();

    /**
     * Tells whether or not a position fix has been acquired
     *
     * \return True if the GPS is good to go, false otherwise
    */
    bool hasFix();

    /**
     * Returns the most recent data from the GPS
     *
     * \return GPSData object containing the most recent GPS data
    */
    GPSData getData();
};

#endif // GPS_HPP
