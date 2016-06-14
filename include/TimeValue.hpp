//
// Created by Myles Inglis on 13/06/2016.
//

#ifndef CHIPAUDIO_TIMEVALUE_HPP
#define CHIPAUDIO_TIMEVALUE_HPP

#include "TimeSignature.hpp"

namespace chip
{
    constexpr int TICKS_PER_WHOLE_NOTE = 3840;

    /**
     * Class representing a time value.
     */
    class TimeValue
    {
    public:
        /**
         * Constructs a time value.
         * @param _bar Bar number
         * @param _beat Beat number
         * @param _division Division number
         * @param _tick Tick number
         */
        TimeValue(unsigned int bar, unsigned int beat, unsigned int division, unsigned int tick)
                : bar_(bar), beat_(beat), division_(division), tick_(tick)
        {}

        /**
         * Test if two TimeValues are equal.
         * @param rhs Right hand side of comparison
         */
        bool operator==(TimeValue rhs)
        {
            return (bar_ == rhs.bar_) && (beat_ == rhs.beat_)
                   && (division_ == rhs.division_) && (tick_ == rhs.tick_);
        }

        /**
         * Increment the time value by one tick.
         * @return A reference to this TimeValue
         */
        TimeValue& operator++();

        const unsigned int& bar() { return bar_; }
        const unsigned int& beat() { return beat_; }
        const unsigned int& division() { return division_; }
        const unsigned int& tick() { return tick_; }

        const TimeSignature timeSignature() { return timeSignature_; }
        void timeSignature(TimeSignature newTimeSig) { timeSignature_ = newTimeSig; }

    private:
        unsigned int bar_, beat_, division_, tick_;
        TimeSignature timeSignature_;
    };
}
#endif //CHIPAUDIO_TIMEVALUE_HPP
