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

        double sampleIncrement = (wave.size() / sampleRate) * frequency;
        phase += sampleIncrement;
        if(phase >= wave.size() )
        {
            phase -= wave.size();
        }
        int phaseTrunc = static_cast<int>(phase);

        double nextValue = wave[(phaseTrunc + 1) & (wave.size() - 1)];
        double signal;
        double toNextStep;

        switch(interpolation)
        {
            case NONE:
            default:
                signal = wave[phaseTrunc];
                break;
            case LINEAR:
                toNextStep = phase - phaseTrunc;
                signal = wave[phaseTrunc] + ( (nextValue - wave[phaseTrunc]) * toNextStep);
                break;
            case COSINE:
                toNextStep = (1 - cos( (phase - phaseTrunc) * M_PI) ) / 2;
                signal = wave[phaseTrunc] + ( (nextValue - wave[phaseTrunc]) * toNextStep);
                break;
        }
        return signal * amplitude;
    }
}
