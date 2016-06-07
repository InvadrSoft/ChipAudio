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
         * Default constructor.
         */
        TimeSignature()
                : beats(4), noteValue(4) {}

        /**
         * Non-default constructor.
         * @param _beats The number of beats in each bar
         * @param _noteValue The value of one beat
         */
        TimeSignature(unsigned int _beats, unsigned int _noteValue)
                : beats(_beats), noteValue(_noteValue) {}

        unsigned int beats;
        unsigned int noteValue;
    };
}

#endif //CHIPAUDIO_TIMESIGNATURE_HPP
