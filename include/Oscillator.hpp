//
// Created by Myles Inglis on 09/06/2016.
//

#ifndef CHIPAUDIO_OSCILLATOR_HPP
#define CHIPAUDIO_OSCILLATOR_HPP

#include "Module.hpp"
#include "WaveTable.hpp"

namespace chip
{
    /**
     * Wavetable oscillator module.
     */
    class Oscillator : public Module
    {
    public:
        /**
         * Enumeration of all inputs to this module.
         */
        enum Inputs
        {
            FREQUENCY,
            AMPLITUDE,
            INPUTS_TOTAL
        };

        /**
         * Enumeration of all possible types of interpolation between wavetable steps.
         */
        enum InterpolationType
        {
            NONE,
            LINEAR,
            COSINE
        };

        /**
         * Default constructor.
         * @param interpolation Type of interpolation to use (optional)
         */
        Oscillator(InterpolationType interpolation = NONE)
                : Module(INPUTS_TOTAL), interpolation_(interpolation), phase_(0) {}

        /**
         * Contructs an Oscillator using a given WaveTable.
         * @param wave WaveTable for Oscillator to use
         * @param interpolation Type of interpolation to use (optional)
         */
        Oscillator(WaveTable wave, InterpolationType interpolation = NONE)
                : Module(INPUTS_TOTAL), wave_(wave), interpolation_(interpolation), phase_(0) {}

        /**
         * Generates and outputs the next sample.
         * @return Generated sample value
         */
        double output() override;

    private:
        WaveTable wave_;
        InterpolationType interpolation_;
        double phase_;
    };
}

#endif //CHIPAUDIO_OSCILLATOR_HPP
