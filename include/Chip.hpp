//
// Created by Myles Inglis on 15/06/2016.
//

#ifndef CHIPAUDIO_CHIP_HPP
#define CHIPAUDIO_CHIP_HPP

#include <future>
#include "Channel.hpp"

namespace chip
{
    class Chip
    {
    public:
        Sample generateNextSample();

    private:
        std::vector<Channel> channels_;
        double tempo_;
    };
}

#endif //CHIPAUDIO_CHIP_HPP
