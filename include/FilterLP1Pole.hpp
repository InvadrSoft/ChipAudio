//
// Created by Myles Inglis on 10/06/2016.
//

#ifndef CHIPAUDIO_FILTERLP1POLE_HPP
#define CHIPAUDIO_FILTERLP1POLE_HPP

#include "Module.hpp"
#include <cmath>

namespace chip
{
    class FilterLP1Pole : public Module
    {
    public:
        /**
         * Enumeration of all inputs to this module.
         */
        enum Inputs
        {
            CUTOFF,
            IN,
            INPUTS_TOTAL
        };

        /**
         * Default constructor.
         */
        FilterLP1Pole()
                : Module(INPUTS_TOTAL), a0(1.0), b1(0.0), z1(0.0) {}

        /**
         * Output the result of filtering the input value.
         */
        double output() override
        {
            double cutoff = (input(CUTOFF) == nullptr) ? 0 : input(CUTOFF)->output() / sampleRate();
            double inValue = (input(IN) == nullptr) ? 0 : input(IN)->output();
            b1 = exp(-2.0 * M_PI * cutoff);
            a0 = 1.0 - b1;
            return z1 += (inValue - z1) * a0;
        }

    private:
        double a0, b1, z1;
    };
}

#endif //CHIPAUDIO_FILTERLP1POLE_HPP
