//
// Created by Myles Inglis on 14/06/2016.
//

#include "Channel.hpp"

namespace chip
{
    void Channel::processEvents()
    {
        if(currentPattern_ < patterns_.size() )
        {
            Pattern &currentPattern = patterns_[currentPattern_];
            auto events = currentPattern.getEvents();
            for(auto &event : events)
            {
                switch(event.type)
                {
                    case NOTE_ON:
                        inputs_[NOTE_NUMBER] = event.note;
                        inputs_[NOTE_FREQ] = FREQ_TABLE[event.note];
                        inputs_[GATE_IN] = event.value;
                        break;
                    case NOTE_OFF:
                        inputs_[GATE_IN] = 0;
                        break;
                    case PARAM_CHANGE:
                        parameters_[event.paramID] = event.value;
                        break;
                }
            }
            currentPattern.nextTick();
            if(currentPattern.finished() )
            {
                currentPattern.restart();
                currentPattern_++;
                if(currentPattern_ >= patterns_.size())
                {
                    if(loop_)
                    {
                        currentPattern_ = 0;
                    }
                }
            }
        }
    }
}
