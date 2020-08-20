//
// Created by Myles Inglis on 14/06/2016.
//

#ifndef CHIPAUDIO_CHANNEL_HPP
#define CHIPAUDIO_CHANNEL_HPP

#include <deque>
#include <vector>
#include <map>
#include <memory>
#include <atomic>
#include "ModuleChain.hpp"
#include "Pattern.hpp"
#include "Module.hpp"
#include "Oscillator.hpp"
#include "Value.hpp"
#include "Notes.hpp"
#include "Sample.hpp"
#include "SPSCRingBuffer.hpp"
#include "MoveableAtomic.hpp"

namespace chip
{
    /**
     * A monophonic sound channel.
     */
    class Channel
    {
        friend class Chip;

    public:
        /**
         * Default constructor.
         */
        Channel() : volume_(1), pan_(0), currentPattern_(0), loop_(0), loopStart_(0), consumePatterns_(0),
                    enabled_(true), autoDisable_(false), silentSamples_(0) {}

        Channel(Channel&&) = default;

        /**
         * Add a pattern to the channel's pattern list.
         * @param pattern Pattern to add
         * @return A reference to the added pattern
         */
        Pattern& addPattern(Pattern pattern)
        {
            patterns_.push_back(std::move(pattern) );
            return patterns_.back();
        }

        /**
         * Add a pattern to the pattern list at a given index.
         * @param pattern Pattern to add
         * @param index Index to put pattern
         * @return A reference to the added pattern
         */
        Pattern& addPattern(Pattern pattern, int index)
        {
            if(currentPattern_ > index)
            {
                currentPattern_++;
            }
            return *(patterns_.insert(patterns_.begin() + index, std::move(pattern) ) );
        }

        /**
         * Remove the first pattern in channel's pattern list.
         */
        void removeFirstPattern()
        {
            patterns_.pop_front();
            if(currentPattern_ > 0)
            {
                currentPattern_--;
            }
        }

        /**
         * Remove the pattern at the given index in the pattern list.
         * @param index Index of pattern
         */
        void removePattern(int index)
        {
            patterns_.erase(patterns_.begin() + index);
            if(currentPattern_ > index)
            {
                currentPattern_--;
            }
        }

        /**
         * Add pattern to queue, which will subsequently be added to the channel's
         * pattern list in a thread-safe manner. Not thread-safe if this method is
         * called from more than one thread.
         * @param pattern Pattern to add
         * @return True if successful, false if queue was full
         */
        bool enqueuePattern(Pattern pattern)
        {
            return patternQueue_.push_back(pattern);
        }

        /**
         * Add a module to the channel.
         * @param module Module to add
         * @return A reference to the added module
         */
        Module& addModule(Module* module)
        {
            return moduleChain_.addModule(module);
        }

        /**
         * Add a parameter to the channel.
         * @param parameter Parameter to add
         * @param name Name of parameter
         * @return A reference to the added parameter
         */
        Value& addParameter(Value parameter, std::string name)
        {
            return moduleChain_.addParameter(parameter, name);
        }

        /**
         * Add an oscillator to the channel.
         * @param oscillator Oscillator to add
         * @return A reference to the added oscillator
         */
        Oscillator& addOscillator(Oscillator* oscillator)
        {
            return moduleChain_.addOscillator(oscillator);
        }

        /**
         * Returns the specified input module.
         * @param input Input module index
         * @return A reference to the specified input module
         */
        Value& input(ModuleChain::InputModule input) { return moduleChain_.input(input); }

        /**
         * Sets the output module of the channel.
         * @param module Pointer to module to use as output
         */
        void output(Module* module) { moduleChain_.output(module); }

        /**
         * Reset playback to beginning of pattern list.
         */
        void restart()
        {
            currentPattern_ = 0;
            for(Pattern& pattern : patterns_)
            {
                pattern.restart();
            }
        }

        /**
         * Clear all patterns and modules.
         */
        void clear()
        {
            patterns_.clear();
            currentPattern_ = 0;
            moduleChain_.clear();
        }

        const bool enabled() const { return enabled_; }
        void enabled(bool enabled) { enabled_ = enabled; }

        const bool autoDisable() const { return autoDisable_; }
        void autoDisable(bool autoDisable) { autoDisable_ = autoDisable; }

        const double& volume() const { return volume_; }
        void volume(double volume) { volume_ = volume; }

        const double& pan() const { return pan_; }
        void pan(double pan) { pan_ = pan; }

        const unsigned int& currentPattern() const { return currentPattern_; }
        void currentPattern(unsigned int pattern) { currentPattern_ = pattern; }

        const bool& loop() const { return loop_; }
        void loop(bool loop) { loop_ = loop; }

        const unsigned int& loopStart() const { return loopStart_; }
        void loopStart(unsigned int index) { loopStart_ = index; }

        const bool& consumePatterns() const { return consumePatterns_; }

        /**
         * Sets whether patterns are removed from the list after they finish.
         * @param consume True to remove patterns after they finish, false to leave them
         */
        void consumePatterns(bool consume) { consumePatterns_ = consume; }

        bool noPatterns() { return patterns_.empty(); }

        ModuleChain& moduleChain() { return moduleChain_; }

    private:
        void processEvents();
        Sample generateNextSample();

        std::deque<Pattern> patterns_;

        ModuleChain moduleChain_;

        SPSCRingBuffer<Pattern, 8> patternQueue_;

        MoveableAtomic<bool> enabled_;

        double volume_;
        double pan_; //-1 for hard left, 1 for hard right, 0 center
        unsigned int currentPattern_;
        bool loop_;
        unsigned int loopStart_; //index of pattern
        bool consumePatterns_;
        bool autoDisable_;
        unsigned int silentSamples_;
    };
}

#endif //CHIPAUDIO_CHANNEL_HPP
