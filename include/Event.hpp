//
// Created by Myles Inglis on 07/06/2016.
//

#ifndef CHIPAUDIO_EVENT_HPP
#define CHIPAUDIO_EVENT_HPP

#include <string>
#include <cmath>

namespace chip
{
    /**
     * Enumeration of all event types.
     */
    enum EventType
    {
        NOTE_ON,
        NOTE_OFF,
        PARAM_CHANGE
    };

    /**
     * Struct representing a musical event.
     */
    struct Event
    {
        /**
         * Constructs an event.
         * @param _type The type of event
         * @param _note Note number (optional)
         * @param _value Event value (optional)
         * @param _paramID ID of parameter (optional)
         */
        Event(EventType _type, int _note = 0, int _value = 0, std::string _paramID = "")
                : note(_note), value(_value), type(_type), paramID(_paramID) {}
        Event(int _type, int _note, int _value, std::string _paramID = "")
                : type(static_cast<EventType>(_type) ), value(_value), note(_note), paramID(_paramID) {}

        EventType type;
        int note, value;
        std::string paramID;
    };

}

#endif //CHIPAUDIO_EVENT_HPP
