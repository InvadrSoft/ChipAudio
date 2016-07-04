//
// Created by Myles Inglis on 24/06/2016.
//

#ifndef CHIPAUDIO_SCRIPT_HPP
#define CHIPAUDIO_SCRIPT_HPP

#include <oolua/oolua.h>
#include "chipaudio.hpp"
#include "chipmodules.hpp"

namespace chip
{
    struct Script
    {
        Script();
        std::string operator()(std::string filename);
        OOLUA::Script lua;
    };
}

#endif //CHIPAUDIO_SCRIPT_HPP
