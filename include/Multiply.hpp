//
// Created by Myles Inglis on 09/06/2016.
//

#ifndef CHIPAUDIO_MULTIPLY_HPP
#define CHIPAUDIO_MULTIPLY_HPP

#include "Module.hpp"

namespace chip
{
    /**
     * This module calculates the result of multiplying the two inputs.
     */
    class Multiply : public Module
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
        Multiply() : Module(INPUTS_TOTAL) {}

        /**
         * Output the value of the two inputs multiplied together.
         * @return The calculated result.
         */
        double output() override
        {
            double value1 = (input(IN1) == nullptr) ? 0 : input(IN1)->output();
            double value2 = (input(IN2) == nullptr) ? 0 : input(IN2)->output();
            return value1 * value2;
        }
    };
}


#endif //CHIPAUDIO_MULTIPLY_HPP
