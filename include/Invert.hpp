//
// Created by Myles Inglis on 08/06/2016.
//

#ifndef CHIPAUDIO_INVERT_HPP
#define CHIPAUDIO_INVERT_HPP

#include "Module.hpp"

namespace chip
{
    /**
     * This module outputs the inverse of its singular input.
     */
    class Invert : public Module
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
        Invert() : Module(INPUTS_TOTAL) {}

        /**
         * Output the inverse of the input.
         * @return The inverse of the input value
         */
        double output() override
        {
            if(input(IN) == nullptr)
            {
                return 0;
            }
            return -input(IN)->output();
        }
    };
}

#endif //CHIPAUDIO_INVERT_HPP
