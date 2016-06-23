/*! \file
 *  \brief Prelude example
 *
 *  \include prelude.cpp
 */

#include <array>
#include <iostream>
#include "chipaudio.hpp"
#include "chipmodules.hpp"

constexpr std::array<std::array<int, 5>, 3> CHORD_SHAPES = {
{
     {0, 2, 4, 7, 12},
     {0, 2, 3, 7, 12},
     {0, 4, 7, 11, 12}
} };

constexpr std::array<std::pair<int, int>, 8> CHORDS = {
{
     {0, chip::C3},
     {1, chip::A2},
     {0, chip::C3},
     {1, chip::A2},
     {0, chip::F2},
     {0, chip::G2},
     {2, chip::Ab2},
     {2, chip::Bb2}
} };

int main()
{
    chip::Chip chip;
    chip.tempo(88);

    for(int channelNum = 0; channelNum < 2; channelNum++)
    {
        chip::Channel& channel = chip.addChannel(chip::Channel() );
        channel.volume(0.5);
        channel.pan(-0.1);

        chip::WaveTable waveTable(chip::WaveTable::SIZE_32);
        waveTable = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
                      -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0 };

        chip::Oscillator &oscillator = channel.addOscillator(new chip::Oscillator(waveTable, chip::Oscillator::COSINE));
        channel.output(&oscillator);
        //inputs to oscillator
        oscillator.input(chip::Oscillator::FREQUENCY) = &channel.input(chip::Channel::NOTE_FREQ);
        chip::Module &envelope = channel.addModule(new chip::EnvelopeADSR() );
        oscillator.input(chip::Oscillator::AMPLITUDE) = &envelope;
        //inputs to envelope
        envelope.input(chip::EnvelopeADSR::GATE) = &channel.input(chip::Channel::GATE_IN);
        chip::Module &attack = channel.addParameter(chip::Value(0.001), "attack");
        envelope.input(chip::EnvelopeADSR::ATTACK) = &attack;
        chip::Module &decay = channel.addParameter(chip::Value(0.28), "decay");
        envelope.input(chip::EnvelopeADSR::DECAY) = &decay;
        chip::Module &sustain = channel.addParameter(chip::Value(0.1), "sustain");
        envelope.input(chip::EnvelopeADSR::SUSTAIN) = &sustain;
        chip::Module &release = channel.addParameter(chip::Value(0.01), "release");
        envelope.input(chip::EnvelopeADSR::RELEASE) = &release;

        if(channelNum > 0)
        {
            channel.volume(0.35);
            channel.pan(0.2);
            chip::Pattern& delay = channel.addPattern(chip::Pattern() );
            delay.endPosition(chip::TimeValue(1, 1, 1, 200) );
            channel.loopStart(1);
        }

        chip::Pattern& pattern = channel.addPattern(chip::Pattern() );
        chip::TimeValue currentTime(1, 1, 1, 1);
        chip::TimeValue noteDuration(0, 0, 0, 200);

        for(int i = 0; i < CHORDS.size(); i++)
        {
            int root = CHORDS[i].second;
            auto& chordShape = CHORD_SHAPES[CHORDS[i].first];

            for(int j = 0; j < 4; j++)
            {
                for(int k = 0; k < 4; k++)
                {
                    pattern.addEvent(chip::Event(chip::NOTE_ON, (root + (j * 12) + chordShape[k]), 1), currentTime);
                    pattern.addEvent(chip::Event(chip::NOTE_OFF), currentTime + noteDuration);
                    currentTime += chip::TimeValue(0, 0, 1, 0);
                }
            }

            for(int j = 3; j >= 0; j--)
            {
                for(int k = 4; k > 0; k--)
                {
                    pattern.addEvent(chip::Event(chip::NOTE_ON, (root + (j * 12) + chordShape[k]), 1), currentTime);
                    pattern.addEvent(chip::Event(chip::NOTE_OFF), currentTime + noteDuration);
                    currentTime += chip::TimeValue(0, 0, 1, 0);
                }
            }
        }

        pattern.endPosition(chip::TimeValue(17, 1, 1, 1) );
        channel.loop(true);
    }

    chip.start();

    std::cin.get();

    chip.stop();

    return 0;
}