//
// Created by Myles Inglis on 14/06/2016.
//

#ifndef CHIPAUDIO_PATTERN_HPP
#define CHIPAUDIO_PATTERN_HPP

#include <vector>
#include <map>
#include "Event.hpp"
#include "TimeValue.hpp"

namespace chip
{
    /**
     * A pattern of musical events.
     */
    class Pattern
    {
    public:
        /**
         * Default constructor.
         */
        Pattern() : currentPosition_(1,1,1,1), endPosition_(1,1,1,1) {}

        /**
         * Construct a Pattern using a given time signature.
         * @param timeSignature Time signature for the pattern
         */
        Pattern(TimeSignature timeSignature) : timeSignature_(timeSignature),
                                               currentPosition_(1,1,1,1), endPosition_(1,1,1,1) {}

        /**
         * @return True if pattern has finished, else false
         */
        bool finished() { return currentPosition_ == endPosition_; }

        /**
         * Returns a vector containing all the events in the pattern at the current position (if any)
         * @return Vector of events
         */
        std::vector<Event> getEvents();

        /**
         * Add a new event to the pattern.
         * @param event Event to add
         * @param timeValue Time value for the event
         */
        void addEvent(Event event, TimeValue timeValue);

        /**
         * Advance the pattern to the next tick.
         */
        void nextTick() { ++currentPosition_; }

        /**
         * Set current position back to beginning of pattern.
         */
        void restart() { currentPosition_ = TimeValue(1,1,1,1); }

        const TimeValue& currentPosition() const { return currentPosition_; }
        void currentPosition(TimeValue time) { currentPosition_ = time; }

        const TimeValue& endPosition() const { return endPosition_; }
        void endPosition(TimeValue time) { endPosition_ = time; }

    private:
        TimeValue currentPosition_;
        TimeValue endPosition_;
        TimeSignature timeSignature_;
        std::multimap<TimeValue, Event> events_;
    };
}

#endif //CHIPAUDIO_PATTERN_HPP
