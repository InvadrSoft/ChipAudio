//
// Created by Myles Inglis on 10/06/2016.
//

#ifndef CHIPAUDIO_FILTERLP1POLE_HPP
#define CHIPAUDIO_FILTERLP1POLE_HPP

#include "Module.hpp"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace chip
{
    /**
     * Simple 1 Pole Low-pass filter module.
     */
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
                : Module(INPUTS_TOTAL), a0_(1.0), b1_(0.0), z1_(0.0) {}

        /**
         * Output the result of filtering the input value.
         */
        double output() override
        {
            double cutoff = (input(CUTOFF) == nullptr) ? 0 : input(CUTOFF)->output() / sampleRate();
            double inValue = (input(IN) == nullptr) ? 0 : input(IN)->output();
            b1_ = exp(-2.0 * M_PI * cutoff);
            a0_ = 1.0 - b1_;
            return z1_ += (inValue - z1_) * a0_;
        }

    private:
        double a0_, b1_, z1_;
    };
}

#endif //CHIPAUDIO_FILTERLP1POLE_HPP
