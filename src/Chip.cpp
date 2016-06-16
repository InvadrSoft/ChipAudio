//
// Created by Myles Inglis on 15/06/2016.
//

#include "Chip.hpp"

namespace chip
{
    Sample Chip::generateNextSample()
    {
        if(sampleCounter_ >= samplesPerTick_)
        {
            sampleCounter_ = 0;
            for(Channel& channel : channels_)
            {
                channel.processEvents();
            }
        }
        sampleCounter_++;

        Sample output;

        for(Channel& channel : channels_)
        {
            output += channel.generateNextSample();
        }

        return output;
    }
}