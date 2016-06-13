//
// Created by Myles Inglis on 13/06/2016.
//

#ifndef CHIPAUDIO_TIMEVALUE_HPP
#define CHIPAUDIO_TIMEVALUE_HPP

#include "TimeSignature.hpp"

namespace chip
{
    constexpr int TICKS_PER_WHOLE_NOTE = 3840;

    struct TimeValue
    {
        unsigned int bar, beat, division, tick;
        TimeSignature timeSignature;

        TimeValue(unsigned int _bar, unsigned int _beat, unsigned int _division, unsigned int _tick)
                : bar(_bar), beat(_beat), division(_division), tick(_tick)
        {}

        bool operator==(TimeValue rhs)
        {
            return (bar == rhs.bar) && (beat == rhs.beat) && (division == rhs.division) && (tick == rhs.tick);
        }

        TimeValue& operator++();
    };
}
#endif //CHIPAUDIO_TIMEVALUE_HPP
