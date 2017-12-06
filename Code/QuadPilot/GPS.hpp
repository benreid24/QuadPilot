#ifndef GPS_HPP
#define GPS_HPP

#include <string>

//degrees = degrees + minutes/60 + seconds/3600

struct GpsData
{
    double lattitude, longitude;
    double speed, heading;
    double altitude;
    int sataliteCount;
};

class GPS
{
    int id;
    std::string inputBuffer;
    int lastUpdate;

    GpsData data;
    bool fix;

    void parseString(std::string str);

public:
    GPS();

    bool initialize();
    void update();

    bool hasFix(); //either read gpio or determine from data
    GpsData getData();
};

#endif // GPS_HPP

