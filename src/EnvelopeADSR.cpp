//
// Created by Myles Inglis on 10/06/2016.
//

#include "EnvelopeADSR.hpp"

namespace chip
{
    double EnvelopeADSR::output()
    {
        double gate = (input(GATE) == nullptr) ? 0 : input(GATE)->output();
        double sustain = (input(SUSTAIN) == nullptr) ? 0 : input(SUSTAIN)->output();

        if( (gate > 0 && lastGateValue_ == 0 ) ||
            (input(RESTART) != nullptr && input(RESTART)->output() > 0) ) //rising edge
        {
            lastSignalValue_ = 0;
            double attack = (input(ATTACK) == nullptr) ? 0 : input(ATTACK)->output() * sampleRate();
            if(attack < gate)
            {
                attack = gate;
            }
            currentPhase_ = Phase::ATTACK;
            currentIncrement_ = gate / attack;
        }
        else if(gate == 0 && lastGateValue_ > 0) //falling edge
        {
            double release = (input(RELEASE) == nullptr) ? 0 : input(RELEASE)->output() * sampleRate();
            if(release < sustain)
            {
                release = sustain;
            }
            currentPhase_ = Phase::RELEASE;
            currentIncrement_ = -(sustain / release);
        }
        lastGateValue_ = gate;

        double signal = lastSignalValue_ + currentIncrement_;

        switch(currentPhase_)
        {
            case Phase::ATTACK:
            {
                if(signal >= gate)
                {
                    double difference = signal - sustain;
                    double decay = (input(DECAY) == nullptr) ? 0 : input(DECAY)->output() * sampleRate();
                    if(decay < difference)
                    {
                        decay = difference;
                    }
                    currentPhase_ = Phase::DECAY;
                    currentIncrement_ = -(difference / decay);
                }
                break;
            }
            case Phase::DECAY:
            {
                if(signal <= sustain)
                {
                    currentPhase_ = Phase::SUSTAIN;
                    currentIncrement_ = 0.0;
                }
                break;
            }
            case Phase::SUSTAIN:
            case Phase::IDLE:
            {
                break;
            }
            case Phase::RELEASE:
            {
                if(signal <= 0)
                {
                    signal = 0;
                    currentPhase_ = Phase::IDLE;
                    currentIncrement_ = 0.0;
                }
            }
        }

        return lastSignalValue_ = signal;
    }
}