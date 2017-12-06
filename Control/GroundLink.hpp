#ifndef GROUNDLINK_HPP
#define GROUNDLINK_HPP

/**
 * This class is responsible for creating and maintaining a network connection to the ground station and handles all communication
*/
class GroundLink
{
    //TODO - networking stuff here

public:
    /**
     * This will establish the link
    */
    GroundLink();

    /**
     * Handles all network traffic and updates recent messges from ground control
    */
    void update();

    /**
     * Enum to represent messages from ground control
    */
    enum Message
    {
        None,
        Hold,
        Resume,
        Return
    };

    /**
     * This fucntion returns the msot recent message from ground control
     *
     * \return The most recent message from ground control
    */
    Message getMessage();
};

#endif // GROUNDLINK_HPP
