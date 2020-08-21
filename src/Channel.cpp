//
// Created by Myles Inglis on 14/06/2016.
//

#include "Channel.hpp"

namespace chip
{
    Sample Channel::generateNextSample()
    {
        static constexpr auto SILENCE_THRESHOLD = 0.000001;
        static constexpr auto MAX_SILENT_SAMPLES = 1024;

        double output = moduleChain_.output() * volume_;
        moduleChain_.input(ModuleChain::NEW_NOTE) = 0;

        if(autoDisable_)
        {
            if(output <= SILENCE_THRESHOLD && output >= -SILENCE_THRESHOLD)
            {
                if(++silentSamples_ >= MAX_SILENT_SAMPLES)
                {
                    enabled_ = false;
                    silentSamples_ = 0;
                }
            }
        }

        for(auto& send : sends_)
        {
            send.channel->input(StereoEffectChannel::LEFT_CHANNEL) += output * send.amount;
            send.channel->input(StereoEffectChannel::RIGHT_CHANNEL) += output * send.amount;
        }

        if(pan_ <= 0)
        {
            return Sample(output * (pan_ + 1), output);
        }
        else
        {
            return Sample(output, output * (-pan_ + 1) );
        }
    }

    void Channel::processEvents()
    {
        Pattern newPattern;
        while(patternQueue_.pop_front(newPattern) )
        {
            addPattern(newPattern);
        }

        if(currentPattern_ < patterns_.size() )
        {
            Pattern &currentPattern = patterns_[currentPattern_];
            auto events = currentPattern.getEvents();
            for(auto &event : events)
            {
                switch(event.type)
                {
                    case NOTE_ON:
                        moduleChain_.input(ModuleChain::NOTE_NUMBER) = event.note;
                        moduleChain_.input(ModuleChain::NOTE_FREQ) = FREQ_TABLE[event.note];
                        moduleChain_.input(ModuleChain::GATE_IN) = event.value;
                        moduleChain_.input(ModuleChain::NEW_NOTE) = 1;
                        break;
                    case NOTE_OFF:
                        moduleChain_.input(ModuleChain::GATE_IN) = 0;
                        break;
                    case PARAM_CHANGE:
                        moduleChain_.setParameter(event.paramID, event.value);
                        break;
                }
            }
            currentPattern.nextTick();
            if(currentPattern.finished() )
            {
                if(consumePatterns_)
                {
                    removePattern(currentPattern_);
                }
                else
                {
                    currentPattern.restart();
                    currentPattern_++;
                }
                if(currentPattern_ >= patterns_.size())
                {
                    if(loop_)
                    {
                        currentPattern_ = loopStart_;
                    }
                }
            }
        }
    }
}
