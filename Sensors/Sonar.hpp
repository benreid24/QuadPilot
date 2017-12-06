#ifndef SONAR_HPP
#define SONAR_HPP

/**
 * This class handles data collection for all six sonar sensors. Range and velocity for each direction is measured
*/
class Sonar
{
    double ranges[6];
    double speeds[6];

public:
    /**
     * Enum for passing directions while maintaining readability
    */
    enum Direction
    {
        Top = 0,
        Bottom = 1,
        Front = 2,
        Right = 3,
        Left = 4,
        Back = 5
    };

    /**
     * Initializes the internal data
    */
    Sonar();

    /**
     * Sends a ping out from all the sensors then waits for a response. Calculates the range for each direction, then recalculates the velocity
     * If a sensor times out the range and velocity for that direction are set to -1
    */
    void update();

    /**
     * Returns the range in meters of a given direction
     *
     * \param dir Direction to take the range in
     * \return The range in meters or -1 if out of range
    */
    double getRange(Direction dir);

    /**
     * Returns the velocity in a given direction in m/s
     *
     * \param dir The direction to poll the velocity in
     * \return The velocity in m/s or -1 if out of range
    */
    double getVelocity(Direction dir);
};

#endif // SONAR_HPP
