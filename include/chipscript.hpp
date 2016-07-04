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
    /**
     * Lua script handler.
     */
    struct Script
    {
        Script();

        /**
         * Loads a lua script file.
         * @param filename Name of Lua script file
         * @return Error details if an error occurred
         */
        std::string operator()(std::string filename);

        OOLUA::Script lua;
    };
}

#endif //CHIPAUDIO_SCRIPT_HPP
