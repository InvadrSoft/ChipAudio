/*! \file
 *  \brief Generative example
 *
 *  Simple generative music example, any input causes program to exit.
 *
 *  \include generative.cpp
 */

#include <array>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include "chipaudio.hpp"
#include "chipmodules.hpp"

//the number of channels to use
constexpr int CHANNELS = 16;

//the scale to use, given as intervals from the root note
constexpr std::array<int, 5> SCALE = { 0, 3, 5, 7, 10 };

//the number of octaves to spread the notes over
constexpr int OCTAVES = 4;

int main()
{
    //seed the random number generator
    srand(static_cast<unsigned int>(time(nullptr) ) );

    //choose a random key from all 12 keys
    const int key = rand() % 12;

    //create the chip object
    chip::Chip chip;

    //do this for every channel
    for(int i = 0; i < CHANNELS; i++)
    {
        //add a new channel to the chip
        chip::Channel& channel = chip.addChannel();

        //set the volume and pan for the channel
        channel.volume(1.0 / CHANNELS + 0.3);
        channel.pan( (rand() % 20 + -10) / 10.0);

        //this means the channel will continuously loop through its patterns
        channel.loop(true);

        //create a wavetable of size 4, and randomise each entry
        chip::WaveTable waveTable(chip::WaveTable::SIZE_4);
        for(int j = 0; j < waveTable.size(); j++)
        {
            waveTable[j] = -1.0 + ( (double)rand() / RAND_MAX) * (1.0 - -1.0);
        }

        //create the first module in the chain, a filter
        chip::Module &filter = channel.addModule(new chip::FilterLP1Pole());

        //make the filter the output module of the channel
        channel.output(&filter);

        //create a new parameter and use this as an input to the filter
        chip::Value &cutoff = channel.addParameter(chip::Value(440), "cutoff");
        filter.input(chip::FilterLP1Pole::CUTOFF) = &cutoff;

        //create an oscillator using the wavetable created earlier
        chip::Oscillator &oscillator = channel.addOscillator(new chip::Oscillator(waveTable, chip::Oscillator::COSINE));
        //and use this as another input to the filter
        filter.input(chip::FilterLP1Pole::IN) = &oscillator;

        //set the channel's note frequency module as an input to the oscillator
        oscillator.input(chip::Oscillator::FREQUENCY) = &channel.input(chip::Channel::NOTE_FREQ);

        //create an envelope and use this as an input to the oscillator
        chip::Module &envelope = channel.addModule(new chip::EnvelopeADSR());
        oscillator.input(chip::Oscillator::AMPLITUDE) = &envelope;

        //set the channel's gate in module as an input to the envelope
        envelope.input(chip::EnvelopeADSR::GATE) = &channel.input(chip::Channel::GATE_IN);

        //create more parameters to use as inputs to the envelope
        chip::Module &attack = channel.addParameter(chip::Value(0.11), "attack");
        envelope.input(chip::EnvelopeADSR::ATTACK) = &attack;

        chip::Module &decay = channel.addParameter(chip::Value(0.38), "decay");
        envelope.input(chip::EnvelopeADSR::DECAY) = &decay;

        chip::Module &sustain = channel.addParameter(chip::Value(0.1), "sustain");
        envelope.input(chip::EnvelopeADSR::SUSTAIN) = &sustain;

        chip::Module &release = channel.addParameter(chip::Value(0.01), "release");
        envelope.input(chip::EnvelopeADSR::RELEASE) = &release;

        //choose a random note from the scale in a random octave to use for this channel
        int note = (key + SCALE[rand() % SCALE.size()]) + ( (rand() % OCTAVES + 1) * 12 );

        //add a new pattern to the channel
        chip::Pattern& pattern = channel.addPattern(chip::Pattern() );

        //add a note on event to the pattern, using the chosen note and starting at a random time
        pattern.addEvent(chip::Event(chip::NOTE_ON, note, 1),
                         chip::TimeValue(1, rand() % 4 + 1, rand() % 4 + 1, 1) );

        //choose a random end time for the note
        chip::TimeValue endTime(2, rand() % 4 + 1, rand() % 4 + 1, 1);

        //add a note off event at the end time
        pattern.addEvent(chip::Event(chip::NOTE_OFF, note, 1), endTime );

        //set the end of the pattern to the tick after the note off
        pattern.endPosition(++endTime);
    }

    //start playback
    chip.start();

    //wait for user input
    std::cin.get();

    //stop playback
    chip.stop();

    return 0;
}