//
// Created by Myles Inglis on 25/06/2016.
//

#include <iostream>
#include "chipscript.hpp"

using namespace chip;

OOLUA_PROXY(Notes)
    OOLUA_TAGS(Register_class_enums)
    OOLUA_ENUMS(
        OOLUA_ENUM(C0) OOLUA_ENUM(Db0) OOLUA_ENUM(D0) OOLUA_ENUM(Eb0) OOLUA_ENUM(E0) OOLUA_ENUM(F0) OOLUA_ENUM(Gb0) OOLUA_ENUM(G0) OOLUA_ENUM(Ab0) OOLUA_ENUM(A0) OOLUA_ENUM(Bb0) OOLUA_ENUM(B0)
        OOLUA_ENUM(C1) OOLUA_ENUM(Db1) OOLUA_ENUM(D1) OOLUA_ENUM(Eb1) OOLUA_ENUM(E1) OOLUA_ENUM(F1) OOLUA_ENUM(Gb1) OOLUA_ENUM(G1) OOLUA_ENUM(Ab1) OOLUA_ENUM(A1) OOLUA_ENUM(Bb1) OOLUA_ENUM(B1)
        OOLUA_ENUM(C2) OOLUA_ENUM(Db2) OOLUA_ENUM(D2) OOLUA_ENUM(Eb2) OOLUA_ENUM(E2) OOLUA_ENUM(F2) OOLUA_ENUM(Gb2) OOLUA_ENUM(G2) OOLUA_ENUM(Ab2) OOLUA_ENUM(A2) OOLUA_ENUM(Bb2) OOLUA_ENUM(B2)
        OOLUA_ENUM(C3) OOLUA_ENUM(Db3) OOLUA_ENUM(D3) OOLUA_ENUM(Eb3) OOLUA_ENUM(E3) OOLUA_ENUM(F3) OOLUA_ENUM(Gb3) OOLUA_ENUM(G3) OOLUA_ENUM(Ab3) OOLUA_ENUM(A3) OOLUA_ENUM(Bb3) OOLUA_ENUM(B3)
        OOLUA_ENUM(C4) OOLUA_ENUM(Db4) OOLUA_ENUM(D4) OOLUA_ENUM(Eb4) OOLUA_ENUM(E4) OOLUA_ENUM(F4) OOLUA_ENUM(Gb4) OOLUA_ENUM(G4) OOLUA_ENUM(Ab4) OOLUA_ENUM(A4) OOLUA_ENUM(Bb4) OOLUA_ENUM(B4)
        OOLUA_ENUM(C5) OOLUA_ENUM(Db5) OOLUA_ENUM(D5) OOLUA_ENUM(Eb5) OOLUA_ENUM(E5) OOLUA_ENUM(F5) OOLUA_ENUM(Gb5) OOLUA_ENUM(G5) OOLUA_ENUM(Ab5) OOLUA_ENUM(A5) OOLUA_ENUM(Bb5) OOLUA_ENUM(B5)
        OOLUA_ENUM(C6) OOLUA_ENUM(Db6) OOLUA_ENUM(D6) OOLUA_ENUM(Eb6) OOLUA_ENUM(E6) OOLUA_ENUM(F6) OOLUA_ENUM(Gb6) OOLUA_ENUM(G6) OOLUA_ENUM(Ab6) OOLUA_ENUM(A6) OOLUA_ENUM(Bb6) OOLUA_ENUM(B6)
        OOLUA_ENUM(C7) OOLUA_ENUM(Db7) OOLUA_ENUM(D7) OOLUA_ENUM(Eb7) OOLUA_ENUM(E7) OOLUA_ENUM(F7) OOLUA_ENUM(Gb7) OOLUA_ENUM(G7) OOLUA_ENUM(Ab7) OOLUA_ENUM(A7) OOLUA_ENUM(Bb7) OOLUA_ENUM(B7)
        OOLUA_ENUM(C8) OOLUA_ENUM(Db8) OOLUA_ENUM(D8) OOLUA_ENUM(Eb8) OOLUA_ENUM(E8) OOLUA_ENUM(F8) OOLUA_ENUM(Gb8) OOLUA_ENUM(G8) OOLUA_ENUM(Ab8) OOLUA_ENUM(A8) OOLUA_ENUM(Bb8) OOLUA_ENUM(B8)
    )
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(Notes)
OOLUA_EXPORT_FUNCTIONS_CONST(Notes)

OOLUA_PROXY(EventType)
    OOLUA_TAGS(Register_class_enums)
    OOLUA_ENUMS(
        OOLUA_ENUM(NOTE_ON)
        OOLUA_ENUM(NOTE_OFF)
        OOLUA_ENUM(PARAM_CHANGE)
    )
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(EventType)
OOLUA_EXPORT_FUNCTIONS_CONST(EventType)

OOLUA_PROXY(Event)
    OOLUA_TAGS(
        No_default_constructor
    )
    OOLUA_CTORS(
        OOLUA_CTOR(int, int, int, std::string)
    )
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(Event)
OOLUA_EXPORT_FUNCTIONS_CONST(Event)

OOLUA_PROXY(TimeValue)
    OOLUA_TAGS(
        No_default_constructor,
        Add_op
    )
    OOLUA_CTORS(
        OOLUA_CTOR(unsigned int, unsigned int, unsigned int, unsigned int)
    )
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(TimeValue)
OOLUA_EXPORT_FUNCTIONS_CONST(TimeValue)

OOLUA_PROXY(Pattern)
    OOLUA_MFUNC(addEvent)
    OOLUA_MFUNC(restart)
    OOLUA_MEM_FUNC(void, endPosition, TimeValue)
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(Pattern, addEvent, restart, endPosition)
OOLUA_EXPORT_FUNCTIONS_CONST(Pattern)

OOLUA_PROXY(Module)
    OOLUA_TAGS(Abstract)
    OOLUA_MFUNC(output)
    OOLUA_MFUNC(input)
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(Module, output, input)
OOLUA_EXPORT_FUNCTIONS_CONST(Module)

OOLUA_PROXY(Value, Module)
    OOLUA_CTORS(OOLUA_CTOR(double) )
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(Value)
OOLUA_EXPORT_FUNCTIONS_CONST(Value)

OOLUA_PROXY(WaveTable)
    OOLUA_TAGS(
        No_default_constructor,
        Register_class_enums
    )
    OOLUA_ENUMS(
        OOLUA_ENUM(SIZE_2)
        OOLUA_ENUM(SIZE_4)
        OOLUA_ENUM(SIZE_8)
        OOLUA_ENUM(SIZE_16)
        OOLUA_ENUM(SIZE_32)
        OOLUA_ENUM(SIZE_64)
        OOLUA_ENUM(SIZE_128)
        OOLUA_ENUM(SIZE_256)
        OOLUA_ENUM(SIZE_512)
        OOLUA_ENUM(SIZE_1024)
    )
    OOLUA_CTORS(OOLUA_CTOR(WaveTable::TableSize))
    OOLUA_MFUNC(set)
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(WaveTable, set)
OOLUA_EXPORT_FUNCTIONS_CONST(WaveTable)

OOLUA_PROXY(Oscillator, Module)
    OOLUA_TAGS(Register_class_enums)
    OOLUA_ENUMS(
        OOLUA_ENUM(FREQUENCY)
        OOLUA_ENUM(AMPLITUDE)
        OOLUA_ENUM(NONE)
        OOLUA_ENUM(LINEAR)
        OOLUA_ENUM(COSINE)
    )
    OOLUA_CTORS(OOLUA_CTOR(WaveTable, Oscillator::InterpolationType) )
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(Oscillator)
OOLUA_EXPORT_FUNCTIONS_CONST(Oscillator)

OOLUA_PROXY(EnvelopeADSR, Module)
    OOLUA_TAGS(Register_class_enums)
    OOLUA_ENUMS(
        OOLUA_ENUM(GATE)
        OOLUA_ENUM(ATTACK)
        OOLUA_ENUM(DECAY)
        OOLUA_ENUM(SUSTAIN)
        OOLUA_ENUM(RELEASE)
        OOLUA_ENUM(RESTART)
    )
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(EnvelopeADSR)
OOLUA_EXPORT_FUNCTIONS_CONST(EnvelopeADSR)

OOLUA_PROXY(Channel)
    OOLUA_TAGS(Register_class_enums)
    OOLUA_ENUMS(
        OOLUA_ENUM(NOTE_FREQ)
        OOLUA_ENUM(NOTE_NUMBER)
        OOLUA_ENUM(GATE_IN)
        OOLUA_ENUM(NEW_NOTE)
    )
    OOLUA_MEM_FUNC(Pattern &, addPattern, Pattern)
    OOLUA_MEM_FUNC_RENAME(addPatternAt, Pattern &, addPattern, Pattern, int)
    OOLUA_MFUNC(removeFirstPattern)
    OOLUA_MFUNC(removePattern)
    OOLUA_MFUNC(addModule)
    OOLUA_MFUNC(addParameter)
    OOLUA_MFUNC(addOscillator)
    OOLUA_MFUNC(input)
    OOLUA_MFUNC(output)
    OOLUA_MFUNC(restart)
    OOLUA_MEM_FUNC_CONST(const double&, volume)
    OOLUA_MEM_FUNC_RENAME(setVolume, void, volume, double)
    OOLUA_MEM_FUNC_CONST(const double&, pan)
    OOLUA_MEM_FUNC_RENAME(setPan, void, pan, double)
    OOLUA_MEM_FUNC_CONST(const unsigned int&, currentPattern)
    OOLUA_MEM_FUNC_RENAME(setCurrentPattern, void, currentPattern, unsigned int)
    OOLUA_MEM_FUNC_CONST(const bool&, loop)
    OOLUA_MEM_FUNC_RENAME(setLoop, void, loop, bool)
    OOLUA_MEM_FUNC_CONST(const unsigned int&, loopStart)
    OOLUA_MEM_FUNC_RENAME(setLoopStart, void, loopStart, unsigned int)
    OOLUA_MFUNC(noPatterns)
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(Channel, addPattern, addPatternAt, removeFirstPattern, removePattern, addModule,
                       addParameter, addOscillator, input, output, restart, setVolume, setPan, setCurrentPattern,
                       setLoop, setLoopStart)
OOLUA_EXPORT_FUNCTIONS_CONST(Channel, volume, pan, currentPattern, loop, loopStart)

OOLUA_PROXY(Chip)
    OOLUA_MFUNC(start)
    OOLUA_MFUNC(pause)
    OOLUA_MFUNC(stop)
    OOLUA_MFUNC(addChannel)
    OOLUA_MFUNC(channel)
    OOLUA_MFUNC(tempo)
    OOLUA_MFUNC(sampleRate)
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(Chip, start, pause, stop, addChannel, channel, tempo, sampleRate)
OOLUA_EXPORT_FUNCTIONS_CONST(Chip)

namespace chip
{
    Oscillator* newOscillator(WaveTable wave, Oscillator::InterpolationType interp)
    {
        return new Oscillator(wave, interp);
    }

    Value* newValue(double value)
    {
        return new Value(value);
    }

    EnvelopeADSR* newEnvelope()
    {
        return new EnvelopeADSR();
    }

    void moduleInput(Module& module, unsigned int input, Module& inputModule)
    {
        module.input(input) = &inputModule;
    }

    OOLUA_CFUNC(newOscillator, l_newOscillator)
    OOLUA_CFUNC(newValue, l_newValue)
    OOLUA_CFUNC(newEnvelope, l_newEnvelope)

    OOLUA_CFUNC(moduleInput, l_moduleInput)
    
    Script::Script()
    {
        lua.register_class<Notes>();
        lua.register_class<EventType>();
        lua.register_class<Event>();
        lua.register_class<TimeValue>();
        lua.register_class<Pattern>();
        lua.register_class<Module>();
        lua.register_class<Value>();
        lua.register_class<WaveTable>();
        lua.register_class<Oscillator>();
        lua.register_class<EnvelopeADSR>();
        lua.register_class<Channel>();
        lua.register_class<Chip>();

        set_global(lua, "moduleInput", l_moduleInput);

        set_global(lua, "newValue", l_newValue);
        set_global(lua, "newEnvelope", l_newEnvelope);
        set_global(lua, "newOscillator", l_newOscillator);
    }

    std::string Script::operator()(std::string filename)
    {
        lua.run_file(filename);
        return OOLUA::get_last_error(lua);
    }
}