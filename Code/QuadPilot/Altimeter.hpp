#ifndef ALTIMETER_HPP
#define ALTIMETER_HPP

class Altimeter
{
    int id;
    long ut;
    unsigned long up;
    int state; //0-3 = set sensor to update pressure when exiting update, 4 = set sensor to update temp
    int lastUpdate;
    double alt, tmp;
    long pres;

    public:
    Altimeter();

    void initialize();
    void update();
    double altitude();
    double temperature();
    long pressure();
};

#endif
