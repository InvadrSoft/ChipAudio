//
// Created by Myles Inglis on 07/06/2016.
//

#ifndef CHIPAUDIO_TIMESIGNATURE_HPP
#define CHIPAUDIO_TIMESIGNATURE_HPP

namespace chip
{
    /**
     * Struct representing a time signature.
     */
    struct TimeSignature
    {
        /**
         * Constructs a TimeSignature, 4/4 by default.
         * @param _beats The number of beats in each bar (optional)
         * @param _noteValue The value of one beat (optional)
         * @param _division The number of divisions in a whole note (optional)
         */
        TimeSignature(unsigned int _beats = 4, unsigned int _noteValue = 4, unsigned int _division = 16)
                : beats(_beats), noteValue(_noteValue), division(_division) {}

        unsigned int beats;
        unsigned int noteValue;
        unsigned int division;
    };
}

#endif //CHIPAUDIO_TIMESIGNATURE_HPP
