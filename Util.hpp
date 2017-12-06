#ifndef UTIL_HPP
#define UTIL_HPP

#include <cstdint>

/**
 * Struct for passing vectors around easily and performing operations on and with them
*/
struct Vector
{
    double x,y,z;

    /**
     * Initialize the vector to (0,0,0)
    */
    Vector();

    /**
     * Initialize the vector with the passed values
     *
     * \param _x X component of the vector
     * \param _y Y component of the vector
     * \param _z Z component of the vector
    */
    Vector(double _x, double _y, double _z);

    /**
     * Returns the magnitude of the vector
     *
     * \return The vector's magnitude
    */
    double magnitude();

    /**
     * Returns the square of the vectors magnitude
     *
     * \return The magnitude of the vector squared
    */
    double magnitudeSquared();

    /**
     * Normalizes the vector while maintaining direction by dividing each component by the magnitude
    */
    void normalize();
};

/**
 * Similar to Vector class but with variables renamed for better readability
*/
struct Orientation
{
    double roll, pitch, yaw;

    /**
     * Initializes the Orientation object with zero values
    */
    Orientation();

    /**
     * Initializes the Orientation with the given inputs
     *
     * \param r The roll
     * \param p The pitch
     * \param y The yaw
    */
    Orientation(double r, double p, double y);
};

/**
 * Reads a word from the I2C bus at the given address on the given device
 *
 * \param devId Id of the device to read from
 * \param addr Address of the data to read off the device
 * \return The value stored in the given address on the device
*/
int16_t readWordFromI2C(int devId, int addr);

/**
 *Function to determine if two values are within a certain threshold of each other. Use for doubleing point comparisons
 *
 * \param r One of the values to compare
 * \param l The other value to compare
 * \param thresh The threshold to test for
 * \return Whether or not the values are within the given threshold of each other
*/
template<typename T>
bool withinThreshold(T r, T l, T thresh)
{
    return (r-l<thresh || l-r<thresh);
}

#endif // UTIL_HPP
