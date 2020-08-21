//
// Created by Myles Inglis on 08/06/2016.
//

#ifndef CHIPAUDIO_VALUE_HPP
#define CHIPAUDIO_VALUE_HPP

#include "Module.hpp"
#include "MoveableAtomic.hpp"

namespace chip
{
    /**
     * Simple module that just stores a value and outputs it
     * when requested. No inputs.
     */
    class Value : public Module
    {
    public:

        /**
         * Enumeration of all inputs to this module.
         */
        enum Inputs
        {
            INPUTS_TOTAL
        };

        /**
         * Constructs a Value, default value is 0.
         * @param value Initial value (optional)
         */
        Value(double value = 0) : Module(INPUTS_TOTAL), value_(value) {}

        /**
         * Copy assignment operator
         * @param pattern Value to copy value from
         * @return Reference to this Value
         */
        Value& operator=(Value &pattern)
        {
            value_ = pattern.value_;
            return *this;
        }

        /**
         * Assign a new value to this Value
         * @param newValue New value to be assigned
         * @return Reference to this Value
         */
        Value& operator=(double newValue)
        {
            value_ = newValue;
            return *this;
        }

        Value& operator+=(double rhs)
        {
            value_ = value_ + rhs;
            return *this;
        }

        /**
         * Output the stored value.
         * @return The stored value
         */
        double output() override { return value_; }

    private:
        MoveableAtomic<double> value_;
    };
}

#endif //CHIPAUDIO_VALUE_HPP
