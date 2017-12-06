#ifndef FLIGHTPLAN_HPP
#define FLIGHTPLAN_HPP

#include <vector>

/**
 * Struct to represent a step in a FlightPlan
*/
struct FlightStep
{
    /**
     * Enum to represent the type of step it is
    */
    enum Type
    {
        WayPoint,
        Motion,
        ReturnHome,
        Land
    }type;

    double lat, lon; //position for waypoint
    double dir, time; //direction and how long for motion
};

/**
 * This class is responsible for loading the flight plan from the filesystem and giving each step to the auto-pilot
*/
class FlightPlan
{
    std::vector<FlightStep> steps;
    int curStep;

public:
    /**
     * Loads the flightplan from the filesystem
    */
    FlightPlan();

    /**
     * Returns the current step that needs to be completed
     *
     * \return The current step being executed
    */
    FlightStep getCurrentStep();

    /**
     * Moves on to the next step in the plan. Only call once the previous step has been completed
    */
    void update();

    /**
     * Tells whether or not there are more steps to be completed
     *
     * \return Whether or not the flight plan has been completed
    */
    bool isFinished();
};

#endif // FLIGHTPLAN_HPP
