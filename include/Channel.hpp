//
// Created by Myles Inglis on 14/06/2016.
//

#ifndef CHIPAUDIO_CHANNEL_HPP
#define CHIPAUDIO_CHANNEL_HPP

#include <deque>
#include <vector>
#include <map>
#include <memory>
#include "Pattern.hpp"
#include "Module.hpp"
#include "Oscillator.hpp"
#include "Value.hpp"
#include "Notes.hpp"
#include "Sample.hpp"

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
         * Enumeration of all available input modules on this channel.
         */
        enum InputModule
        {
            NOTE_FREQ,
            NOTE_NUMBER,
            GATE_IN,
            NEW_NOTE,
            INPUTS_TOTAL
        };

        /**
         * Default constructor.
         */
        Channel() : volume_(1), pan_(0), currentPattern_(0), loop_(0), loopStart_(0), output_(nullptr)
        {
            for(int i = 0; i < INPUTS_TOTAL; i++)
            {
                inputs_.push_back(Value() );
            }
        }

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
         * Add a module to the channel.
         * @param module Module to add
         * @return A reference to the added module
         */
        Module& addModule(Module* module)
        {
            modules_.push_back(std::unique_ptr<Module>(module) );
            return *modules_.back();
        }

        /**
         * Add a parameter to the channel.
         * @param parameter Parameter to add
         * @param name Name of parameter
         * @return A reference to the added parameter
         */
        Value& addParameter(Value parameter, std::string name)
        {
            auto result = parameters_.emplace(name, std::move(parameter) );
            return result.first->second;
        }

        /**
         * Add an oscillator to the channel.
         * @param oscillator Oscillator to add
         * @return A reference to the added oscillator
         */
        Oscillator& addOscillator(Oscillator* oscillator)
        {
            oscillators_.push_back(std::unique_ptr<Oscillator>(oscillator) );
            return *oscillators_.back();
        }

        /**
         * Returns the specified input module.
         * @param input Input module index
         * @return A reference to the specified input module
         */
        Value& input(InputModule input) { return inputs_[input]; }

        /**
         * Sets the output module of the channel.
         * @param module Pointer to module to use as output
         */
        void output(Module* module) { output_ = module; }

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

        bool noPatterns() { return patterns_.empty(); }

    private:
        void processEvents();
        Sample generateNextSample();

        std::deque<Pattern> patterns_;

        std::vector<std::unique_ptr<Module> > modules_;
        std::vector<Value> inputs_;
        std::map<std::string, Value> parameters_;
        std::vector<std::unique_ptr<Oscillator> > oscillators_;
        Module* output_;

        double volume_;
        double pan_; //-1 for hard left, 1 for hard right, 0 center
        unsigned int currentPattern_;
        bool loop_;
        unsigned int loopStart_; //index of pattern
    };
}

#endif //CHIPAUDIO_CHANNEL_HPP
