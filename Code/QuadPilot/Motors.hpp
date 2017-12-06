#ifndef MOTORS_HPP
#define MOTORS_HPP

class Motors
{
    int motorSpeeds[4]; //0-100%
    int hoverPower; //percentage to hover
    int _roll, _pitch, _climb; //adjusted rates based on input to functions and hover power

    enum Position
    {
        FrontRight = 0,
        FrontLeft = 1,
        RearRight = 2,
        RearLeft = 3
    };
    void setMotor(Position pos, int rate);
    void setSpeeds();

    public:
    Motors(); //init vars, supply commands to setup servoblaster

    void initialize(); //find hover value and calculate motor trims required to stay level (will hold the craft about a foot off the ground and hover during intialization)

    //the following functions control rates only
    void climb(int amnt); //-100 to 100
    void roll(int amnt); //-100 to 100 (negative is left roll)
    void pitch(int amnt); //-100 to 100 (negative is down pitch);
    void level();
};

#endif
