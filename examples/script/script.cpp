/*! \file
 *  \brief Script example
 *
 *  Example program that runs a lua script (specified by command-line argument).
 *
 *  \include script.cpp
 */

#include <iostream>
#include "chipaudio.hpp"
#include "chipmodules.hpp"
#include "chipscript.hpp"

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
    }
    else
    {
        chip::Script script;
        std::cout << script(argv[1]) << std::endl;
    }
    return 0;
}