include_directories(
        ${PROJECT_SOURCE_DIR}/include
)

add_library(chipaudio ../include/chipaudio.hpp PortAudioHandler.cpp ../include/PortAudioHandler.hpp ../include/Sample.hpp ../include/Event.hpp ../include/TimeSignature.hpp ../include/Module.hpp ../include/Value.hpp ../include/Invert.hpp ../include/Add.hpp ../include/Subtract.hpp ../include/Multiply.hpp ../include/Oscillator.hpp ../include/WaveTable.hpp Oscillator.cpp ../include/FilterLP1Pole.hpp Module.cpp ../include/EnvelopeADSR.hpp EnvelopeADSR.cpp ../include/Notes.hpp ../include/NoteToFrequency.hpp ../include/TimeValue.hpp TimeValue.cpp ../include/Pattern.hpp Pattern.cpp ../include/Channel.hpp Channel.cpp ../include/Chip.hpp Chip.cpp ../include/chipmodules.hpp)