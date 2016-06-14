//
// Created by Myles Inglis on 08/06/2016.
//

#ifndef CHIPAUDIO_MODULE_HPP
#define CHIPAUDIO_MODULE_HPP

#include <vector>

namespace chip
{
    /**
     * Abstract base class for modules.
     */
    class Module
    {
    public:
        /**
         * Construct module with specified number of inputs.
         * @param _inputs No. of inputs
         */
        Module(unsigned int _inputs) : inputs_(_inputs, nullptr) {}

        /**
         * Override this method to define the behaviour of the module.
         * @return Current output value of the module
         */
        virtual double output() = 0;

        /**
         * Get input at given index (no bounds checking).
         * @param _input Index of input
         * @return Pointer to module at given index
         */
        Module*& input(unsigned int _input) { return inputs_[_input]; }

        /**
         * @return Current sample rate
         */
        static double sampleRate() { return sampleRate_; }

        /**
         * @param sampleRate New sample rate
         */
        static void sampleRate(double sampleRate) { sampleRate_ = sampleRate; }

        virtual ~Module() {}

    private:
        static double sampleRate_;
        std::vector<Module*> inputs_;
    };
}

#endif //CHIPAUDIO_MODULE_HPP
