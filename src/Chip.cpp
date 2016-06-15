//
// Created by Myles Inglis on 15/06/2016.
//

#include "Chip.hpp"

namespace chip
{
    Sample Chip::generateNextSample()
    {
        std::vector<std::future<Sample> > channelResults;

        for(Channel& channel : channels_)
        {
            channelResults.push_back(std::async(channel.generateNextSample() ) );
        }

        Sample output;

        for(auto& result : channelResults)
        {
            output += result.get();
        }

        return output;
    }
}