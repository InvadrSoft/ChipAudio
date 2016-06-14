//
// Created by Myles Inglis on 14/06/2016.
//

#include "Pattern.hpp"

namespace chip
{
    std::vector<Event> Pattern::getEvents()
    {
        std::vector<Event> result;
        auto range = events_.equal_range(currentPosition_);
        for(auto itr = range.first; itr != range.second; ++itr)
        {
            result.push_back(itr->second);
        }
        return result;
    }

    void Pattern::addEvent(Event event, TimeValue timeValue)
    {
        timeValue.timeSignature(timeSignature_);
        events_.emplace(timeValue, std::move(event));
    }
}