//
// Created by Myles Inglis on 13/06/2016.
//

#include "TimeValue.hpp"

namespace chip
{
    TimeValue& TimeValue::operator++()
    {
        tick_++;
        if(tick_ > (TICKS_PER_WHOLE_NOTE / timeSignature_.division) )
        {
            tick_ = 1;
            division_++;
            if(division_ > (timeSignature_.division / timeSignature_.noteValue) )
            {
                division_ = 1;
                beat_++;
                if(beat_ > timeSignature_.beats)
                {
                    beat_ = 1;
                    bar_++;
                }
            }
        }
        return *this;
    }
}