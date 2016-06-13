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
     * Struct representing a time value.
     */
    struct TimeValue
    {
        unsigned int bar, beat, division, tick;
        TimeSignature timeSignature;

        /**
         * Constructs a time value.
         * @param _bar Bar number
         * @param _beat Beat number
         * @param _division Division number
         * @param _tick Tick number
         */
        TimeValue(unsigned int _bar, unsigned int _beat, unsigned int _division, unsigned int _tick)
                : bar(_bar), beat(_beat), division(_division), tick(_tick)
        {}

        /**
         * Test if two TimeValues are equal.
         * @param rhs Right hand side of comparison
         */
        bool operator==(TimeValue rhs)
        {
            return (bar == rhs.bar) && (beat == rhs.beat) && (division == rhs.division) && (tick == rhs.tick);
        }

        /**
         * Increment the time value by one tick.
         * @return A reference to this TimeValue
         */
        TimeValue& operator++();
    };
}
#endif //CHIPAUDIO_TIMEVALUE_HPP
