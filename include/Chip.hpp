//
// Created by Myles Inglis on 15/06/2016.
//

#ifndef CHIPAUDIO_CHIP_HPP
#define CHIPAUDIO_CHIP_HPP

#include <atomic>
#include "Channel.hpp"
#include "PortAudioHandler.hpp"
#include "StereoEffectChannel.hpp"

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
        Chip(double initTempo = 120) : sampleCounter_(0), masterVolume_(1), masterTime_(chip::TimeValue() )
        {
            tempo(initTempo);
        }

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
         * @return A reference to the added channel
         */
        Channel& addChannel()
        {
            channels_.push_back(Channel() );
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

        const double tempo() const { return tempo_; }

        /**
         * Set a new sample rate.
         * @param sampleRate New sample rate
         */
        void sampleRate(double sampleRate)
        {
            Module::sampleRate(sampleRate);
            calculateSamplesPerTick();
        }

        const TimeValue masterTime() const { return masterTime_; }

        void masterVolume(double volume) { masterVolume_ = volume; }

        StereoEffectChannel& masterEffects() { return masterEffects_; }

        StereoEffectChannel& addSendChannel()
        {
            sendChannels_.emplace_back(StereoEffectChannel() );
            return sendChannels_.back();
        }

        double samplesPerTick() { return samplesPerTick_; }

    private:
        Sample generateNextSample();

        void calculateSamplesPerTick()
        {
            samplesPerTick_ = Module::sampleRate() /  ( (tempo_ / 60) * (TICKS_PER_WHOLE_NOTE / 4.0) );
        }

        std::deque<Channel> channels_;
        std::deque<StereoEffectChannel> sendChannels_;

        StereoEffectChannel masterEffects_;

        double masterVolume_;
        double tempo_;
        double samplesPerTick_;
        int sampleCounter_;
        std::atomic<TimeValue> masterTime_;

        PortAudioHandler portAudioHandler_;
    };
}

#endif //CHIPAUDIO_CHIP_HPP
