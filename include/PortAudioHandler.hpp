//
// Created by Myles Inglis on 10/12/2015.
//

#ifndef CHIPAUDIO_PORTAUDIOHANDLER_HPP
#define CHIPAUDIO_PORTAUDIOHANDLER_HPP

#include <stdexcept>
#include <functional>
#include "portaudio.h"
#include "Sample.hpp"

namespace chip
{
    constexpr int SAMPLE_RATE = 44100;

    class PAException : public std::runtime_error
    {
    public:
        PAException() : std::runtime_error("PortAudio failed.")
        { }
    };

    class PortAudioHandler
    {
    public:
        PortAudioHandler();

        ~PortAudioHandler();

        void start(std::function<Sample()> _nextSampleFunction);

        void stop();

    private:
        static int paCallback(const void *inputBuffer, void *outputBuffer,
                              unsigned long framesPerBuffer,
                              const PaStreamCallbackTimeInfo *timeInfo,
                              PaStreamCallbackFlags statusFlags,
                              void *userData);

        int paCallbackMethod(const void *inputBuffer, void *outputBuffer,
                             unsigned long framesPerBuffer);

        PaStream *stream;
        std::function<Sample()> nextSampleFunction;
    };

}


#endif //CHIPAUDIO_PORTAUDIOHANDLER_HPP
