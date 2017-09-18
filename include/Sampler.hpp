//
// Created by Myles Inglis on 30/07/2017.
//

#ifndef CHIPAUDIO_SAMPLER_HPP
#define CHIPAUDIO_SAMPLER_HPP

#include "Module.hpp"

namespace chip
{
    class Sampler : public Module
    {
    public:
        /**
         * Enumeration of all inputs to this module.
         */
        enum Inputs
        {
            TRIGGER,
            INPUTS_TOTAL
        };

        Sampler(const double* samples = nullptr, size_t sampleCount = 0)
                : Module(INPUTS_TOTAL), samples_(samples), sampleCount_(sampleCount), currentSample_(sampleCount) {}

        double output() override
        {
            double trigger = (input(TRIGGER) == nullptr) ? 0 : input(TRIGGER)->output();
            if(trigger > 0)
            {
                currentSample_ = 0;
            }
            double output = 0;
            if(currentSample_ < sampleCount_)
            {
                output = samples_[currentSample_];
                currentSample_++;
            }
            return output;
        }

    private:
        const double* samples_;
        size_t sampleCount_;
        size_t currentSample_;
    };
}

#endif //CHIPAUDIO_SAMPLER_HPP
