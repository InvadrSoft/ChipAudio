//
// Created by Myles Inglis on 09/06/2016.
//

#ifndef CHIPAUDIO_ADD_HPP
#define CHIPAUDIO_ADD_HPP

#include "Module.hpp"

namespace chip
{
    /**
     * This module calculates the sum of its two inputs.
     */
    class Add : public Module
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
        Add() : Module(INPUTS_TOTAL) {}

        /**
         * Output the sum of the two inputs.
         * @return The calculated sum.
         */
        double output() override
        {
            double value1 = (input(IN1) == nullptr) ? 0 : input(IN1)->output();
            double value2 = (input(IN2) == nullptr) ? 0 : input(IN2)->output();
            return value1 + value2;
        }
    };
}

#endif //CHIPAUDIO_ADD_HPP
