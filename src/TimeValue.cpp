//
// Created by Myles Inglis on 13/06/2016.
//

#include "TimeValue.hpp"

namespace chip
{
    TimeValue& TimeValue::operator++()
    {
        tick++;
        if(tick > (TICKS_PER_WHOLE_NOTE / timeSignature.division) )
        {
            tick = 1;
            division++;
            if(division > (timeSignature.division / timeSignature.noteValue) )
            {
                division = 1;
                beat++;
                if(beat > timeSignature.beats)
                {
                    beat = 1;
                    bar++;
                }
            }
        }
        return *this;
    }
}