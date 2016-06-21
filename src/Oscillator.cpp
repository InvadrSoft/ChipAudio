//
// Created by Myles Inglis on 09/06/2016.
//

#include <cmath>
#include "Oscillator.hpp"

namespace chip
{
    double Oscillator::output()
    {
        double frequency = (input(FREQUENCY) == nullptr) ? 0 : input(FREQUENCY)->output();
        double amplitude = (input(AMPLITUDE) == nullptr) ? 0 : input(AMPLITUDE)->output();

        double sampleIncrement = (wave_.size() / sampleRate() ) * fabs(frequency);
        phase_ += sampleIncrement;
        if(phase_ >= wave_.size() )
        {
            phase_ -= wave_.size();
        }
        int phaseTrunc = static_cast<int>(phase_);

        double nextValue = wave_[(phaseTrunc + 1) & (wave_.size() - 1)];
        double signal;
        double toNextStep;

        switch(interpolation_)
        {
            case NONE:
            default:
                signal = wave_[phaseTrunc];
                break;
            case LINEAR:
                toNextStep = phase_ - phaseTrunc;
                signal = wave_[phaseTrunc] + ( (nextValue - wave_[phaseTrunc]) * toNextStep);
                break;
            case COSINE:
                toNextStep = (1 - cos( (phase_ - phaseTrunc) * M_PI) ) / 2;
                signal = wave_[phaseTrunc] + ( (nextValue - wave_[phaseTrunc]) * toNextStep);
                break;
        }
        return signal * amplitude;
    }
}
