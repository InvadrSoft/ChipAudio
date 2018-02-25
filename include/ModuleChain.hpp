//
// Created by Myles Inglis on 22/02/2018.
//

#ifndef CHIPAUDIO_MODULECHAIN_HPP
#define CHIPAUDIO_MODULECHAIN_HPP

#include <vector>
#include <map>
#include <string>
#include "Value.hpp"
#include "Oscillator.hpp"
#include "Sample.hpp"

namespace chip
{
    class ModuleChain
    {
    public:
        /**
         * Enumeration of all available input modules.
         */
        enum InputModule
        {
            NOTE_FREQ,
            NOTE_NUMBER,
            GATE_IN,
            NEW_NOTE,
            INPUTS_TOTAL
        };

        ModuleChain() : inputs_(INPUTS_TOTAL), output_(nullptr) {}

        /**
         * Add a module to the chain.
         * @param module Module to add
         * @return A reference to the added module
         */
        Module& addModule(Module* module)
        {
            modules_.push_back(std::unique_ptr<Module>(module) );
            return *modules_.back();
        }

        /**
         * Add a parameter to the module chain.
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
         * Add an oscillator to the module chain.
         * @param oscillator Oscillator to add
         * @return A reference to the added oscillator
         */
        Oscillator& addOscillator(Oscillator* oscillator)
        {
            oscillators_.push_back(std::unique_ptr<Oscillator>(oscillator) );
            return *oscillators_.back();
        }

        void setParameter(std::string name, double value) { parameters_[name] = value; }

        /**
         * Returns the specified input module.
         * @param input Input module index
         * @return A reference to the specified input module
         */
        Value& input(size_t input) { return inputs_[input]; }

        /**
         * Sets the output module of the chain.
         * @param module Pointer to module to use as output
         */
        void output(Module* module) { output_ = module; }

        double output() { return output_->output(); }

        void clear()
        {
            modules_.clear();
            parameters_.clear();
            oscillators_.clear();
            output_ = nullptr;
        }

    private:
        std::vector<std::unique_ptr<Module> > modules_;
        std::vector<Value> inputs_;
        std::map<std::string, Value> parameters_;
        std::vector<std::unique_ptr<Oscillator> > oscillators_;
        Module* output_;
    };
}

#endif //CHIPAUDIO_MODULECHAIN_HPP
