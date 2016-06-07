//
// Created by Myles Inglis on 07/06/2016.
//

#ifndef CHIPAUDIO_TIMESIGNATURE_HPP
#define CHIPAUDIO_TIMESIGNATURE_HPP

namespace chip
{
    struct TimeSignature
    {
        TimeSignature()
                : beats(4), noteValue(4) {}

        TimeSignature(unsigned int _beats, unsigned int _noteValue)
                : beats(_beats), noteValue(_noteValue) {}

        unsigned int beats;
        unsigned int noteValue;
    };
}

#endif //CHIPAUDIO_TIMESIGNATURE_HPP
