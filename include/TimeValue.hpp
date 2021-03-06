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
        TimeValue() : bar_(1), beat_(1), division_(1), tick_(1) {}

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
         * @return True if equal, else false
         */
        bool operator==(const TimeValue& rhs) const
        {
            return (bar_ == rhs.bar_) && (beat_ == rhs.beat_)
                   && (division_ == rhs.division_) && (tick_ == rhs.tick_);
        }

        /**
         * Test whether rhs is before this TimeValue.
         * @param rhs Right hand side of comparison
         * @return True if this TimeValue comes before rhs
         */
        bool operator<(const TimeValue& rhs) const;

        bool operator>(const TimeValue& rhs) const
        {
            return rhs < *this && !(*this == rhs);
        }

        /**
         * Increment the time value by one tick.
         * @return A reference to this TimeValue
         */
        TimeValue& operator++();

        /**
         * Add the time value on the rhs to this TimeValue.
         * @param rhs Right hand side of addition
         * @return A reference to this TimeValue
         */
        TimeValue& operator+=(const TimeValue& rhs);

        TimeValue& operator-=(const TimeValue& rhs);

        const unsigned int& bar() const { return bar_; }
        const unsigned int& beat() const { return beat_; }
        const unsigned int& division() const { return division_; }
        const unsigned int& tick() const { return tick_; }

        const TimeSignature timeSignature() { return timeSignature_; }
        void timeSignature(TimeSignature newTimeSig) { timeSignature_ = newTimeSig; }

    private:
        unsigned int bar_, beat_, division_, tick_;
        TimeSignature timeSignature_;
    };

    inline TimeValue operator-(TimeValue lhs, const TimeValue &rhs)
    {
        return lhs -= rhs;
    }

    inline TimeValue operator+(TimeValue lhs, const TimeValue& rhs)
    {
        return lhs += rhs;
    }
}
#endif //CHIPAUDIO_TIMEVALUE_HPP
