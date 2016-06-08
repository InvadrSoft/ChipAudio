//
// Created by Myles Inglis on 07/06/2016.
//

#ifndef CHIPAUDIO_TIMESIGNATURE_HPP
#define CHIPAUDIO_TIMESIGNATURE_HPP

namespace chip
{
    struct TimeSignature
    {
        /**
         * Constructs a TimeSignature, 4/4 by default.
         * @param _beats The number of beats in each bar
         * @param _noteValue The value of one beat
         */
        TimeSignature(unsigned int _beats = 4, unsigned int _noteValue = 4)
                : beats(_beats), noteValue(_noteValue) {}

        unsigned int beats;
        unsigned int noteValue;
    };
}

#endif //CHIPAUDIO_TIMESIGNATURE_HPP
