#ifndef GYROSCOPEORIENTATION_HPP
#define GYROSCOPEORIENTATION_HPP

#include "Util.hpp"

/**
 * Class for containing and updating the quaternions needed for calculating the orientation of the drone.
*/
class GyroscopeOrientation
{
    //TODO - quaternions and whatnot here

public:
    /**
     * Initializes all of the quaternions used for the calculations
    */
    GyroscopeOrientation();

    /**
     * Recalculates the orientation from a small rotation about the vehicle standard basis axes
     *
     * \param angularRot Vector describing the local rotation
    */
    void update(Vector angularRot);

    /**
     * Resets the quaternions to reflect the given orientation. Use to compensate for drift when accelerometer data is valid for calculating the orientation
     *
     * \param ori Orientation object representing the orientation to update the quaternions to
    */
    void update(Orientation ori);

    /**
     * Returns the orientation calculated from the gyroscope data
     *
     * \return An Orientation object containing the drone's current attitude
    */
    Orientation getOrientation();
};

#endif // GYROSCOPEORIENTATION_HPP
