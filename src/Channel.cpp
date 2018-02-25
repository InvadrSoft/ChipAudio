//
// Created by Myles Inglis on 14/06/2016.
//

#include "Channel.hpp"

namespace chip
{
    Sample Channel::generateNextSample()
    {
        double output = moduleChain_.output() * volume_;
        moduleChain_.input(ModuleChain::NEW_NOTE) = 0;
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
