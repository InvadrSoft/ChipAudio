# ChipAudio

ChipAudio C++ Music Synthesis Library

# Introduction

The ChipAudio library provides a means for implementing synthesised music and sound in real-time, interactive applications.

See the example programs to get an idea of how the library works.

Currently tested and working on Mac OS X.

# Headers

The [chipaudio.hpp](include/chipaudio.hpp) header includes all the essential components of the library, and the 
[chipmodules.hpp](include/chipmodules.hpp) header includes all the standard Modules. 
Most projects using the library should include both of these headers. Projects requiring the Lua script support should also include 
[chipscript.hpp](include/chipscript.hpp).

# Dependencies

ChipAudio requires the PortAudio (http://www.portaudio.com/) library. In order to use the Lua script functionality, OOLua (https://oolua.org/) is
also required as well as a suitable version of Lua (Lua, LuaJIT etc.).
