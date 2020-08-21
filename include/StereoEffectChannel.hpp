#ifndef CHIPAUDIO_STEREOEFFECTCHANNEL_HPP
#define CHIPAUDIO_STEREOEFFECTCHANNEL_HPP

#include "Module.hpp"
#include "Sample.hpp"
#include "Value.hpp"

#include <array>

namespace chip
{
    class StereoEffectChannel
    {
    public:
        enum Channel
        {
            LEFT_CHANNEL,
            RIGHT_CHANNEL
        };

        StereoEffectChannel() : outputs_({nullptr, nullptr}) {}

        Module& addModule(Module* module, Channel channel)
        {
            moduleLists_[channel].push_back(std::unique_ptr<Module>(module) );
            return *moduleLists_[channel].back();
        }

        void output(Module* module, Channel channel) { outputs_[channel] = module; }

        Value& input(Channel channel) { return inputs_[channel]; }

        Sample process(Sample input)
        {
            inputs_[LEFT_CHANNEL] = input.left;
            inputs_[RIGHT_CHANNEL] = input.right;
            return {
                outputs_[LEFT_CHANNEL] == nullptr ? input.left : outputs_[LEFT_CHANNEL]->output(),
                outputs_[RIGHT_CHANNEL] == nullptr ? input.right : outputs_[RIGHT_CHANNEL]->output()
            };
        }

    private:
        using ModuleList = std::vector<std::unique_ptr<Module> >;
        std::array<ModuleList, 2> moduleLists_;
        std::array<Module*, 2> outputs_;
        std::array<Value, 2> inputs_;
    };
}

#endif //CHIPAUDIO_STEREOEFFECTCHANNEL_HPP