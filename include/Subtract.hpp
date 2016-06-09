//
// Created by Myles Inglis on 09/06/2016.
//

#ifndef CHIPAUDIO_SUBTRACT_HPP
#define CHIPAUDIO_SUBTRACT_HPP

#include "Module.hpp"

namespace chip
{
    /**
     * This module calculates the result of the first input subtracted
     * by the second input.
     */
    class Subtract : public Module
    {
    public:
        /**
         * Enumeration of all inputs to this module.
         */
        enum Inputs
        {
            IN1,
            IN2,
            INPUTS_TOTAL
        };

        /**
         * Default constructor.
         */
        Subtract() : Module(INPUTS_TOTAL) {}

        /**
         * Output the value of the first input subtracted
         * by the second input.
         * @return The calculated result.
         */
        double output() override
        {
            double value1 = (input(IN1) == nullptr) ? 0 : input(IN1)->output();
            double value2 = (input(IN2) == nullptr) ? 0 : input(IN2)->output();
            return value1 - value2;
        }
    };
}

#endif //CHIPAUDIO_SUBTRACT_HPP
