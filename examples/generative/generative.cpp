/*! \file
 *  \brief Generative example
 *
 *  Simple generative music example, any input causes program to exit.
 *
 *  \include generative.cpp
 */

#include <array>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "chipaudio.hpp"
#include "chipmodules.hpp"

constexpr int CHANNELS = 16;
constexpr std::array<int, 5> SCALE = { 0, 3, 5, 7, 10 };
constexpr int OCTAVES = 4;

int main()
{
    srand(static_cast<unsigned int>(time(nullptr) ) );

    const int key = rand() % 12;

    chip::Chip chip;

    for(int i = 0; i < CHANNELS; i++)
    {
        chip::Channel& channel = chip.addChannel(chip::Channel() );
        channel.volume(1.0 / CHANNELS + 0.3);
        channel.pan( (rand() % 20 + -10) / 10.0);
        channel.loop(true);

        chip::WaveTable waveTable(chip::WaveTable::SIZE_4);
        for(int j = 0; j < waveTable.size(); j++)
        {
            waveTable[j] = -1.0 + ( (double)rand() / RAND_MAX) * (1.0 - -1.0);
        }

        //first module in chain
        chip::Module &filter = channel.addModule(new chip::FilterLP1Pole());
        channel.output(&filter);
        //inputs to filter
        chip::Value &cutoff = channel.addParameter(chip::Value(440), "cutoff");
        filter.input(chip::FilterLP1Pole::CUTOFF) = &cutoff;
        chip::Oscillator &oscillator = channel.addOscillator(new chip::Oscillator(waveTable, chip::Oscillator::COSINE));
        filter.input(chip::FilterLP1Pole::IN) = &oscillator;
        //inputs to oscillator
        oscillator.input(chip::Oscillator::FREQUENCY) = &channel.input(chip::Channel::NOTE_FREQ);
        chip::Module &envelope = channel.addModule(new chip::EnvelopeADSR());
        oscillator.input(chip::Oscillator::AMPLITUDE) = &envelope;
        //inputs to envelope
        envelope.input(chip::EnvelopeADSR::GATE) = &channel.input(chip::Channel::GATE_IN);
        chip::Module &attack = channel.addParameter(chip::Value(0.11), "attack");
        envelope.input(chip::EnvelopeADSR::ATTACK) = &attack;
        chip::Module &decay = channel.addParameter(chip::Value(0.38), "decay");
        envelope.input(chip::EnvelopeADSR::DECAY) = &decay;
        chip::Module &sustain = channel.addParameter(chip::Value(0.1), "sustain");
        envelope.input(chip::EnvelopeADSR::SUSTAIN) = &sustain;
        chip::Module &release = channel.addParameter(chip::Value(0.01), "release");
        envelope.input(chip::EnvelopeADSR::RELEASE) = &release;

        int note = (key + SCALE[rand() % SCALE.size()]) + ( (rand() % OCTAVES + 1) * 12 );

        chip::Pattern& pattern = channel.addPattern(chip::Pattern() );

        pattern.addEvent(chip::Event(chip::NOTE_ON, note, 1),
                         chip::TimeValue(1, rand() % 4 + 1, rand() % 4 + 1, 1) );

        chip::TimeValue endTime(2, rand() % 4 + 1, rand() % 4 + 1, 1);
        pattern.addEvent(chip::Event(chip::NOTE_OFF, note, 1), endTime );

        pattern.endPosition(++endTime);
    }

    chip.start();

    std::cin.get();

    chip.stop();

    return 0;
}