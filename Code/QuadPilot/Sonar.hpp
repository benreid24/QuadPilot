#ifndef SONAR_HPP
#define SONAR_HPP

class Sonar
{
    double front, right, back, left, top, bottom;
    double frontPrev, rightPrev, backPrev, leftPrev, topPrev, bottomPrev;
    double frontV, rightV, backV, leftV, topV, bottomV;  //with accelerometers, do i even need this? probably... maybe use to confirm integrated accelerometer values?

    double readSensor(int pin);

public:
    Sonar();

    void update();

    double getFrontDistance();
    double getRightDistance();
    double getBackDistance();
    double getLeftDistance();
    double getTopDistance();
    double getBottomDistance();

    double getFrontVelocity();
    double getRightVelocity();
    double getBackVelocity();
    double getLeftVelocity();
    double getTopVelocity();
    double getBottomVelocity();
};

#endif
