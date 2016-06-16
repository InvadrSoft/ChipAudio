//
// Created by Myles Inglis on 15/06/2016.
//

#ifndef CHIPAUDIO_CHIP_HPP
#define CHIPAUDIO_CHIP_HPP

#include <atomic>
#include <thread>
#include "Channel.hpp"
#include "PortAudioHandler.hpp"

namespace chip
{
    /**
     * Class representing a virtual sound chip, made up of a variable number of Channels.
     */
    class Chip
    {
    public:
        /**
         * Constructs a chip with option to specify initial tempo.
         * @param initTempo Initial tempo (optional, default = 120)
         */
        Chip(double initTempo = 120) : sampleCounter_(0)
        {
            tempo(initTempo);
        }

        /**
         * Generate the next sample by summing the output of all channels.
         * @return The generated sample
         */
        Sample generateNextSample();

        /**
         * Start/resume playback.
         */
        void start() { portAudioHandler_.start(std::bind(&Chip::generateNextSample, this) ); }

        /**
         * Pause playback, preserving current playback position.
         */
        void pause() { portAudioHandler_.stop(); }

        /**
         * Stop playback, restarting playback position.
         */
        void stop()
        {
            portAudioHandler_.stop();
            for(Channel& channel : channels_)
            {
                channel.restart();
            }
        }

        /**
         * Add a channel to the chip.
         * @param channel Channel to add
         * @return A reference to the added channel
         */
        Channel& addChannel(Channel channel)
        {
            channels_.push_back(std::move(channel) );
            return channels_.back();
        }

        /**
         * Access a channel by index.
         * @param index Index of channel
         * @return Reference to the indexed channel
         */
        Channel& channel(unsigned int index) { return channels_[index]; }

        /**
         * Set a new tempo
         * @param tempo New tempo
         */
        void tempo(double tempo)
        {
            tempo_ = tempo;
            calculateSamplesPerTick();
        }

        /**
         * Set a new sample rate.
         * @param sampleRate New sample rate
         */
        void sampleRate(double sampleRate)
        {
            Module::sampleRate(sampleRate);
            calculateSamplesPerTick();
        }

    private:
        void calculateSamplesPerTick()
        {
            samplesPerTick_ = Module::sampleRate() /  ( (tempo_ / 60) * (TICKS_PER_WHOLE_NOTE / 4.0) );
        }

        std::vector<Channel> channels_;

        double tempo_;
        double samplesPerTick_;
        int sampleCounter_;

        PortAudioHandler portAudioHandler_;
    };
}

#endif //CHIPAUDIO_CHIP_HPP
