#ifndef MOTORDRIVER_HPP
#define MOTORDRIVER_HPP

/**
 * This class interacts directly with the PWM motors and is responsible for calculating the required motor speeds given the desired behvior
*/
class MotorDriver
{
    int motorSpeeds[4]; //0-255? something
    bool needsRecalc;

    double pitch, roll; //direction to move and the amount (0-1)
    double throttle; //0 to 1
    double yaw; //-1 to 1

public:
    /**
     * Initializes all internal data
    */
    MotorDriver();

    /**
     * If necessary, recalculates motor speeds and updates PWM outputs
    */
    void update();

    /**
     * Sets the pitch and roll amounts of the motors. The input is normalized so that the attitude vector is unit
     *
     * \param _roll Amount to roll the craft by. Input is in the range [-1,1]
     * \param _pitch Amount to pitch the craft by. Input is in the range [-1,1]
    */
    void setAttitude(double _roll, double _pitch);

    /**
     * Sets the base speed of all the motors. All other inputs are just scalar mulipliers to this value
     *
     * \param t The level of throttle to apply. Accepted range is [0,1]
    */
    void setThrottle(double t);

    /**
     * Sets the angular rate by differentiating the speeds of the counterclockwise and clockwise motors
     *
     * \param y The amount to angle by. Accepted range is [-1,1]
    */
    void setYaw(double y);
};

#endif // MOTORDRIVER_HPP
