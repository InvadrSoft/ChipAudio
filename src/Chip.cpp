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
                if(channel.enabled() )
                {
                    channel.processEvents();
                }
            }
            chip::TimeValue currentMasterTime = masterTime_;
            masterTime_ = ++currentMasterTime;
        }
        sampleCounter_++;

        Sample output;

        bool highLoad = portAudioHandler_.highLoad();

        for(Channel& channel : channels_)
        {
            if(highLoad && channel.enabled() && channel.autoDisable() )
            {
                channel.enabled(false);
                highLoad = false;
            }
            else if(channel.enabled() )
            {
                output += channel.generateNextSample();
            }
        }

        for(StereoEffectChannel& sendChannel : sendChannels_)
        {
            output += sendChannel.process();
        }

        return masterEffects_.process(output) * masterVolume_;
    }
}