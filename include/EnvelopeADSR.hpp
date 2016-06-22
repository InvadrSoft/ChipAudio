//
// Created by Myles Inglis on 10/06/2016.
//

#ifndef CHIPAUDIO_ENVELOPEADSR_HPP
#define CHIPAUDIO_ENVELOPEADSR_HPP

#include "Module.hpp"

namespace chip
{
    /**
     * ADSR envelope generator module.
     */
    class EnvelopeADSR : public Module
    {
    public:
        /**
         * Enumeration of all inputs to this module.
         */
        enum Inputs
        {
            GATE,
            ATTACK,
            DECAY,
            SUSTAIN,
            RELEASE,
            RESTART,
            INPUTS_TOTAL
        };

        /**
         * Enumeration of all envelope phases.
         */
        enum class Phase
        {
            IDLE,
            ATTACK,
            DECAY,
            SUSTAIN,
            RELEASE
        };

        /**
         * Default constructor.
         */
        EnvelopeADSR()
                : Module(INPUTS_TOTAL), lastGateValue_(0.0), currentPhase_(Phase::IDLE),
                  currentIncrement_(0.0), lastSignalValue_(0.0) {}

        /**
         * Generates and outputs the next sample.
         * @return The generated value
         */
        double output() override;

    private:
        double lastGateValue_;
        double lastSignalValue_;
        double currentIncrement_;
        Phase currentPhase_;

    };
}

#endif //CHIPAUDIO_ENVELOPEADSR_HPP
