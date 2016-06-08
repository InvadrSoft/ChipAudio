//
// Created by Myles Inglis on 08/06/2016.
//

#ifndef CHIPAUDIO_MODULE_HPP
#define CHIPAUDIO_MODULE_HPP

#include <vector>

/**
 * Abstract base class for modules.
 */
class Module
{
public:
    /**
     * Override this method to define the behaviour of the module.
     * @return Current output value of the module
     */
    virtual double output() = 0;

private:
    std::vector<Module*> inputs;
};

#endif //CHIPAUDIO_MODULE_HPP
