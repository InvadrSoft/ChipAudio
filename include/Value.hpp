//
// Created by Myles Inglis on 08/06/2016.
//

#ifndef CHIPAUDIO_VALUE_HPP
#define CHIPAUDIO_VALUE_HPP

#include "Module.hpp"

/**
 * Simple module that just stores a value and outputs it
 * when requested.
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
     * @param _value Initial value (optional)
     */
    Value(double _value = 0) : Module(), value(_value) {}

    /**
     * Copy assignment operator
     * @param pattern Value to copy value from
     * @return Reference to this Value
     */
    Value& operator=(Value& pattern)
    {
        value = pattern.value;
        return *this;
    }

    /**
     * Assign a new value to this Value
     * @param newValue New value to be assigned
     * @return Reference to this Value
     */
    Value& operator=(double newValue)
    {
        value = newValue;
        return *this;
    }

    /**
     * Output the stored value.
     * @return The stored value
     */
    double output() override { return value; }

private:
    double value;
};

#endif //CHIPAUDIO_VALUE_HPP
