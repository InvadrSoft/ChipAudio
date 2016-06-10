//
// Created by Myles Inglis on 09/06/2016.
//

#ifndef CHIPAUDIO_OSCILLATOR_HPP
#define CHIPAUDIO_OSCILLATOR_HPP

#include "Module.hpp"
#include "WaveTable.hpp"

namespace chip
{
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
         * @param _interpolation Type of interpolation to use (optional)
         */
        Oscillator(InterpolationType _interpolation = NONE)
                : Module(INPUTS_TOTAL), interpolation(_interpolation), phase(0) {}

        /**
         * Contructs an Oscillator using a given WaveTable.
         * @param _wave WaveTable for Oscillator to use
         * @param _interpolation Type of interpolation to use (optional)
         */
        Oscillator(WaveTable _wave, InterpolationType _interpolation = NONE)
                : Module(INPUTS_TOTAL), wave(_wave), interpolation(_interpolation), phase(0) {}

        /**
         * Generates and outputs the next sample.
         * @return Generated sample value
         */
        double output() override;

    private:
        WaveTable wave;
        InterpolationType interpolation;
        double phase;
    };
}

#endif //CHIPAUDIO_OSCILLATOR_HPP
