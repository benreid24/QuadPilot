#ifndef IMU_HPP
#define IMU_HPP

struct Orientation
{
    Orientation() { roll = pitch = yaw = 0; }
    double roll, pitch, yaw;
};

struct Vector
{
    Vector() { x = y = z = 0; }
    double x, y, z;
};

class IMU
{
    int mpu6050; //device id
    double xGOff, yGOff, zGOff; //gyro offsets
    double xAOff, yAOff, zAOff; //accelerometer offsets

    Orientation orientation; //time integrated orientation with complimentary filter and accelerometer corrections
    double temperature;
    //what other things will i need?

    Orientation gyroOrientation;
    double DCM[3][3];
    double temp[3][3];
    double updateM[3][3];
    Vector angularVelocity; //time integrated with respect to earth reference frame
    Vector wI;
    double XF;

    Orientation accelOrientation;
    Vector velocity; //time integrated velocities (with gravity pulled out based on orientation)

    //something for heading and gps position

    int lastUpdate; //for time integration

    enum Axis
    {
        X = 0,
        Y = 2,
        Z = 4
    };

    double readGyro(Axis a);
    double readAccel(Axis a);

public:
    IMU(); //initialize vars and i2c stuff

    void calibrateSensors();

    void update();

    Orientation getOrientation();
    double getTemperature();
    Orientation getGyroOrientation();
    Orientation getAccelOrientation(); //returns (1000, 1000, 1000) if accelerometer orientation is unavailable

    Vector getAngularVelocity();
    Vector getVelocity();
};

#endif // IMU_HPP
