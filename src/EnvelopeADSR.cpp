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

        if(gate > 0 && lastGateValue == 0) //rising edge
        {
            double attack = (input(ATTACK) == nullptr) ? 0 : input(ATTACK)->output() * sampleRate();
            if(attack < gate)
            {
                attack = gate;
            }
            currentPhase = Phase::ATTACK;
            currentIncrement = gate / attack;
        }
        else if(gate == 0 && lastGateValue > 0) //falling edge
        {
            double release = (input(RELEASE) == nullptr) ? 0 : input(RELEASE)->output() * sampleRate();
            if(release < sustain)
            {
                release = sustain;
            }
            currentPhase = Phase::RELEASE;
            currentIncrement = -(sustain / release);
        }
        lastGateValue = gate;

        double signal = lastSignalValue + currentIncrement;

        switch(currentPhase)
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
                    currentPhase = Phase::DECAY;
                    currentIncrement = -(difference / decay);
                }
                break;
            }
            case Phase::DECAY:
            {
                if(signal <= sustain)
                {
                    currentPhase = Phase::SUSTAIN;
                    currentIncrement = 0.0;
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
                    currentPhase = Phase::IDLE;
                    currentIncrement = 0.0;
                }
            }
        }

        return lastSignalValue = signal;
    }
}