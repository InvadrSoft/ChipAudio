//
// Created by Myles Inglis on 14/06/2016.
//

#ifndef CHIPAUDIO_CHANNEL_HPP
#define CHIPAUDIO_CHANNEL_HPP

#include <vector>
#include <map>
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
    public:
        /**
         * Enumeration of all available input modules on this channel.
         */
        enum InputModule
        {
            NOTE_FREQ,
            NOTE_NUMBER,
            GATE_IN,
            INPUTS_TOTAL
        };

        /**
         * Default constructor.
         */
        Channel() : volume_(1), pan_(0), currentPattern_(0), loop_(0), output_(nullptr)
        {
            for(int i = 0; i < INPUTS_TOTAL; i++)
            {
                inputs_.push_back(Value() );
            }
        }

        /**
         * Process events and advance to the next tick in the current pattern.
         */
        void processEvents();

        /**
         * Get the next sample from the output module.
         * @return The generated sample value
         */
        Sample generateNextSample();

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

    private:
        std::vector<Pattern> patterns_;

        std::vector<std::unique_ptr<Module> > modules_;
        std::vector<Value> inputs_;
        std::map<std::string, Value> parameters_;
        std::vector<std::unique_ptr<Oscillator> > oscillators_;
        Module* output_;

        double volume_;
        double pan_; //-1 for hard left, 1 for hard right, 0 center
        unsigned int currentPattern_;
        bool loop_;
    };
}

#endif //CHIPAUDIO_CHANNEL_HPP
