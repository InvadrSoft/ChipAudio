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
    //user needs to specify a lua script to run
    if(argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
    }
    else
    {
        //create the script object
        chip::Script script;

        //run the script specified by the command-line argument
        //and print the return value in case of an error
        std::cout << script(argv[1]) << std::endl;
    }
    return 0;
}