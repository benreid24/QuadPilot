#include "GPS.hpp"
#include <wiringSerial.h>
#include <wiringPi.h>
#include <cstdlib>
using namespace std;

GPS::GPS()
{
    id = -1;
    lastUpdate = 0;
    data.lattitude = data.longitude = data.speed = data.heading = data.altitude = 0;
    data.sataliteCount = 0;
    fix = false;
}

bool GPS::initialize()
{
    id = serialOpen("/dev/ttyAMA0", 9600);
    lastUpdate = millis();
    return (id!=-1);
}

bool GPS::hasFix()
{
    return fix;
}

GpsData GPS::getData()
{
    return data;
}

void GPS::update()
{
    if (millis()-lastUpdate>=1050)
    {
        lastUpdate = millis();

        int len = serialDataAvail(id);
        if (len>5)
        {
            inputBuffer.reserve(serialDataAvail(id));
            while (serialDataAvail(id)>0)
            {
                inputBuffer.push_back(serialGetchar(id));
            }
            string temp;
            unsigned int i = 0;

            while (inputBuffer.size()>0)
            {
                for (; inputBuffer[i]!='$' && i<inputBuffer.size(); i++); //ignore up to $
                if (i>=inputBuffer.size())
                    return;
                inputBuffer.erase(0,i);
                i = 0;

                temp.clear();
                for (i++; inputBuffer[i]!='\r' && i<inputBuffer.size(); i++) //read string
                {
                    temp.push_back(inputBuffer[i]);
                }
                if (i<inputBuffer.size())
                    parseString(temp);
            }
        }
    }
}

void GPS::parseString(string input) //starts after $
{
    string temp;
    unsigned int i = 0;

    for (; input[i]!=','; i++) temp.push_back(input[i]);
    i++;

    if (temp=="GPRMC")
    {
        for (i++; input[i]!=','; i++); //move past utc time
        i++;

        i += 2; //move past comma and onto start of lattitude
        temp.clear();
        temp.push_back(input[i]);
        temp.push_back(input[i+1]);
        data.lattitude = atoi(temp.c_str()); //read degrees in
        i += 2; //move to start of minutes
        temp = input.substr(i, 7);
        i += 7;
        data.lattitude += atof(temp.c_str())/60; //add the minutes as decimal

        i += 2; //move to start of longitude
        temp = input.substr(i, 3);
        i += 3;
        data.longitude = atoi(temp.c_str());
        temp = input.substr(i, 7);
        i += 7;
        data.longitude += atof(temp.c_str())/60;
        i += 2; //move onto start of ground speed

        temp.clear();
        for (; input[i]!=','; i++) temp.push_back(input[i]); //read speed in knots
        i++;
        data.speed = atof(temp.c_str()) * 0.51444;
        temp.clear();
        for (; input[i]!=','; i++) temp.push_back(input[i]); //read heading
        i++;
        data.heading = atof(temp.c_str());
    }
    else if (temp=="GPGGA")
    {
        for (int j = 0; j<5; i++)
        {
            if (input[i]==',')
                j++;
        }
        temp.clear();
        temp.push_back(input[i]);
        i+=2;
        int var = atoi(temp.c_str());
        fix = var==1 || var==2;
        temp = input.substr(i, 2);
        i += 2;
        data.sataliteCount = atoi(temp.c_str());
        for (i++; input[i]!=','; i++); //skip hdop
        temp.clear();
        for (i++; input[i]!=','; i++) temp.push_back(input[i]); //read altitude
        data.altitude = atof(temp.c_str());
    }
}
