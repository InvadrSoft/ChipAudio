//
// Created by Myles Inglis on 10/12/2015.
//

#include "PortAudioHandler.hpp"
#include "Module.hpp"

namespace chip
{

    PortAudioHandler::PortAudioHandler() : previousLoad(0)
    {
        PaError err = Pa_Initialize();
        if( err != paNoError )
        {
            throw PAException();
        }
    }

    PortAudioHandler::~PortAudioHandler()
    {
        Pa_Terminate();
    }

    void PortAudioHandler::start(std::function<Sample()> _nextSampleFunction)
    {
        nextSampleFunction = _nextSampleFunction;
        /* Open an audio I/O stream. */
        PaError  err = Pa_OpenDefaultStream(&stream,
                                            0,          /* no input channels */
                                            2,          /* stereo output */
                                            paFloat32,  /* 32 bit floating point output */
                                            Module::sampleRate(),
                                            paFramesPerBufferUnspecified,        /* frames per buffer, i.e. the number
                                                           of sample frames that PortAudio will
                                                           request from the callback. Many apps
                                                           may want to use
                                                           paFramesPerBufferUnspecified, which
                                                           tells PortAudio to pick the best,
                                                           possibly changing, buffer size.*/
                                            &PortAudioHandler::paCallback, /* this is your callback function */
                                            this); /*This is a pointer that will be passed to
                                                                   your callback*/
        if( err != paNoError )
        {
            throw PAException();
        }

        err = Pa_StartStream(stream);

        if( err != paNoError )
        {
            throw PAException();
        }
    }

    void PortAudioHandler::stop()
    {
        PaError err = Pa_StopStream(stream);
        if( err != paNoError )
        {
            throw PAException();
        }
        err = Pa_CloseStream(stream);
        if( err != paNoError )
        {
            throw PAException();
        }
    }

    bool PortAudioHandler::highLoad()
    {
        auto load = Pa_GetStreamCpuLoad(stream);
        if (load == previousLoad) return false;
        previousLoad = load;
        return load > 0.9;
    }

    int PortAudioHandler::paCallbackMethod(const void *inputBuffer, void *outputBuffer,
                                           unsigned long framesPerBuffer)
    {
        float *out = static_cast<float*>(outputBuffer);

        for (int i = 0; i < framesPerBuffer; i++)
        {
            Sample nextSample = nextSampleFunction();
            *out++ = static_cast<float>(nextSample.left);
            *out++ = static_cast<float>(nextSample.right);
        }

        return 0;
    }

    int PortAudioHandler::paCallback(const void *inputBuffer, void *outputBuffer,
                                     unsigned long framesPerBuffer,
                                     const PaStreamCallbackTimeInfo *timeInfo,
                                     PaStreamCallbackFlags statusFlags,
                                     void *userData)
    {
        return ( static_cast<PortAudioHandler*>(userData)->paCallbackMethod(inputBuffer, outputBuffer, framesPerBuffer) );
    }

}