/*! \file
 *  \brief Prelude example
 *
 *  \include prelude.cpp
 */

#include <array>
#include <iostream>
#include "chipaudio.hpp"
#include "chipmodules.hpp"

//the chord shapes used in the tune, given as intervals from the root note
constexpr std::array<std::array<int, 5>, 3> CHORD_SHAPES = {
{
     {0, 2, 4, 7, 12},
     {0, 2, 3, 7, 12},
     {0, 4, 7, 11, 12}
} };

//all the chords in the tune, given as the index of the chord shape and the root note
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
    //create the chip object
    chip::Chip chip;

    //set the bpm of the tune
    chip.tempo(88);

    //two channels are used for the echo effect
    for(int channelNum = 0; channelNum < 2; channelNum++)
    {
        //add a channel to the chip
        chip::Channel& channel = chip.addChannel();

        //set the volume and pan
        channel.volume(0.5);
        channel.pan(-0.1);

        //create a wavetable containing a square wave
        chip::WaveTable waveTable(chip::WaveTable::SIZE_32);
        waveTable = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
                      -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0 };

        //create an oscillator using the wavetable, with cosine interpolation to avoid aliasing
        chip::Oscillator &oscillator = channel.addOscillator(new chip::Oscillator(waveTable, chip::Oscillator::COSINE));
        //use the oscillator as the output module of the channel
        channel.output(&oscillator);

        //use the channel's note frequency module as an input to the oscillator
        oscillator.input(chip::Oscillator::FREQUENCY) = &channel.input(chip::Channel::NOTE_FREQ);

        //create an envelope and use this as an input to the oscillator
        chip::Module &envelope = channel.addModule(new chip::EnvelopeADSR() );
        oscillator.input(chip::Oscillator::AMPLITUDE) = &envelope;

        //set the channel's gate in module as an input to the envelope
        envelope.input(chip::EnvelopeADSR::GATE) = &channel.input(chip::Channel::GATE_IN);

        //create more parameters to use as inputs to the envelope
        chip::Module &attack = channel.addParameter(chip::Value(0.001), "attack");
        envelope.input(chip::EnvelopeADSR::ATTACK) = &attack;

        chip::Module &decay = channel.addParameter(chip::Value(0.28), "decay");
        envelope.input(chip::EnvelopeADSR::DECAY) = &decay;

        chip::Module &sustain = channel.addParameter(chip::Value(0.1), "sustain");
        envelope.input(chip::EnvelopeADSR::SUSTAIN) = &sustain;

        chip::Module &release = channel.addParameter(chip::Value(0.01), "release");
        envelope.input(chip::EnvelopeADSR::RELEASE) = &release;

        //for the echo channel
        if(channelNum > 0)
        {
            //make the volume lower and change the pan
            channel.volume(0.35);
            channel.pan(0.2);

            //add an extra short pattern at the beginning to delay the channel
            chip::Pattern& delay = channel.addPattern(chip::Pattern() );
            delay.endPosition(chip::TimeValue(1, 1, 1, 200) );

            //start looping from the second pattern so the delay pattern is not repeated
            channel.loopStart(1);
        }

        //add a pattern to the channel
        chip::Pattern& pattern = channel.addPattern(chip::Pattern() );

        //this time value will be incremented for each note
        chip::TimeValue currentTime(1, 1, 1, 1);

        //this time value represents the duration of each note
        chip::TimeValue noteDuration(0, 0, 0, 200);

        //for every chord in the tune
        for(int i = 0; i < CHORDS.size(); i++)
        {
            //the second value in the chords pair is the root note of the chord
            int root = CHORDS[i].second;

            //the first value is the chord shape
            auto& chordShape = CHORD_SHAPES[CHORDS[i].first];

            //for the ascending part of the arpeggio
            for(int j = 0; j < 4; j++)
            {
                //for each octave of the arpeggio
                for(int k = 0; k < 4; k++)
                {
                    //add a note on event using the chord data
                    pattern.addEvent(chip::Event(chip::NOTE_ON, (root + (j * 12) + chordShape[k]), 1), currentTime);

                    //add a note off event using the note duration
                    pattern.addEvent(chip::Event(chip::NOTE_OFF), currentTime + noteDuration);

                    //increment the current time by 1 division
                    currentTime += chip::TimeValue(0, 0, 1, 0);
                }
            }

            //for the descending part of the arpeggio
            for(int j = 3; j >= 0; j--)
            {
                //for each octave of the arpeggio
                for(int k = 4; k > 0; k--)
                {
                    //add a note on event using the chord data
                    pattern.addEvent(chip::Event(chip::NOTE_ON, (root + (j * 12) + chordShape[k]), 1), currentTime);

                    //add a note off event using the note duration
                    pattern.addEvent(chip::Event(chip::NOTE_OFF), currentTime + noteDuration);

                    //increment the current time by 1 division
                    currentTime += chip::TimeValue(0, 0, 1, 0);
                }
            }
        }

        //set the end position of the pattern
        pattern.endPosition(chip::TimeValue(17, 1, 1, 1) );

        //repeat the pattern when it's finished
        channel.loop(true);
    }

    //start playback
    chip.start();

    //wait for user input
    std::cin.get();

    //stop playback
    chip.stop();

    return 0;
}