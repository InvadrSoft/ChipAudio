//
// Created by Myles Inglis on 13/06/2016.
//

#include "TimeValue.hpp"

namespace chip
{
    TimeValue& TimeValue::operator++()
    {
        return operator+=(TimeValue(0, 0, 0, 1) );
    }

    TimeValue& TimeValue::operator+=(const TimeValue& rhs)
    {
        int carry = 0;

        tick_ += rhs.tick_;
        while(tick_ > (TICKS_PER_WHOLE_NOTE / timeSignature_.division) )
        {
            tick_ -= TICKS_PER_WHOLE_NOTE / timeSignature_.division;
            carry++;
        }

        division_ += rhs.division_ + carry;
        carry = 0;
        while(division_ > (timeSignature_.division / timeSignature_.noteValue) )
        {
            division_ -= timeSignature_.division / timeSignature_.noteValue;
            carry++;
        }

        beat_ += rhs.beat_ + carry;
        carry = 0;
        while(beat_ > timeSignature_.beats)
        {
            beat_ -= timeSignature_.beats;
            carry++;
        }

        bar_ += rhs.bar_ + carry;

        return *this;
    }

    bool TimeValue::operator<(const TimeValue& rhs) const
    {
        if(bar_ < rhs.bar_ )
        {
            return true;
        }
        if(bar_ == rhs.bar_ )
        {
            if(beat_ < rhs.beat_ )
            {
                return true;
            }
            if(beat_ == rhs.beat_ )
            {
                if(division_ < rhs.division_ )
                {
                    return true;
                }
                if(division_ == rhs.division_ )
                {
                    if(tick_ < rhs.tick_ )
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
}