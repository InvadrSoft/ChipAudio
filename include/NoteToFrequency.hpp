//
// Created by Myles Inglis on 13/06/2016.
//

#ifndef CHIPAUDIO_NOTETOFREQUENCY_HPP
#define CHIPAUDIO_NOTETOFREQUENCY_HPP

#include "Module.hpp"
#include "Notes.hpp"
#include <cmath>

namespace chip
{
    /**
     * Module to convert from note number to frequency.
     */
    class NoteToFrequency : public Module
    {
    public:
        /**
         * Enumeration of all inputs to this module.
         */
        enum Inputs
        {
            IN,
            INPUTS_TOTAL
        };

        /**
         * Default constructor.
         */
        NoteToFrequency() : Module(INPUTS_TOTAL) {}

        /**
         * Convert the input note number to frequency value
         * @return The frequency in Hz
         */
        double output() override
        {
            if(input(IN) == nullptr)
            {
                return 0;
            }
            return TUNING * pow(TWELFTH_ROOT_OF_TWO, input(IN)->output() );
        }
    };
}

#endif //CHIPAUDIO_NOTETOFREQUENCY_HPP
